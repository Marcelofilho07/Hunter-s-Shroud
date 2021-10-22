// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectLanternGameMode.generated.h"

UCLASS(minimalapi)
class AProjectLanternGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectLanternGameMode();

	void CompleteTask(int32 TaskId, int32 NextTaskId);

	void FadeScreen();

	void UpdateFlavorText(FString FT);

};



