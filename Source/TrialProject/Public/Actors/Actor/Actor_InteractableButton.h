// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"

#include "Actors/Actor/Actor_BaseInteractableObject.h"
#include "Actor_InteractableButton.generated.h"


class UCurveFloat;


/**
 * 
 */
UCLASS()
class TRIALPROJECT_API AActor_InteractableButton : public AActor_BaseInteractableObject
{
	GENERATED_BODY()

/**
 * Properties
 */
public:
	// Offset location using component rotation
	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableButton")
		FVector m_OffsetInteractionLocation;

	// Offset location using component rotation
	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableButton")
		FVector m_ButtonInteractionOffsetLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableButton")
		UCurveFloat* m_CurveFloat_ButtonInteractionLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Custom InteractableButton")
		float m_ButtonInteractionTime;

protected:
private:
	// Timeline controls button interaction
	FTimeline m_Timeline_ButtonInteraction;
	FVector m_SavedButtonLocation;
	FVector m_SavedNewButtonLocation;


/**
 * Functions
 */
public:
	AActor_InteractableButton();
	virtual void Tick(float DeltaTime) override;

	// Interface_InteractableObject override functions
	virtual void IFunc_TriggerInteraction(AActor* p_ActorInteract) override;
	virtual FVector IFunc_GetInteractionLocation() override;

protected:
	virtual void BeginPlay() override;

private:
};
