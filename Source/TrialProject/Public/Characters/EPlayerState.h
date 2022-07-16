// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EPlayerState.generated.h"


/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Locomotion			UMETA(DisplayName = "Locomotion"), 
	Sleeping			UMETA(DisplayName = "Sleeping"),
	Sitting				UMETA(DisplayName = "Sitting")
};
