// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Characters/Interface_InputControl.h"
#include "Character_PlayerHuman.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UAnimInstance_PlayerHuman;

/**
 * 
 */

UCLASS()
class TRIALPROJECT_API ACharacter_PlayerHuman : public ACharacter, public IInterface_InputControl
{
	GENERATED_BODY()


/**
 * Properties
 */
	
public:
	float m_CurrentMovingSpeed;
	bool b_IsInAir;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman Components")
		USpringArmComponent* m_SpringArm_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman Components")
		UCameraComponent* m_CameraComp_01;
private:
	UPROPERTY()
		UAnimInstance_PlayerHuman* m_AnimInstancePlayerHumanREF;



/**
 * Functions
 */

public:
	ACharacter_PlayerHuman();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Interface_InputControl interface functions
	void HandleInputAxis_MoveForward(float p_Value) override;
	void HandleInputAxis_MoveRight(float p_Value) override;

protected:
	virtual void BeginPlay() override;

private:	
	// Calculates and checks for m_CurrentMovingSpeed, b_InInAir
	void CalculateMovement();
};
