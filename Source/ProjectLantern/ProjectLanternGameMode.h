// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "ProjectLanternGameMode.generated.h"

UCLASS(minimalapi)
class AProjectLanternGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectLanternGameMode();

	void EnableObj(int32 NextTaskId);

	void FadeScreen();

	void ChangeAmbience(float LightningLevel, FColor LightningColor, FColor FogColor);

	void UpdateFlavorText(FString FT);

	void EnableEvent(int32 EventId);

	void RemoveActor(AActor* ActorToRemove);

	TArray<AActor*> MainPlayer;

	USoundBase* SoundBaseMorning;
	USoundBase* SoundBaseNight;
	USoundBase* SoundBaseWhisperingNight;
	UAudioComponent* AudioComponentAmbienceDay;
	UAudioComponent* AudioComponentAmbienceNight;
	UAudioComponent* AudioComponentAmbienceWhisperingNight;
};



