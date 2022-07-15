// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Actor/Actor_BaseInteractableObject.h"
#include "Actor_InteractableBed.generated.h"



/**
 * 
 */

UCLASS()
class TRIALPROJECT_API AActor_InteractableBed : public AActor_BaseInteractableObject
{
	GENERATED_BODY()


/**
 * Properties
 */

public:

protected:

private:



/**
 * Functions
 */

public:
	AActor_InteractableBed();

	// Interface_InteractableObject override functions
	virtual void IFunc_TriggerInteraction(AActor* p_ActorInteract) override;

protected:

private:

};
