// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectLanternHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AProjectLanternHUD::AProjectLanternHUD()
{
	// Set the crosshair texture
	FlavorText = "";
}


void AProjectLanternHUD::DrawHUD()
{
	Super::DrawHUD();

}
