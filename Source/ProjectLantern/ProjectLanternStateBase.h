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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	TArray<int32> AEventsToDoManager;

	TArray<int32> AEventsDoneManager;

	TArray<AActor*> FoundActors;

	int32 GameDay;
};
