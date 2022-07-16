// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character/Character_PlayerHuman.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/FMontageToPlay.h"
#include "System/Interaction/Interface_InteractableObject.h"
#include "Characters/AnimInstance/AnimInstance_PlayerHuman.h"
#include "Actors/EInteractableObjectType.h"



/**
 * 
 */

ACharacter_PlayerHuman::ACharacter_PlayerHuman()
{
	// Character defaults
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// CapsuleComponent defaults
	GetCapsuleComponent()->InitCapsuleSize(36.0f, 96.0f);

	// SkeletalMesh defaults
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	
	// SpringArm defaults
	m_SpringArm_01 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp 01"));
	m_SpringArm_01->SetupAttachment(RootComponent);
	m_SpringArm_01->bUsePawnControlRotation = true;
	m_SpringArm_01->bInheritPitch = true;
	m_SpringArm_01->bInheritRoll = true;
	m_SpringArm_01->bInheritYaw = true;
	m_SpringArm_01->TargetArmLength = 400.0f;
	m_SpringArm_01->bEnableCameraLag = true;
	m_SpringArm_01->CameraLagSpeed = 7.0f;

	// CameraComponent defaults
	m_CameraComp_01 = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp 01"));
	m_CameraComp_01->SetupAttachment(m_SpringArm_01);

	// CharacterMovemmentComponent defaults
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 420.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.4f;
}




/**
 * Override functions
 */

void ACharacter_PlayerHuman::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	m_AnimInstancePlayerHumanREF = Cast<UAnimInstance_PlayerHuman>(GetMesh()->GetAnimInstance());
}

void ACharacter_PlayerHuman::BeginPlay()
{
	Super::BeginPlay();
	InitTimelines();
	ChangeState(EPlayerState::Locomotion);
}

void ACharacter_PlayerHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateMovement();
	TickTimelines(DeltaTime);
}





/**
 *  Interface override functions
 */

void ACharacter_PlayerHuman::IFunc_HandleInputAxis_MoveForward(float p_Value)
{
	if (m_CurrentState != EPlayerState::Locomotion) return;
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetForwardVector(ControlRotation), p_Value, false);
}

void ACharacter_PlayerHuman::IFunc_HandleInputAxis_MoveRight(float p_Value)
{
	if (m_CurrentState != EPlayerState::Locomotion) return;
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRotation), p_Value, false);
}

void ACharacter_PlayerHuman::IFunc_HandleInputAction_JumpStart()
{
	if (m_CurrentState != EPlayerState::Locomotion) return;
	LaunchCharacter(FVector(0.0f, 0.0f, c_JumpForce), false, true);
}

void ACharacter_PlayerHuman::IFunc_HandleInputAction_Interact()
{
	if (m_CurrentState != EPlayerState::Locomotion) return;
	IInterface_InteractableObject* InteractableObject = Cast<IInterface_InteractableObject>(m_CurrentInteractableObject);
	if (InteractableObject != nullptr)
	{
		InteractableObject->IFunc_TriggerInteraction(this);

		// Delay display AnimMontage
		FTimerHandle TimerHandle_DelayPlayAnimMontage;

		switch (InteractableObject->IFunc_GetInteractableObjectType())
		{
		case EInteractableObjectType::Bed_01:
		{
			ChangeState(EPlayerState::Sleeping);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayPlayAnimMontage, [&]()
				{
					PlayAnimMontageFromTable(FName(TEXT("GetOnBed_01")));
					GetCharacterMovement()->SetMovementMode(MOVE_Flying);
				}, 0.25f, false);
			break;
		}
		case EInteractableObjectType::Bed_02:
		{
			ChangeState(EPlayerState::Sleeping);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayPlayAnimMontage, [&]()
				{
					PlayAnimMontageFromTable(FName(TEXT("GetOnBed_02")));
					GetCharacterMovement()->SetMovementMode(MOVE_Flying);
				}, 0.25f, false);
			break;
		}
		case EInteractableObjectType::Chair_01:
		{
			ChangeState(EPlayerState::Sitting);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayPlayAnimMontage, [&]()
				{
					PlayAnimMontageFromTable(FName(TEXT("SitOnChair_01")));
				}, 0.25f, false);
			break;
		}
		case EInteractableObjectType::Chair_02:
		{
			ChangeState(EPlayerState::Sitting);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayPlayAnimMontage, [&]()
				{
					PlayAnimMontageFromTable(FName(TEXT("SitOnChair_02")));
				}, 0.25f, false);
			break;
		}
		case EInteractableObjectType::Chair_03:
		{
			ChangeState(EPlayerState::Sitting);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_DelayPlayAnimMontage, [&]()
				{
					PlayAnimMontageFromTable(FName(TEXT("SitOnChair_03")));
				}, 0.25f, false);
			break;
		}
		}
	}
}

void ACharacter_PlayerHuman::IFunc_HandleInputAction_EndInteract()
{
	switch (m_CurrentState)
	{
	case EPlayerState::Sleeping:
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		PlayAnimMontageFromTable(FName(TEXT("SleepingGetUp")));
		ChangeState(EPlayerState::Locomotion);
		break;
	}
	case EPlayerState::Sitting:
	{
		PlayAnimMontageFromTable(FName(TEXT("StandUpFromChair")));
		ChangeState(EPlayerState::Locomotion);
		break;
	}
	}
}

void ACharacter_PlayerHuman::IFunc_CanInteractNewObject(AActor* p_NewInteractableObject)
{
	if (p_NewInteractableObject != nullptr) m_CurrentInteractableObject = p_NewInteractableObject;
}

void ACharacter_PlayerHuman::IFunc_RemoveInteractableObject(AActor* p_NewInteractableObject)
{
	if (m_CurrentInteractableObject == p_NewInteractableObject) m_CurrentInteractableObject = nullptr;
}

void ACharacter_PlayerHuman::IFunc_MoveToLocation(FVector p_NewLocation, float p_MoveTime)
{
	MoveToLocation(p_NewLocation, p_MoveTime);
}

void ACharacter_PlayerHuman::IFunc_RotateToRotation(FRotator p_NewRotation, float p_RotateTime)
{
	RotateToRotation(p_NewRotation, p_RotateTime);
}




/**
 * Public member functions
 */

void ACharacter_PlayerHuman::MoveToLocation(FVector p_NewLocation, float p_BlendTime)
{
	if (m_CurveFloat_EaseInOutAlpha == nullptr) return;
	if (p_BlendTime <= 0)
	{
		m_SavedLocation = p_NewLocation;
		m_SavedNewLocation = p_NewLocation;
		SetActorLocation(p_NewLocation);
	}
	else
	{
		m_SavedLocation = GetActorLocation();
		m_SavedNewLocation = p_NewLocation;
		m_Timeline_LocationControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_LocationControl.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::RotateToRotation(FRotator p_NewRotation, float p_BlendTime)
{
	if (m_CurveFloat_EaseInOutAlpha == nullptr) return;
	if (p_BlendTime <= 0)
	{
		m_SavedRotation = p_NewRotation;
		m_SavedNewRotation = p_NewRotation;
		SetActorRotation(p_NewRotation);
	}
	else
	{
		m_SavedRotation = GetActorRotation();
		m_SavedNewRotation = p_NewRotation;
		m_Timeline_RotationControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_RotationControl.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::ChangeCapsuleSize(float p_NewRadius, float p_NewHalfHeight, float p_BlendTime)
{
	if (p_NewHalfHeight <= 0.0f || p_NewHalfHeight < p_NewRadius) return;
	if (p_BlendTime <= 0.0f)
	{
		m_SavedCapsuleRadius = p_NewRadius;
		m_SavedNewCapsuleRadius = p_NewRadius;
		m_SavedCapsuleHalfHeight = p_NewHalfHeight;
		m_SavedNewCapsuleHalfHeight = p_NewHalfHeight;
		GetCapsuleComponent()->SetCapsuleSize(p_NewRadius, p_NewHalfHeight, true);
	}
	else
	{
		GetCapsuleComponent()->GetUnscaledCapsuleSize(m_SavedCapsuleRadius, m_SavedCapsuleHalfHeight);
		m_SavedNewCapsuleRadius = p_NewRadius;
		m_SavedNewCapsuleHalfHeight = p_NewHalfHeight;
		m_Timeline_CapsuleSizeControl.SetPlayRate(1.0f / p_BlendTime);
		m_Timeline_CapsuleSizeControl.PlayFromStart();
	}
}

void ACharacter_PlayerHuman::PlayAnimMontageFromTable(const FName& p_MontageID)
{
	if (m_DataTable_Montages == nullptr) return;
	FMontageToPlay* MontageStruct = m_DataTable_Montages->FindRow<FMontageToPlay>(p_MontageID, "", true);
	if (MontageStruct == nullptr || MontageStruct->m_AnimMontage == nullptr) return;
	PlayAnimMontage(MontageStruct->m_AnimMontage);
}

void ACharacter_PlayerHuman::ChangeState(EPlayerState p_NewState)
{
	m_CurrentState = p_NewState;
}

EPlayerState ACharacter_PlayerHuman::GetCurrentState()
{
	return m_CurrentState;
}






/**
 * Private member functions
 */

void ACharacter_PlayerHuman::CalculateMovement()
{
	m_CurrentMovingSpeed = GetVelocity().Size();
	if (GetCharacterMovement() != nullptr) b_IsInAir = GetCharacterMovement()->IsFalling();
	else b_IsInAir = false;
}

void ACharacter_PlayerHuman::InitTimelines()
{
	if (m_CurveFloat_EaseInOutAlpha == nullptr) return;

	// Create m_Timeline_LocationControl
	FOnTimelineFloatStatic OnTimelineFloat_LocationControl_01;
	OnTimelineFloat_LocationControl_01.BindLambda([&](float p_Value)
		{
			SetActorLocation(FMath::Lerp(m_SavedLocation, m_SavedNewLocation, p_Value), true);
		});
	m_Timeline_LocationControl.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineFloat_LocationControl_01);
	m_Timeline_LocationControl.SetTimelineLength(1.0f);
	m_Timeline_LocationControl.SetLooping(false);

	// Create m_Timeline_RotationControl
	FOnTimelineFloatStatic OnTimelineFloat_RotationControl;
	OnTimelineFloat_RotationControl.BindLambda([&](float p_Value)
		{
			SetActorRotation(FMath::Lerp(m_SavedRotation, m_SavedNewRotation, p_Value));
		});
	m_Timeline_RotationControl.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineFloat_RotationControl);
	m_Timeline_RotationControl.SetTimelineLength(1.0f);
	m_Timeline_RotationControl.SetLooping(false);

	// Create m_Timeline_CapsuleSizeControl
	FOnTimelineFloatStatic OnTimelineFloat_CapsuleSizeControl_01;
	OnTimelineFloat_CapsuleSizeControl_01.BindLambda([&](float p_Value)
		{
			if (GetCapsuleComponent() != nullptr)
			{
				float CapsuleRadius = FMath::Lerp(m_SavedCapsuleRadius, m_SavedNewCapsuleRadius, p_Value);
				float CapsuleHalfHeight = FMath::Lerp(m_SavedCapsuleHalfHeight, m_SavedNewCapsuleHalfHeight, p_Value);
				GetCapsuleComponent()->SetCapsuleSize(CapsuleRadius, CapsuleHalfHeight, true);
			}
		});
	m_Timeline_CapsuleSizeControl.AddInterpFloat(m_CurveFloat_EaseInOutAlpha, OnTimelineFloat_CapsuleSizeControl_01);
	m_Timeline_CapsuleSizeControl.SetTimelineLength(1.0f);
	m_Timeline_CapsuleSizeControl.SetLooping(false);
}

void ACharacter_PlayerHuman::TickTimelines(float p_DeltaTime)
{
	m_Timeline_LocationControl.TickTimeline(p_DeltaTime);
	m_Timeline_RotationControl.TickTimeline(p_DeltaTime);
	m_Timeline_CapsuleSizeControl.TickTimeline(p_DeltaTime);
}












void ACharacter_PlayerHuman::TestFunction(int p_CommandID)
{
	switch (p_CommandID)
	{
	case 0:
	{
		ChangeCapsuleSize(10.0f, 96.0f, 0.5f);
		break;
	}
	case 1:
	{
		ChangeCapsuleSize(38.0f, 96.0f, 0.5f);
		break;
	}
	}
}
