// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/PlayerController_PlayerHuman.h"




/**
 * 
 */

APlayerController_PlayerHuman::APlayerController_PlayerHuman()
{
	m_MouseSensitive = 0.5f;
}



/**
 * Override functions
 */

void APlayerController_PlayerHuman::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent == nullptr) return;
	InputComponent->BindAxis(FName(TEXT("MoveForward")), this, &APlayerController_PlayerHuman::HandleInputAxis_MoveForward);
	InputComponent->BindAxis(FName(TEXT("MoveRight")), this, &APlayerController_PlayerHuman::HandleInputAxis_MoveRight);
	InputComponent->BindAxis(FName(TEXT("LookUp")), this, &APlayerController_PlayerHuman::HandleInputAxis_LookUp);
	InputComponent->BindAxis(FName(TEXT("LookRight")), this, &APlayerController_PlayerHuman::HandleInputAxis_LookRight);
	InputComponent->BindAction(FName(TEXT("Jump")), EInputEvent::IE_Pressed, this, &APlayerController_PlayerHuman::HandleInputAction_JumpStart);
	InputComponent->BindAction(FName(TEXT("Interact")), EInputEvent::IE_Pressed, this, &APlayerController_PlayerHuman::HandleInputAction_Interact);
	InputComponent->BindAction(FName(TEXT("EndInteract")), EInputEvent::IE_Pressed, this, &APlayerController_PlayerHuman::HandleInputAction_EndInteract);
}

void APlayerController_PlayerHuman::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	HandleOnPossess(aPawn);
}

void APlayerController_PlayerHuman::OnUnPossess()
{
	Super::OnUnPossess();
	HandleOnUnpossess();
}




/**
 * Private member functions
 */

void APlayerController_PlayerHuman::HandleInputAxis_MoveForward(float p_Value)
{
	if (m_CharacterInputControlInterfaceREF != nullptr) m_CharacterInputControlInterfaceREF->IFunc_HandleInputAxis_MoveForward(p_Value);
}

void APlayerController_PlayerHuman::HandleInputAxis_MoveRight(float p_Value)
{
	if (m_CharacterInputControlInterfaceREF != nullptr) m_CharacterInputControlInterfaceREF->IFunc_HandleInputAxis_MoveRight(p_Value);
}

void APlayerController_PlayerHuman::HandleInputAxis_LookUp(float p_Value)
{
	AddPitchInput(p_Value * m_MouseSensitive);
}

void APlayerController_PlayerHuman::HandleInputAxis_LookRight(float p_Value)
{
	AddYawInput(p_Value * m_MouseSensitive);
}

void APlayerController_PlayerHuman::HandleInputAction_JumpStart()
{
	if (m_CharacterInputControlInterfaceREF != nullptr) m_CharacterInputControlInterfaceREF->IFunc_HandleInputAction_JumpStart();
}

void APlayerController_PlayerHuman::HandleInputAction_Interact()
{
	if (m_CharacterInputControlInterfaceREF != nullptr) m_CharacterInputControlInterfaceREF->IFunc_HandleInputAction_Interact();
}

void APlayerController_PlayerHuman::HandleInputAction_EndInteract()
{
	if (m_CharacterInputControlInterfaceREF != nullptr) m_CharacterInputControlInterfaceREF->IFunc_HandleInputAction_EndInteract();
}

void APlayerController_PlayerHuman::HandleOnPossess(APawn* p_PossessedPawn)
{
	m_CharacterInputControlInterfaceREF = Cast<IInterface_InputControl>(p_PossessedPawn);
}

void APlayerController_PlayerHuman::HandleOnUnpossess()
{
	m_CharacterInputControlInterfaceREF = nullptr;
}
