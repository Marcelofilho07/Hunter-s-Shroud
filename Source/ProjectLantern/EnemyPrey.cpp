// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPrey.h"
#include "ProjectLanternGameMode.h"
#include "Math/UnrealMathUtility.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


void AEnemyPrey::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_HandleToggleMovement, this, &AEnemyPrey::ToggleMovement, (FMath::RandRange(MinMovementTime, MaxMovementTime)), false);
	if (FireSound != NULL)
	{
		AudioComponent = UGameplayStatics::SpawnSoundAtLocation(this, FireSound, GetActorLocation(), FRotator::ZeroRotator, 1.f, 1.f, 0.f, FireAttenuation);
	}
}

void AEnemyPrey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement(DeltaTime);


	if (HitPoints <= 0)
	{
		AudioComponent->SetActive(false);
		ChangeAmbienceOnDeath();
		this->Destroy();
	}

}

void AEnemyPrey::ChangeAmbienceOnDeath()
{
	if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->ChangeAmbience(LightningLevel, LightningColor, FogColor);
		GM->EnableEvent(EventToEnableAfterDeath);
	}
}

void AEnemyPrey::Movement(float DeltaTime)
{
	FVector NewLocation = GetActorLocation() + (GetActorUpVector() * (Speed * DeltaTime));
	FRotator NewRotation = GetActorRotation();
	if (Speed == 0)
	{
		float DeltaRotation = DeltaTime * TurnRate;
		NewRotation.Yaw += DeltaRotation;
	}
	SetActorLocationAndRotation(NewLocation, NewRotation, true);
}

void AEnemyPrey::ToggleMovement()
{
	if (Speed == 0)
		Speed = FMath::RandRange(MinWalkingSpeed, MaxWalkingSpeed);
	else
	{
		Speed = 0;
		TurnRate = FMath::RandRange(-MinMaxTurnRate, MinMaxTurnRate);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_HandleToggleMovement, this, &AEnemyPrey::ToggleMovement, (FMath::RandRange(MinMovementTime, MaxMovementTime)), false);
}