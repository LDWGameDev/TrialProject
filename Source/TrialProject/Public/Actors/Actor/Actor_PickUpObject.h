// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Actor/Actor_BaseInteractableObject.h"
#include "Actor_PickUpObject.generated.h"

/**
 * 
 */
UCLASS()
class TRIALPROJECT_API AActor_PickUpObject : public AActor_BaseInteractableObject
{
	GENERATED_BODY()


/**
 * Properties
 */
public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom PickUpObject")
		FVector m_InteractionOffsetLocation;

protected:
private:



/**
 * Functions
 */
public:
	AActor_PickUpObject();

	// Interface_InteractableObject functions
	virtual FVector IFunc_GetInteractionLocation() override;

protected:
private:

};
