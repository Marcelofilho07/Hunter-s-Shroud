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
	FString ObjMessage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	USceneComponent* HoldingComp;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool IsPickable;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Gameplay)
	bool BGravity;

	UFUNCTION()
	void PickUp();

	bool BHolding;
	

	FRotator ControlRotation;
	ACharacter* MyCharacter;
	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
