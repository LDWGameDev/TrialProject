// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_InteractableObject.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_InteractableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRIALPROJECT_API IInterface_InteractableObject
{
	GENERATED_BODY()

public:
	virtual void IFunc_TriggerInteraction(AActor* p_ActorInteract) = 0;
};
