// Fill out your copyright notice in the Description page of Project Settings.


#include "EventTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "ProjectLanternGameMode.h"

AEventTriggerBox::AEventTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AEventTriggerBox::Event);
}

void AEventTriggerBox::BeginPlay()
{
	Super::BeginPlay();

}

void AEventTriggerBox::Event(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (Enabled)
	{
		if (OtherActor && OtherActor != this)
		{
			if (OtherActor->IsA(AProjectLanternCharacter::StaticClass()))
			{
				if (TriggerOnlyOnce)
					Enabled = false;
				GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, Rotation);

				if (ObjSound != NULL)
				{
					GetWorldTimerManager().SetTimer(TimerHandle_PlaySound, this, &AEventTriggerBox::PlayEventSound, SoundDelay, false);
				}

				if (AProjectLanternGameMode* GM = Cast<AProjectLanternGameMode>(GetWorld()->GetAuthGameMode()))
				{
					if (NextObjId != 0)
						GM->EnableObj(NextObjId);
					if (NextEventId != 0)
						GM->EnableEvent(NextEventId);
				}
			}
		}
	}
}

void AEventTriggerBox::PlayEventSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, ObjSound, GetActorLocation());
}