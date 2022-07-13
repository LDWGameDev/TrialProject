// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Characters/Interface_InputControl.h"
#include "PlayerController_PlayerHuman.generated.h"

/**
 * 
 */
UCLASS()
class TRIALPROJECT_API APlayerController_PlayerHuman : public APlayerController
{
	GENERATED_BODY()


/**
 * Properties
 */

public:
	float m_MouseSensitive;
protected:

private:
	// Current controlled character's interface Interface_InputControl
	IInterface_InputControl* m_CharacterInputControlInterfaceREF;


/**
 * Functions
 */

public:
	APlayerController_PlayerHuman();
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	// Handles player inputs
	void HandleInputAxis_MoveForward(float p_Value);
	void HandleInputAxis_MoveRight(float p_Value);
	void HandleInputAxis_LookUp(float p_Value);
	void HandleInputAxis_LookRight(float p_Value);

	// Handles OnPossess and OnUnPossess
	void HandleOnPossess(APawn* p_PossessedPawn);
	void HandleOnUnpossess();
};
