// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GravityController.generated.h"

UCLASS()
class U_OTHER_API AGravityController: public APlayerController
{
	GENERATED_BODY()
public:
	virtual void UpdateRotation(float DeltaTime) override;
	
	// 월드 공간의 회전을 중력 기준 공간의 회전으로 변환합니다.
	UFUNCTION(BlueprintPure)
	static FRotator GetGravityRelativeRotation(FRotator Rotation, FVector GravityDirection);
	
	// 중력 기준 공간의 회전을 월드 공간의 회전으로 변환합니다.
	UFUNCTION(BlueprintPure)
	static FRotator GetGravityWorldRotation(FRotator Rotation, FVector GravityDirection);
	
private:
	FVector LastFrameGravity = FVector::ZeroVector;	
};
