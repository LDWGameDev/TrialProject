// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FMontageToPlay.generated.h"


class UAnimMontage;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMontageToPlay : public FTableRowBase
{
	GENERATED_BODY()

	FORCEINLINE FMontageToPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName m_MontageID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString m_MontageDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* m_AnimMontage;
};

FORCEINLINE FMontageToPlay::FMontageToPlay() : m_MontageID(FName(TEXT(""))), m_MontageDescription(TEXT("No Description")), m_AnimMontage(nullptr) {}
