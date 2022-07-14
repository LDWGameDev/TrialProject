// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Actor/Actor_BaseObject.h"



/**
 * 
 */

AActor_BaseObject::AActor_BaseObject()
{
	PrimaryActorTick.bCanEverTick = true;

}



/**
 * Override functions
 */

void AActor_BaseObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActor_BaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

