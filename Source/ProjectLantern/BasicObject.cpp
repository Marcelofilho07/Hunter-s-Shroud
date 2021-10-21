// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicObject.h"
#include "ProjectLanternGameMode.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ABasicObject::ABasicObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsEnabled = true;
	IsDestroyedAfterUse = false;
	IsChangeVisualMeshAfterUse = false;
	IsTeleport = false;
	BGravity = true;
	BHolding = false;
	ObjId = 0;
	NextTaskObjId = 0;
	TeleportDelay = 1.5f;
	ChangeDelay = 1.5f;
	DestroyDelay = 1.5f;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetOnlyOwnerSee(false);
	VisualMesh->SetSimulatePhysics(BGravity);
	SetRootComponent(VisualMesh);
	VisualMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));
	VisualMesh2->SetOnlyOwnerSee(false);
	VisualMesh2->SetSimulatePhysics(BGravity);
	VisualMesh2->SetVisibility(false);
	SetRootComponent(VisualMesh2);

}


// Called when the game starts or when spawned
void ABasicObject::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerCamera = MyCharacter->FindComponentByClass<UCameraComponent>();

	TArray<USceneComponent*> Components;

	MyCharacter->GetComponents(Components);

	if (Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if (Comp->GetName() == "FP_Item")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}
	
}

void ABasicObject::Teleport()
{
	MyCharacter->SetActorLocation(TeleportDestination);
}

void ABasicObject::ChangeMesh()
{
	VisualMesh->SetVisibility(false);
	VisualMesh2->SetVisibility(true);
}


void ABasicObject::DestroySelf()
{
	this->Destroy();
}


// Called every frame
void ABasicObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABasicObject::Action()
{
	if (IsEnabled)
	{
		if (IsChangeVisualMeshAfterUse)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_HandleChange, this, &ABasicObject::ChangeMesh, ChangeDelay, false);
		}
		if (IsDestroyedAfterUse)
		{

			GetWorldTimerManager().SetTimer(TimerHandle_HandleDestroy, this, &ABasicObject::DestroySelf, DestroyDelay, false);
			/*BHolding = !BHolding;
			BGravity = !BGravity;
			VisualMesh->SetEnableGravity(BGravity);
			VisualMesh->SetSimulatePhysics(BHolding ? false : true);
			VisualMesh->SetCollisionEnabled(BHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
			if (HoldingComp && BHolding)
			{
				VisualMesh->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepRelativeTransform);
				SetActorLocation(HoldingComp->GetComponentLocation());
			}

			if (!BHolding)
			{
				VisualMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
				//ForwardVector = PlayerCamera->GetForwardVector();
				//VisualMesh->AddForce(ForwardVector * 10 * VisualMesh->GetMass());
			}*/
		}

		if (ObjSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ObjSound, GetActorLocation());
		}

		if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GM->CompleteTask(ObjId, NextTaskObjId);
			if(ScreenFadesToBlackAfterAction)
				GM->FadeScreen();
		}

		if (IsTeleport && !TeleportDestination.IsZero())
		{

			GetWorldTimerManager().SetTimer(TimerHandle_HandleTeleport, this, &ABasicObject::Teleport, TeleportDelay, false);
		}
	}
}

