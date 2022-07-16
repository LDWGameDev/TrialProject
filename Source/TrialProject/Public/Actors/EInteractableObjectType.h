// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EInteractableObjectType.generated.h"


/**
 * 
 */

UENUM(BlueprintType)
enum class EInteractableObjectType : uint8
{
	None			UMETA(DisplayName = "None"),
	Bed_01			UMETA(DisplayName = "Bed_01"),
	Bed_02			UMETA(DisplayName = "Bed_02"),
	Chair_01		UMETA(DisplayName = "Chair_01"),
	Chair_02		UMETA(DisplayName = "Chair_02"),
	Chair_03		UMETA(DisplayName = "Chair_03"),
	Button			UMETA(DisplayName = "Button"),
	PickUp			UMETA(DisplayName = "PickUp")
};
