// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectLanternStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API AProjectLanternStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AProjectLanternStateBase();

	TArray<AActor*> FoundEvents;

	TArray<AActor*> FoundActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FString FlavorText;

	int32 GameDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	float LightningLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor LightningColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor FogColor;
};
