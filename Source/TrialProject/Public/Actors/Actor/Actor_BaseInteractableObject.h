// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Actors/Actor/Actor_BaseObject.h"
#include "System/Interaction/Interface_InteractableObject.h"
#include "Actors/EInteractableObjectType.h"
#include "Actor_BaseInteractableObject.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;

/**
 * 
 */

UCLASS()
class TRIALPROJECT_API AActor_BaseInteractableObject : public AActor_BaseObject, public IInterface_InteractableObject
{
	GENERATED_BODY()

/**
 * Properties
 */

public:
	UPROPERTY(EditDefaultsOnly, Category = "Custom BaseInteractableObject")
		EInteractableObjectType m_InteractableObjectType;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom BaseInteractableObject Components")
		USphereComponent* m_SphereComponent_BaseRootCollision_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom BaseInteractableObject Components")
		USphereComponent* m_SphereComponent_InteractionCheck_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom BaseInteractableObject Components")
		UStaticMeshComponent* m_StaticMesh_ObjectMesh_01;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom BaseInteractableObject Components")
		UWidgetComponent* m_WidgetComponent_InteractionDisplay_01;

	UPROPERTY()
		AActor* m_CurrentInteractionCreator;

private:



/**
 * Function
 */

public:
	AActor_BaseInteractableObject();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Interface_InteractableObject override functions
	virtual void IFunc_TriggerInteraction(AActor* p_ActorInteract) override;
	virtual EInteractableObjectType IFunc_GetInteractableObjectType() override;
	virtual FVector IFunc_GetInteractionLocation() override;

protected:
	virtual void BeginPlay() override;
	
	// m_SphereComponent_InteractionCheck_01 OnComponentBegineOverlap binding function
	UFUNCTION()
		virtual void HandleOnComponentBeginOverlap_InteractionCheck_01(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex, bool p_FromSweep, const FHitResult& p_SweepResult);
	
	// m_SphereComponent_InteractionCheck_01 OnComponentBegineOverlap binding function
	UFUNCTION()
		virtual void HandleOnComponentExitOverlap_InteractionCheck_01(UPrimitiveComponent* p_OverlappedComponent, AActor* p_OtherActor, UPrimitiveComponent* p_OtherComp, int32 p_OtherBodyIndex);

private:






public:
	UFUNCTION(BlueprintCallable)
		void TestFunction(int32 p_CommandID);
	UFUNCTION(BlueprintPure, BlueprintCallable)
		FVector WorldLocationOfOffsetLocation(FVector p_OffsetLocation);
};
