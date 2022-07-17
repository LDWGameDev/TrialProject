// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_InteractableButton.h"
#include "Kismet/KismetMathLibrary.h"


/**
 * 
 */

AActor_InteractableButton::AActor_InteractableButton()
{
	m_ButtonInteractionTime = 1.0f;
}



/**
 * Override functions
 */

void AActor_InteractableButton::BeginPlay()
{
	Super::BeginPlay();

	// Create m_Timeline_ButtonInteraction
	FOnTimelineFloatStatic OnTimelineFloat_ButtonInteractionControl;
	OnTimelineFloat_ButtonInteractionControl.BindLambda([&](float p_Value)
		{
			m_StaticMesh_ObjectMesh_01->SetRelativeLocation(FMath::Lerp(m_SavedButtonLocation, m_SavedNewButtonLocation, p_Value));
		});
	m_Timeline_ButtonInteraction.AddInterpFloat(m_CurveFloat_ButtonInteractionLocation, OnTimelineFloat_ButtonInteractionControl);
	m_Timeline_ButtonInteraction.SetTimelineLength(1.0f);
	m_Timeline_ButtonInteraction.SetPlayRate(1.0f / m_ButtonInteractionTime);
	m_Timeline_ButtonInteraction.SetLooping(false);

	// Set timeline values
	FRotator ButtonRotator = m_StaticMesh_ObjectMesh_01->GetRelativeRotation();
	FVector AdditionalLocation = UKismetMathLibrary::GetForwardVector(ButtonRotator) * m_ButtonInteractionOffsetLocation.X + UKismetMathLibrary::GetRightVector(ButtonRotator) * m_ButtonInteractionOffsetLocation.Y + UKismetMathLibrary::GetUpVector(ButtonRotator) * m_ButtonInteractionOffsetLocation.Z;
	m_SavedButtonLocation = m_StaticMesh_ObjectMesh_01->GetRelativeLocation();
	m_SavedNewButtonLocation = m_SavedButtonLocation + AdditionalLocation;
}

void AActor_InteractableButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_Timeline_ButtonInteraction.TickTimeline(DeltaTime);
}




/**
 * Interface override functions
 */

FVector AActor_InteractableButton::IFunc_GetInteractionLocation()
{
	FRotator ButtonRotator = m_StaticMesh_ObjectMesh_01->GetComponentRotation();
	FVector AdditionalLocation = UKismetMathLibrary::GetForwardVector(ButtonRotator) * m_OffsetInteractionLocation.X + UKismetMathLibrary::GetRightVector(ButtonRotator) * m_OffsetInteractionLocation.Y + UKismetMathLibrary::GetUpVector(ButtonRotator) * m_OffsetInteractionLocation.Z;
	return m_StaticMesh_ObjectMesh_01->GetComponentLocation() + AdditionalLocation;
}

void AActor_InteractableButton::IFunc_TriggerInteraction(AActor* p_ActorInteract)
{
	Super::IFunc_TriggerInteraction(p_ActorInteract);
	m_Timeline_ButtonInteraction.PlayFromStart();
}



/**
 * Private member functions
 */
