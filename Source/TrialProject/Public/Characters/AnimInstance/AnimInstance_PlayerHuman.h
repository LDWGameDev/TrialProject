// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_PlayerHuman.generated.h"


class ACharacter_PlayerHuman;

/**
 * 
 */
UCLASS()
class TRIALPROJECT_API UAnimInstance_PlayerHuman : public UAnimInstance
{
	GENERATED_BODY()
	
	
/**
 * Properties
 */

public:
	UPROPERTY(BlueprintReadOnly, Category = "Custom AnimInstancePlayerHuman")
		float m_MovingSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "Custom AnimInstancePlayerHuman")
		bool b_IsInAir;
	UPROPERTY(BlueprintReadOnly, Category = "Custom AnimInstancePlayerHuman")
		float m_ZVelocity;
	UPROPERTY(BlueprintReadOnly, Category = "Custom AnimInstancePlayerHuman")
		bool b_ShouldDoFootIK;
protected:

private:
	ACharacter_PlayerHuman* m_CharacterPlayerHumanREF;



/**
 * Functions
 */

public:
	UAnimInstance_PlayerHuman();
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds);
protected:

private:
};
