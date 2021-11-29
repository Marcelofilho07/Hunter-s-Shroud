// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicObject.h"
#include "BasicObjectGun.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLANTERN_API ABasicObjectGun : public ABasicObject
{
	GENERATED_BODY()
	
public:
	void Action() override;
};
