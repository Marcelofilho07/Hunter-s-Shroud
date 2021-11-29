// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLanternInstance.h"

UProjectLanternInstance::UProjectLanternInstance()
{
	IsEndGame = false;
}

void UProjectLanternInstance::ToggleEndGame()
{
	IsEndGame = !IsEndGame;
}
