// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Character/Character_PlayerHuman.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Characters/AnimInstance/AnimInstance_PlayerHuman.h"



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
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

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
	m_SpringArm_01->CameraLagSpeed = 10.0f;

	// CameraComponent defaults
	m_CameraComp_01 = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp 01"));
	m_CameraComp_01->SetupAttachment(m_SpringArm_01);

	// CharacterMovemmentComponent defaults
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 420.0f, 0.0f);
}



/**
 * Override functions
 */

void ACharacter_PlayerHuman::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacter_PlayerHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CalculateMovement();
}

void ACharacter_PlayerHuman::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	m_AnimInstancePlayerHumanREF = Cast<UAnimInstance_PlayerHuman>(GetMesh()->GetAnimInstance());
}





/**
 *  Interface functions
 */

void ACharacter_PlayerHuman::HandleInputAxis_MoveForward(float p_Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetForwardVector(ControlRotation), p_Value, false);
}

void ACharacter_PlayerHuman::HandleInputAxis_MoveRight(float p_Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;
	AddMovementInput(UKismetMathLibrary::GetRightVector(ControlRotation), p_Value, false);
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