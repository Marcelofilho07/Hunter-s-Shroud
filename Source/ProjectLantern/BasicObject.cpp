// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicObject.h"
#include "ProjectLanternGameMode.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "ProjectLanternInstance.h"
#include "GameFramework/Character.h"

// Sets default values
ABasicObject::ABasicObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsEnabled = true;
	IsDestroyedAfterUse = false;
	IsChangeVisualMeshAfterUse = false;
	IsChangeAmbience = false;
	IsTeleport = false;
	BGravity = true;
	BHolding = false;
	ObjId = 0;
	NextObjId = 0;
	TeleportDelay = 1.5f;
	ChangeDelay = 1.5f;
	DestroyDelay = 1.5f;
	AmbienceDelay = 1.5f;
	EndGameDelay = 1.5f;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	if (StaticMesh)
	{
		VisualMesh->SetStaticMesh(StaticMesh);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

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
	//VisualMesh->SetVisibility(false);
	//VisualMesh2->SetVisibility(true);
}

void ABasicObject::ChangeAmbience()
{
	if(AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
		GM->ChangeAmbience(LightningLevel, LightningColor, FogColor);
}


void ABasicObject::DestroySelf()
{

	if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
		GM->RemoveActor(this);
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
		}

		if (ObjSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ObjSound, GetActorLocation());
		}

		if (IsChangeAmbience)
			GetWorldTimerManager().SetTimer(TimerHandle_HandleAmbience, this, &ABasicObject::ChangeAmbience, AmbienceDelay, false);

		if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
		{
			if (NextObjId != 0)
				GM->EnableObj(NextObjId);
			if (NextEventId != 0)
				GM->EnableEvent(NextEventId);
			if (ScreenFadesToBlackAfterAction)
				GM->FadeScreen();
		}

		if (IsTeleport && !TeleportDestination.IsZero())
		{

			GetWorldTimerManager().SetTimer(TimerHandle_HandleTeleport, this, &ABasicObject::Teleport, TeleportDelay, false);
		}

		if (IsDisabledAfterUse)
		{
			IsEnabled = false;
		}

		if(IsEndGame)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_HandleTeleport, this, &ABasicObject::SwapLevel, EndGameDelay, false);
		}
	}

}

void ABasicObject::SwapLevel()
{
	UWorld* TheWorld = GetWorld();

	FString CurrentLevel = TheWorld->GetMapName();

	if (UProjectLanternInstance* GI = Cast<UProjectLanternInstance>(GetWorld()->GetGameInstance()))
	{
		if (!GI->IsEndGame)
			GI->ToggleEndGame();
	}

	UGameplayStatics::OpenLevel(GetWorld(), "MainMenuLevel");

}