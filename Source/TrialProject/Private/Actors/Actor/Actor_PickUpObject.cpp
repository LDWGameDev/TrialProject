// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_PickUpObject.h"
#include "Library/CustomMathLibrary.h"



/**
 * 
 */

AActor_PickUpObject::AActor_PickUpObject()
{

}

FVector AActor_PickUpObject::IFunc_GetInteractionLocation()
{
	return CustomMathLibrary::WorldLocationOfRelativeLocationToActor(this, m_InteractionOffsetLocation);
}
