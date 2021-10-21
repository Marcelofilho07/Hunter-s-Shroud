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

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	UStaticMeshComponent* VisualMesh2;

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
	bool IsTeleport;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	FVector TeleportDestination;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsEnabled;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool ScreenFadesToBlackAfterAction;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	int ObjId;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	int NextTaskObjId;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool BGravity;

	bool BHolding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float TeleportDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ChangeDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float DestroyDelay;

	FTimerHandle TimerHandle_HandleTeleport;
	FTimerHandle TimerHandle_HandleChange;
	FTimerHandle TimerHandle_HandleDestroy;

	FRotator ControlRotation;
	ACharacter* MyCharacter;
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

	UFUNCTION()
	void Action();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Teleport();

	void ChangeMesh();

	void DestroySelf();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
