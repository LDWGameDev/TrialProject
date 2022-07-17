// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/CustomMathLibrary.h"
#include "Kismet/KismetMathLibrary.h"


/**
 * 
 */

float CustomMathLibrary::TwoVectorsAngle_Degrees180(FVector p_VectorFrom, FVector p_VectorTo)
{
	if (UKismetMathLibrary::Vector_IsNearlyZero(p_VectorFrom, 0.01f) || UKismetMathLibrary::Vector_IsNearlyZero(p_VectorTo, 0.01f)) return 0.0f;

	p_VectorFrom.Normalize();
	p_VectorTo.Normalize();
	float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(p_VectorFrom, p_VectorTo)));
	Angle = ((FVector::CrossProduct(p_VectorFrom, p_VectorTo)).Z > 0) ? Angle : -Angle;
	return Angle;
}

FVector CustomMathLibrary::WorldLocationOfRelativeLocationToActor(const AActor* p_PivotActor, const FVector& p_RelativeLocation)
{
	if (p_PivotActor == nullptr) return FVector::ZeroVector;
	FVector AdditionLocation = p_RelativeLocation.X * p_PivotActor->GetActorForwardVector() + p_RelativeLocation.Y * p_PivotActor->GetActorRightVector() + p_RelativeLocation.Z * p_PivotActor->GetActorUpVector();
	return AdditionLocation + p_PivotActor->GetActorLocation();
}
