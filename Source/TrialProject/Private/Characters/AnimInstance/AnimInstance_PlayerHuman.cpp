// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstance/AnimInstance_PlayerHuman.h"

#include "Characters/Character/Character_PlayerHuman.h"



/**
 * 
 */

UAnimInstance_PlayerHuman::UAnimInstance_PlayerHuman()
{
	m_MovingSpeed = 0.0f;
	b_IsInAir = false;
}



/**
 * Override functions
 */

void UAnimInstance_PlayerHuman::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	m_CharacterPlayerHumanREF = Cast<ACharacter_PlayerHuman>(TryGetPawnOwner());
}

void UAnimInstance_PlayerHuman::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (m_CharacterPlayerHumanREF == nullptr) return;
	m_MovingSpeed = m_CharacterPlayerHumanREF->m_CurrentMovingSpeed;
	b_IsInAir = m_CharacterPlayerHumanREF->b_IsInAir;
	m_ZVelocity = m_CharacterPlayerHumanREF->GetVelocity().Z;
	if (m_CharacterPlayerHumanREF->GetCurrentState() == EPlayerState::Locomotion && !b_IsInAir && m_MovingSpeed < 30.0f)
	{
		b_ShouldDoFootIK = true;
	}
	else 
	{
		b_ShouldDoFootIK = false;
	}
}

void UAnimInstance_PlayerHuman::ResetRightHandIKAlpha(float p_BlendTime)
{
	if (m_CharacterPlayerHumanREF == nullptr) return;
	m_CharacterPlayerHumanREF->SetRightHandIKAlpha(0.0f, p_BlendTime);
}

void UAnimInstance_PlayerHuman::PickUpItem()
{
	if (m_CharacterPlayerHumanREF == nullptr) return;
	m_CharacterPlayerHumanREF->PickUpCurrentInteractableObject();
}
