// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectLanternGameMode.h"
#include "ProjectLanternStateBase.h"
#include "ProjectLanternHUD.h"
#include "ProjectLanternCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BasicObject.h"
#include "EventTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "EngineUtils.h"
#include "LevelSequence.h"
#include "ProjectLanternInstance.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

AProjectLanternGameMode::AProjectLanternGameMode()
	: Super()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> WoodMorning(TEXT("/Game/Audio/WoodMorning"));
	SoundBaseMorning = WoodMorning.Object;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProjectLanternCharacter::StaticClass(), MainPlayer);

	// use our custom HUD class
	HUDClass = AProjectLanternHUD::StaticClass();
}

void AProjectLanternGameMode::EnableObj(int32 NextTaskId)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		for (AActor* Objs : GS->FoundActors)
		{
			if (ABasicObject* BO = Cast<ABasicObject>(Objs))
			{
				if (BO->ObjId == NextTaskId)
				{
					BO->IsEnabled = true;
				}
			}
		}
	}
}

void AProjectLanternGameMode::FadeScreen()
{
	for (TActorIterator<class ALevelSequenceActor> it(GetWorld()); it; ++it)
	{
		ALevelSequenceActor* lsa = *it;

		if (lsa->GetName() == TEXT("FadeBlack"))
			lsa->SequencePlayer->Play();
	}
}

void AProjectLanternGameMode::ChangeAmbience(float LightningLevel, FColor LightningColor, FColor FogColor)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		GS->LightningLevel = LightningLevel;
		GS->LightningColor = LightningColor;
		GS->FogColor = FogColor;
		if (LightningLevel >= 0.75 && SoundBaseMorning)
		{
			if(!AudioComponentAmbienceDay)
				AudioComponentAmbienceDay = UGameplayStatics::SpawnSoundAtLocation(this, SoundBaseMorning, FVector::ZeroVector, FRotator::ZeroRotator, 1.f, 1.f, 0.f);
			else
				AudioComponentAmbienceDay->SetVolumeMultiplier(1.f);
		}
		else if (LightningLevel < 0.75 && AudioComponentAmbienceDay)
		{
			AudioComponentAmbienceDay->SetVolumeMultiplier(0.f);
		}
	}
}


void AProjectLanternGameMode::UpdateFlavorText(FString FT)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		GS->FlavorText = FT;
	}
}

void AProjectLanternGameMode::EnableEvent(int32 EventId)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		for (AActor* Objs : GS->FoundEvents)
		{
			if (AEventTriggerBox* TB = Cast<AEventTriggerBox>(Objs))
			{
				FString ToLog = FString::FromInt(TB->EventId);

				UE_LOG(LogTemp, Warning, TEXT("%s"), *ToLog);

				UE_LOG(LogTemp, Warning, TEXT("FLAG: %s"), *FString::FromInt(EventId));
				if (TB->EventId == EventId)
				{
					UE_LOG(LogTemp, Warning, TEXT("FLAGN IN!"));
					TB->Enabled = true;
				}
			}
		}
	}

}

void AProjectLanternGameMode::RemoveActor(AActor* ActorToRemove)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		GS->FoundActors.Remove(ActorToRemove);
	}
}
