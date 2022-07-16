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
	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableBed")
		FVector m_InteractorOffsetLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableBed")
		FRotator m_InteractorOffsetRotation;
	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableBed")
		float m_InteractorTransformSnappingTime;

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
