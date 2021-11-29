// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectLanternInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API UProjectLanternInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UProjectLanternInstance();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	bool IsEndGame;

	void ToggleEndGame();
};
