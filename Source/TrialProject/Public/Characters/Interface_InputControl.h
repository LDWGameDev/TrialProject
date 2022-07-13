// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_InputControl.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_InputControl : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class TRIALPROJECT_API IInterface_InputControl
{
	GENERATED_BODY()

public:
	virtual void HandleInputAxis_MoveForward(float p_Value) = 0;
	virtual void HandleInputAxis_MoveRight(float p_Value) = 0;
};
