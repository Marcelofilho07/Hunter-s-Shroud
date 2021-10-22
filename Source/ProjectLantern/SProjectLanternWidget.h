// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class PROJECTLANTERN_API SProjectLanternWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SProjectLanternWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString FlavorText;
};
