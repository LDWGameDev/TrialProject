// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"

#include "System/Interaction/Interface_InteractionCreator.h"
#include "Characters/Interface_InputControl.h"
#include "Characters/EPlayerState.h"
#include "Actors/Interface_TransformControl.h"
#include "Character_PlayerHuman.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UAnimInstance_PlayerHuman;
class UCurveFloat;
class UDataTable;
class AActor_PickUpObject;


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
	// Float curve 
	UPROPERTY(EditDefaultsOnly, Category = "Custom PlayerHuman")
		UCurveFloat* m_CurveFloat_EaseInOutAlpha;

	UPROPERTY(EditDefaultsOnly, Category = "Custom PlayerHuman")
		UDataTable* m_DataTable_Montages;

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
	// Current holding object AActor_PickUpObject type
	UPROPERTY()
		AActor_PickUpObject* m_CurrentHoldingObject;

	const float c_JumpForce = 800.0f;

	// Timeline controls actor location
	FTimeline m_Timeline_LocationControl;
	FVector m_SavedLocation;
	FVector m_SavedNewLocation;

	// Timeline controls actor rotation
	FTimeline m_Timeline_RotationControl;
	FRotator m_SavedRotation;
	FRotator m_SavedNewRotation;

	// Timeline controls CapsuleComponent size
	FTimeline m_Timeline_CapsuleSizeControl;
	float m_SavedCapsuleRadius;
	float m_SavedNewCapsuleRadius;
	float m_SavedCapsuleHalfHeight;
	float m_SavedNewCapsuleHalfHeight;

	// Timeline controls RightHandIKAlpha in AnimInstance_PlayerHuman
	FTimeline m_Timeline_RightHandIKAlphaControl;
	float m_SavedRightHandIKAlpha;
	float m_SavedNewRightHandIKAlpha;

	EPlayerState m_CurrentState;



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
	virtual void IFunc_HandleInputAction_EndInteract() override;

	// Interface_InteractionCreator interface functions
	virtual void IFunc_CanInteractNewObject(AActor* p_NewInteractableObject) override;
	virtual void IFunc_RemoveInteractableObject(AActor* p_NewInteractableObject) override;

	// Interface_TransformControl interface functions
	virtual void IFunc_MoveToLocation(FVector p_NewLocation, float p_MoveTime) override;
	virtual void IFunc_RotateToRotation(FRotator p_NewRotation, float p_RotateTime) override;

	// Move to a new location using m_Timeline_LocationControl
	void MoveToLocation(FVector p_NewLocation, float p_BlendTime);
	
	// Rotate to a rotation using m_Timeline_RotationControl
	void RotateToRotation(FRotator p_NewRotation, float p_BlendTime);
	void RotateToFaceTarget(AActor* p_FacingTarget, float p_BlendTime);

	// Change to new capsule size using m_Timeline_CapsuleSizeControl;
	void ChangeCapsuleSize(float p_NewRadius, float p_NewHalfHeight, float p_BlendTime);

	// Find and play AnimMontage from m_DataTable_Montage
	void PlayAnimMontageFromTable(const FName& p_MontageID);

	// StateMachine functions
	void ChangeState(EPlayerState p_NewState);
	EPlayerState GetCurrentState();

	// 
	void SetRightHandIKAlpha(float p_NewAlpha, float p_BlendTime);
	void SetRightHandIKLocation(const FVector p_NewLocation);

	void PickUpCurrentInteractableObject();

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
	UFUNCTION(BlueprintCallable)
		void TestRightHandIK(FVector p_RightHandIKLocation);
};
