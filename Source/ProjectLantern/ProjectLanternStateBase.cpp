// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLanternStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "BasicObject.h"
#include "EventTriggerBox.h"

AProjectLanternStateBase::AProjectLanternStateBase()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicObject::StaticClass(), FoundActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEventTriggerBox::StaticClass(), FoundEvents);

	LightningLevel = 0.25f;
}