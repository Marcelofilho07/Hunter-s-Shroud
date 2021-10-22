// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectLanternGameMode.h"
#include "ProjectLanternStateBase.h"
#include "ProjectLanternHUD.h"
#include "ProjectLanternCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BasicObject.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "EngineUtils.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

AProjectLanternGameMode::AProjectLanternGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectLanternHUD::StaticClass();

}

void AProjectLanternGameMode::CompleteTask(int32 TaskId, int32 NextTaskId)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		GS->AEventsDoneManager.Add(TaskId);

		for (AActor* Objs : GS->FoundActors)
		{
			if (ABasicObject* BO = Cast<ABasicObject>(Objs))
			{
				if (BO->ObjId == NextTaskId)
				{
					BO->IsEnabled = true;
				}
				if (BO->ObjId == TaskId)
				{
					BO->IsEnabled = false;
				}
			}
		}
	}
}

void AProjectLanternGameMode::FadeScreen()
{
	for (TActorIterator<class ALevelSequenceActor> it(GetWorld()); it; ++it)
	{
		ALevelSequenceActor* lsa = *it;

		if (lsa->GetName() == TEXT("FadeBlack"))
			lsa->SequencePlayer->Play();
	}
}


void AProjectLanternGameMode::UpdateFlavorText(FString FT)
{
	if (AProjectLanternStateBase* GS = Cast<AProjectLanternStateBase>(GameState))
	{
		GS->FlavorText = FT;
	}
}

