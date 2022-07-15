// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_BaseObject.generated.h"


/**
 * 
 */

UCLASS()
class TRIALPROJECT_API AActor_BaseObject : public AActor
{
	GENERATED_BODY()
	

/**
 * Functions
 */

public:	
	AActor_BaseObject();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

};
