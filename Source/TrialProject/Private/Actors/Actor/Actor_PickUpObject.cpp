// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_PickUpObject.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Library/CustomMathLibrary.h"



/**
 * 
 */

AActor_PickUpObject::AActor_PickUpObject()
{
	m_SphereComponent_BaseRootCollision_01->SetSimulatePhysics(true);
	m_SphereComponent_BaseRootCollision_01->SetCollisionProfileName(FName(TEXT("DynamicObject")));
	m_StaticMesh_ObjectMesh_01->SetCollisionProfileName(FName(TEXT("DynamicObject")));
}

FVector AActor_PickUpObject::IFunc_GetInteractionLocation()
{
	return CustomMathLibrary::WorldLocationOfRelativeLocationToActor(this, m_InteractionOffsetLocation);
}



/**
 * Public member functions
 */

void AActor_PickUpObject::EnablePickingUp()
{
	m_SphereComponent_BaseRootCollision_01->SetSimulatePhysics(false);
	m_SphereComponent_BaseRootCollision_01->SetCollisionProfileName(FName(TEXT("NoCollision")));
	m_StaticMesh_ObjectMesh_01->SetCollisionProfileName(FName(TEXT("NoCollision")));
}

void AActor_PickUpObject::DisablePickingUp()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	m_SphereComponent_BaseRootCollision_01->SetSimulatePhysics(true);
	m_SphereComponent_BaseRootCollision_01->SetCollisionProfileName(FName(TEXT("DynamicObject")));
	m_StaticMesh_ObjectMesh_01->SetCollisionProfileName(FName(TEXT("DynamicObject")));
}
