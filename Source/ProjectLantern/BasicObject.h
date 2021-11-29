// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicObject.generated.h"

class UCameraComponent;
class ACharacter;

UCLASS()
class PROJECTLANTERN_API ABasicObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicObject();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Mesh")
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Mesh")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	FString ObjMessage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	USceneComponent* HoldingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* ObjSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* ObjAnimation;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsDestroyedAfterUse;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsChangeVisualMeshAfterUse;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsDisabledAfterUse;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsTeleport;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsChangeAmbience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	float LightningLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor LightningColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Events)
	FColor FogColor;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	FVector TeleportDestination;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsEnabled;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsEndGame;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)	
	bool ScreenFadesToBlackAfterAction;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	int ObjId;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	int NextObjId;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	int NextEventId;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool BGravity;

	bool BHolding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float TeleportDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ChangeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DestroyDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float AmbienceDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float EndGameDelay;

	FTimerHandle TimerHandle_HandleTeleport;
	FTimerHandle TimerHandle_HandleChange;
	FTimerHandle TimerHandle_HandleDestroy;
	FTimerHandle TimerHandle_HandleAmbience;

	FRotator ControlRotation;
	ACharacter* MyCharacter;
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;


	UFUNCTION()
	virtual void Action();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Teleport();

	void ChangeMesh();

	void ChangeAmbience();

	void DestroySelf();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SwapLevel();

};
