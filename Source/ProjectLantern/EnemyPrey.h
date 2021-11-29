// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemyPrey.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API AEnemyPrey : public AEnemy
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	USoundAttenuation* FireAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	float LightningLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor LightningColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor FogColor;

	void ChangeAmbienceOnDeath();

	void Movement(float DeltaTime);

	void ToggleMovement();

	UAudioComponent* AudioComponent;

	FTimerHandle TimerHandle_HandleToggleMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxMovementTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MinMovementTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxWalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MinWalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MinMaxTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 EventToEnableAfterDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	bool IsWalking = false;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
