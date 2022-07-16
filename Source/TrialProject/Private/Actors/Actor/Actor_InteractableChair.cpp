// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_InteractableChair.h"
#include "Actors/Interface_TransformControl.h"
#include "Kismet/KismetMathLibrary.h"

#include "Library/CustomMathLibrary.h"



/**
 * 
 */
AActor_InteractableChair::AActor_InteractableChair()
{
	m_InteractorTransformSnappingTime = 0.25f;
}



/**
 * Interface override functions
 */

void AActor_InteractableChair::IFunc_TriggerInteraction(AActor* p_ActorInteract)
{
	Super::IFunc_TriggerInteraction(p_ActorInteract);
	IInterface_TransformControl* InteractorTransformControl = Cast<IInterface_TransformControl>(p_ActorInteract);
	if (InteractorTransformControl != nullptr)
	{
		FVector NewLocation = CustomMathLibrary::WorldLocationOfRelativeLocationToActor(this, m_InteractorOffsetLocation);
		FRotator NewRotator = UKismetMathLibrary::ComposeRotators(GetActorRotation(), m_InteractorOffsetRotation);
		InteractorTransformControl->IFunc_MoveToLocation(NewLocation, m_InteractorTransformSnappingTime);
		InteractorTransformControl->IFunc_RotateToRotation(NewRotator, m_InteractorTransformSnappingTime);
	}
}
