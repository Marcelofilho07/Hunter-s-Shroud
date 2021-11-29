// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TriggerBox.h"
#include "EnemyPrey.h"
#include "ProjectLanternCharacter.h"
#include "EventTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API AEventTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<AActor> ActorToSpawn;

public:
	AEventTriggerBox();

	UFUNCTION()
	void Event(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	int32 EventId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	bool TriggerOnlyOnce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	bool Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	AActor* Lights;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	class USoundBase* ObjSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	float SoundDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	int32 NextObjId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	int32 NextEventId;

	void PlayEventSound();

	FTimerHandle TimerHandle_PlaySound;

};
