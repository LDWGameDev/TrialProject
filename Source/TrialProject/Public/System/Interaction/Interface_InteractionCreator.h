// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_InteractionCreator.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_InteractionCreator : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRIALPROJECT_API IInterface_InteractionCreator
{
	GENERATED_BODY()

public:
	virtual void IFunc_CanInteractNewObject(AActor* p_NewInteractableObject) = 0;
	virtual void IFunc_RemoveInteractableObject(AActor* p_NewInteractableObject) = 0;
};
