// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectLanternHUD.generated.h"

UCLASS()
class AProjectLanternHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectLanternHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString FlavorText;

private:
	/** Crosshair asset pointer */

};

