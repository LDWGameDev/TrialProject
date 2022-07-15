// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Interface_GameplayTagControl.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_GameplayTagControl : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRIALPROJECT_API IInterface_GameplayTagControl
{
	GENERATED_BODY()

public:
	virtual const FGameplayTagContainer& IFunc_GetMainTagContainer() = 0;
};
