// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWildHunter.h"

//AEnemyWildHunter::AEnemyWildHunter();

void AEnemyWildHunter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_HandleDestroySelf, this, &AEnemyWildHunter::DestroySelf, DeathTime, false);
}

void AEnemyWildHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (GetActorRightVector() * (Speed * DeltaTime));
	FRotator NewRotation = GetActorRotation();
	if (Speed == 0)
	{
		float DeltaRotation = DeltaTime * TurnRate;
		NewRotation.Yaw += DeltaRotation;
	}
	SetActorLocationAndRotation(NewLocation, NewRotation, true);
}

void AEnemyWildHunter::DestroySelf()
{
	Destroy();
}