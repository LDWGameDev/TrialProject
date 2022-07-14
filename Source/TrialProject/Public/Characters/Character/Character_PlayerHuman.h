// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "System/Interaction/Interface_InteractionCreator.h"
#include "Characters/Interface_InputControl.h"
#include "Actors/Interface_TransformControl.h"
#include "Character_PlayerHuman.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UAnimInstance_PlayerHuman;
class UCurveFloat;

/**
 * 
 */

UCLASS()
class TRIALPROJECT_API ACharacter_PlayerHuman : public ACharacter, public IInterface_InputControl, public IInterface_InteractionCreator, public IInterface_TransformControl
{
	GENERATED_BODY()


/**
 * Properties
 */
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom PlayerHuman")
		UCurveFloat* m_CurveFloat_EaseInOutAlpha;

	float m_CurrentMovingSpeed;
	bool b_IsInAir;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman Components")
		USpringArmComponent* m_SpringArm_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom PlayerHuman Components")
		UCameraComponent* m_CameraComp_01;

private:
	// AnimInstance reference
	UPROPERTY()
		UAnimInstance_PlayerHuman* m_AnimInstancePlayerHumanREF;
	// Current actor to interact with. Set and remove value using functions of Interface_InteractionCreator
	UPROPERTY()
		AActor* m_CurrentInteractableObject;

	const float c_JumpForce = 800.0f;

	// Timeline controls actor location
	FTimeline m_Timeline_LocationControl;
	FVector m_SavedLocation;
	FVector m_SavedNewLocation;

	// Timeline controls actor rotation
	FTimeline m_Timeline_RotationControl;
	FRotator m_SavedRotation;
	FRotator m_SavedNewRotation;


/**
 * Functions
 */

public:
	ACharacter_PlayerHuman();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Interface_InputControl interface functions
	virtual void IFunc_HandleInputAxis_MoveForward(float p_Value) override;
	virtual void IFunc_HandleInputAxis_MoveRight(float p_Value) override;
	virtual void IFunc_HandleInputAction_JumpStart() override;
	virtual void IFunc_HandleInputAction_Interact() override;

	// Interface_InteractionCreator interface functions
	virtual void IFunc_CanInteractNewObject(AActor* p_NewInteractableObject) override;
	virtual void IFunc_RemoveInteractableObject(AActor* p_NewInteractableObject) override;

	// Interface_TransformControl interface functions
	virtual void IFunc_MoveToLocation(FVector p_NewLocation, float p_MoveTime) override;
	virtual void IFunc_RotateToRotation(FRotator p_NewRotation, float p_RotateTime) override;

	void MoveToLocation(FVector p_NewLocation, float p_BlendTime);
	void RotateToRotation(FRotator p_NewRotation, float p_BlendTime);

protected:
	virtual void BeginPlay() override;

private:	
	// Calculates and checks for m_CurrentMovingSpeed, b_InInAir
	void CalculateMovement();

	// Create timelines, called in BeginPlay()
	void InitTimelines();
	// Tick timeliens, called in Tick()
	void TickTimelines(float p_DeltaTime);




public: 
	UFUNCTION(BlueprintCallable)
		void TestFunction(int p_CommandID);
};
