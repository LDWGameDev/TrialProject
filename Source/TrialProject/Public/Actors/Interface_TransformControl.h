// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_TransformControl.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_TransformControl : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRIALPROJECT_API IInterface_TransformControl
{
	GENERATED_BODY()

public:
	virtual void IFunc_MoveToLocation(FVector p_NewLocation, float p_MoveTime) = 0;
	virtual void IFunc_RotateToRotation(FRotator p_NewRotation, float p_RotateTime) = 0;
};
