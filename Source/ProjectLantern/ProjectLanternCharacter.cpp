// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectLanternCharacter.h"
#include "ProjectLanternProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "BasicObject.h"
#include "ProjectLanternHUD.h"
#include "EngineUtils.h"
#include "ProjectLanternGameMode.h"
#include "Enemy.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProjectLanternCharacter

AProjectLanternCharacter::AProjectLanternCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	TouchRange = 1000.f;
	IsHoldingObj = false;
	ZoomAmmount = 0.85f;
	ZoomInMulti = 0.999f;
	ZoomOutMulti = 0.999f;
	FadeTime = 1.5f;
	CanMove = true;
	CanClick = true;
	CanFire = true;
	CanMakeStepSound = true;
	SpeedMultiplier = 1.f;
	IsHoldingGun = false;
	GunDamage = 50.f;
	GunRange = 1000000.f;
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FoV = FirstPersonCameraComponent->FieldOfView;
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Item = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Item"));
	FP_Item->bCastDynamicShadow = false;
	FP_Item->CastShadow = false;
	FP_Item->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	FP_Item->SetupAttachment(Mesh1P);


	CurrentObject = NULL;
}

void AProjectLanternCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Item->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	Mesh1P->SetHiddenInGame(!IsHoldingGun, true);

	WalkSound = WalkGrassSound;
}

void AProjectLanternCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	//This verification can be removed since we check for Ammo before calling this funcion
	const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
	const FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * TouchRange) + StartTrace;
	const float CurrentFoV = FirstPersonCameraComponent->FieldOfView;
	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 5, 0, 3);
	if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))//I should cast this outside of tick for better performance
	{
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			if (ABasicObject* BO = Cast<ABasicObject>(Hit.GetActor()))
			{
				CurrentObject = BO;
				GM->UpdateFlavorText(BO->ObjMessage);

				if (FirstPersonCameraComponent->FieldOfView > FoV * ZoomAmmount)
					FirstPersonCameraComponent->SetFieldOfView(CurrentFoV * ZoomInMulti);
			}
			else
			{
				CurrentObject = NULL;
				GM->UpdateFlavorText("");
				if (FirstPersonCameraComponent->FieldOfView < FoV)
					FirstPersonCameraComponent->SetFieldOfView(CurrentFoV / ZoomOutMulti);
			}
		}
		else
		{
			CurrentObject = NULL;
			GM->UpdateFlavorText("");
			if (FirstPersonCameraComponent->FieldOfView < FoV)
				FirstPersonCameraComponent->SetFieldOfView(CurrentFoV / ZoomOutMulti);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectLanternCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AProjectLanternCharacter::OnAction);
	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AProjectLanternCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectLanternCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectLanternCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AProjectLanternCharacter::OnAction()
{
	//Interact with the object
	if (CanClick)
	{
		FHitResult Hit;
		const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
		const FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * TouchRange) + StartTrace;

		FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
		InteractWithObj();
	}
}

void AProjectLanternCharacter::OnFire()
{
	// try and fire gun
	if (IsHoldingGun && CanFire)
	{
		FHitResult Hit;
		const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
		const FVector EndTrace = (FirstPersonCameraComponent->GetForwardVector() * GunRange) + StartTrace;

		FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
		{
			if (AEnemy* Enemy = Cast<AEnemy>(Hit.GetActor()))
			{
				Enemy->TakeDamage(GunDamage);
			}
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

		ToggleFire();
		GetWorldTimerManager().SetTimer(TimerHandle_HandleRateOfFire, this, &AProjectLanternCharacter::ToggleFire, RateOfFireTime, false);

		//FP_Item->SetVisibility(false);
	}
}


void AProjectLanternCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && CanMove)
	{

		if (WalkSound != NULL && CanMakeStepSound)
		{
			FHitResult Hit;
			const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
			const FVector EndTrace = (FirstPersonCameraComponent->GetUpVector() * -1 * GunRange) + StartTrace;

			FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
			if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
			{
				if (AActor* Floor = Cast<AActor>(Hit.GetActor()))
				{
					if (Floor->GetName() == "SM_Plane_19") //indeed there is a better way to check what I'm stepping over(check for materials), but I'm tired and wanna release an alpha
						WalkSound = WalkWoodSound;
					else if (Floor->GetName() == "SM_Plane_83")
						WalkSound = WalkGrassSound;
				}
			}

			UGameplayStatics::PlaySoundAtLocation(this, WalkSound, GetActorLocation(), 1.f, FMath::RandRange(0.1f, 1.1f));
			ToggleCanMakeWalkingSound();
			GetWorldTimerManager().SetTimer(TimerHandle_HandleWalkSound, this, &AProjectLanternCharacter::ToggleCanMakeWalkingSound, WalkSoundTime, false);
		}
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value* SpeedMultiplier);
	}
}

void AProjectLanternCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && CanMove)
	{
		// add movement in that direction

		if (WalkSound != NULL && CanMakeStepSound)
		{
			FHitResult Hit;
			const FVector StartTrace = FirstPersonCameraComponent->GetComponentLocation();
			const FVector EndTrace = (FirstPersonCameraComponent->GetUpVector() * -1 * GunRange) + StartTrace;

			FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
			if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParams))
			{
				if (AActor* Floor = Cast<AActor>(Hit.GetActor()))
				{
					if (Floor->GetName() == "SM_Plane_19") //indeed there is a better way to check what I'm stepping over(check for materials), but I'm tired and wanna release an alpha
						WalkSound = WalkWoodSound;
					else if (Floor->GetName() == "SM_Plane_83")
						WalkSound = WalkGrassSound;
				}
			}
			UGameplayStatics::PlaySoundAtLocation(this, WalkSound, GetActorLocation(), 1.f, FMath::RandRange(0.1f, 1.1f));
			ToggleCanMakeWalkingSound();
			GetWorldTimerManager().SetTimer(TimerHandle_HandleWalkSound, this, &AProjectLanternCharacter::ToggleCanMakeWalkingSound, WalkSoundTime, false);
		}

		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value * SpeedMultiplier);
	}
}

void AProjectLanternCharacter::InteractWithObj()
{
	if (CurrentObject)
	{
		IsHoldingObj = !IsHoldingObj;
		if (CurrentObject->ScreenFadesToBlackAfterAction && CurrentObject->IsEnabled)
		{
			ToggleMovement();
			GetWorldTimerManager().SetTimer(TimerHandle_HandleFadeBlack, this, &AProjectLanternCharacter::ToggleMovement, FadeTime, false);
		}
		CurrentObject->Action();
		if (!IsHoldingObj)
			CurrentObject = NULL;
	}
}

void AProjectLanternCharacter::ToggleMovement()
{
	CanMove = !CanMove;
	CanClick = !CanClick;
}

void AProjectLanternCharacter::ToggleCanMakeWalkingSound()
{
	CanMakeStepSound = !CanMakeStepSound;
}

void AProjectLanternCharacter::ToggleFire()
{
	CanFire = !CanFire;
}

void AProjectLanternCharacter::ToggleGun()
{
	IsHoldingGun = !IsHoldingGun;
	Mesh1P->SetHiddenInGame(!IsHoldingGun, true);
}