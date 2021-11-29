// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicObjectGun.h"
#include "ProjectLanternCharacter.h"
#include "ProjectLanternGameMode.h"

void ABasicObjectGun::Action()
{
	Super::Action();
	if (IsEnabled)
	{
		if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode())) //Should have a better implemantation...
		{
			if (AProjectLanternCharacter* PLC = Cast<AProjectLanternCharacter>(GM->MainPlayer[0]))
			{
				PLC->ToggleGun();
			}
		}
	}

}