// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLanternStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "BasicObject.h"

AProjectLanternStateBase::AProjectLanternStateBase()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicObject::StaticClass(), FoundActors);
	for (auto& Act : FoundActors)
	{
		if (ABasicObject* BO = Cast<ABasicObject>(Act))
		{
			AEventsToDoManager.Add(BO->ObjId);
		}
	}
}