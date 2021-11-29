// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyWildHunter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API AEnemyWildHunter : public AEnemy
{
	GENERATED_BODY()

public:
	//AEnemyWildHunter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DeathTime;

	void DestroySelf();

private:
	FTimerHandle TimerHandle_HandleDestroySelf;


	virtual void BeginPlay() override;
	
};
