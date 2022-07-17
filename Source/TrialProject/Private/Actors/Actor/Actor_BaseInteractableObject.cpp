// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_BaseInteractableObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "System/Interaction/Interface_InteractionCreator.h"
#include "Library/CustomMathLibrary.h"



/**
 * 
 */

AActor_BaseInteractableObject::AActor_BaseInteractableObject()
{
	// Actor defaults
	PrimaryActorTick.bCanEverTick = true;
	m_InteractableObjectType = EInteractableObjectType::None;

	// SphereComponent root defaults
	m_SphereComponent_BaseRootCollision_01 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent Root Collision 01"));
	m_SphereComponent_BaseRootCollision_01->SetCollisionProfileName(FName(TEXT("StaticObject")), false);
	SetRootComponent(m_SphereComponent_BaseRootCollision_01);
	RootComponent->SetMobility(EComponentMobility::Static);

	// SphereComponent interaction area defaults
	m_SphereComponent_InteractionCheck_01 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent Interaction Check 01"));
	m_SphereComponent_InteractionCheck_01->SetupAttachment(RootComponent);
	m_SphereComponent_InteractionCheck_01->SetCollisionProfileName(FName(TEXT("Trigger")), false);

	// StaticMesh defaults
	m_StaticMesh_ObjectMesh_01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Object Mesh 01"));
	m_StaticMesh_ObjectMesh_01->SetupAttachment(RootComponent);
	m_SphereComponent_BaseRootCollision_01->SetCollisionProfileName(FName(TEXT("StaticObject")), false);

	// WidgetComponent defaults
	m_WidgetComponent_InteractionDisplay_01 = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent Interaction Display 01"));
	m_WidgetComponent_InteractionDisplay_01->SetupAttachment(RootComponent);
	m_WidgetComponent_InteractionDisplay_01->SetWidgetSpace(EWidgetSpace::Screen);
	m_WidgetComponent_InteractionDisplay_01->SetDrawAtDesiredSize(true);
	m_WidgetComponent_InteractionDisplay_01->SetHiddenInGame(true);
}

void AActor_BaseInteractableObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (m_SphereComponent_InteractionCheck_01 != nullptr)
	{
		m_SphereComponent_InteractionCheck_01->OnComponentBeginOverlap.AddDynamic(this, &AActor_BaseInteractableObject::HandleOnComponentBeginOverlap_InteractionCheck_01);
		m_SphereComponent_InteractionCheck_01->OnComponentEndOverlap.AddDynamic(this, &AActor_BaseInteractableObject::HandleOnComponentExitOverlap_InteractionCheck_01);
	}
}

void AActor_BaseInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AActor_BaseInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



/**
 * Interface override functions
 */

void AActor_BaseInteractableObject::IFunc_TriggerInteraction(AActor* p_ActorInteract)
{
	m_WidgetComponent_InteractionDisplay_01->SetHiddenInGame(true);
}

EInteractableObjectType AActor_BaseInteractableObject::IFunc_GetInteractableObjectType()
{
	return m_InteractableObjectType;
}

FVector AActor_BaseInteractableObject::IFunc_GetInteractionLocation()
{
	return GetActorLocation();
}




/**
 * Protected member functions
 */

void AActor_BaseInteractableObject::HandleOnComponentBeginOverlap_InteractionCheck_01(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex, bool p_FromSweep, const FHitResult& p_SweepResult)
{
	IInterface_InteractionCreator* InteractionCreator = Cast<IInterface_InteractionCreator>(p_OtherActor);
	if (InteractionCreator != nullptr)
	{
		m_WidgetComponent_InteractionDisplay_01->SetHiddenInGame(false);
		InteractionCreator->IFunc_CanInteractNewObject(this);
		m_CurrentInteractionCreator = p_OtherActor;
	}
}

void AActor_BaseInteractableObject::HandleOnComponentExitOverlap_InteractionCheck_01(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex)
{
	IInterface_InteractionCreator* InteractionCreator = Cast<IInterface_InteractionCreator>(p_OtherActor);
	if (InteractionCreator != nullptr)
	{
		m_WidgetComponent_InteractionDisplay_01->SetHiddenInGame(true);
		InteractionCreator->IFunc_RemoveInteractableObject(this);
		if (p_OtherActor == m_CurrentInteractionCreator) m_CurrentInteractionCreator = nullptr;
	}
}

void AActor_BaseInteractableObject::TestFunction(int32 p_CommandID)
{
	switch (p_CommandID)
	{
	case 0:
	{

		break;
	}
	case 1:
	{

		break;
	}
	}
}

FVector AActor_BaseInteractableObject::WorldLocationOfOffsetLocation(FVector p_OffsetLocation)
{
	return CustomMathLibrary::WorldLocationOfRelativeLocationToActor(this, p_OffsetLocation);
}
