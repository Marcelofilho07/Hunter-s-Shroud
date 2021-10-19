// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicObject.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ABasicObject::ABasicObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	IsPickable = false;
	BGravity = true;
	BHolding = false;
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetOnlyOwnerSee(false);
	VisualMesh->SetSimulatePhysics(BGravity);
	SetRootComponent(VisualMesh);

}


// Called when the game starts or when spawned
void ABasicObject::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerCamera = MyCharacter->FindComponentByClass<UCameraComponent>();

	TArray<USceneComponent*> Components;

	MyCharacter->GetComponents(Components);

	if (Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if (Comp->GetName() == "FP_Item")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}
	
}

// Called every frame
void ABasicObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABasicObject::PickUp()
{
	if (IsPickable)
	{
		BHolding = !BHolding;
		BGravity = !BGravity;
		VisualMesh->SetEnableGravity(BGravity);
		VisualMesh->SetSimulatePhysics(BHolding ? false : true);
		VisualMesh->SetCollisionEnabled(BHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);
		if (HoldingComp && BHolding)
		{
			VisualMesh->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepWorldTransform);
			SetActorLocation(HoldingComp->GetComponentLocation());
		}

		if (!BHolding)
		{
			VisualMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			//ForwardVector = PlayerCamera->GetForwardVector();
			//VisualMesh->AddForce(ForwardVector * 10 * VisualMesh->GetMass());
		}
	}
}

