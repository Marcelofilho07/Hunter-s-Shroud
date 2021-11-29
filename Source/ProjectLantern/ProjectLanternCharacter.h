// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectLanternCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AProjectLanternCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Item;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	AProjectLanternCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AProjectLanternProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* WalkGrassSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* WalkWoodSound;

	/** Sound to play each time we walk */
	class USoundBase* WalkSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class AProjectLanternHUD> MainHUD;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float SpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float TouchRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ZoomInMulti;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ZoomOutMulti;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float ZoomAmmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float GunDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float GunRange;

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoldingComponent;

	class ABasicObject* CurrentObject;

	FTimerHandle TimerHandle_HandleFadeBlack;
	FTimerHandle TimerHandle_HandleWalkSound;
	FTimerHandle TimerHandle_HandleRateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float FadeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float WalkSoundTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RateOfFireTime;

	bool IsHoldingGun;

	bool IsHoldingObj;

	bool CanFire;
	bool CanMove;
	bool CanClick;
	bool CanMakeStepSound;

	virtual void Tick(float DeltaTime) override;

	void ToggleGun();

protected:
	
	/** Interact with object. */
	void OnAction();

	/** Fire gun if holding any. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void InteractWithObj();

	void ToggleMovement();

	void ToggleCanMakeWalkingSound();

	void ToggleFire();

	float FoV;

	FTimerHandle TimerHandle_HandleZoomIn;

	FTimerHandle TimerHandle_HandleZoomOut;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

