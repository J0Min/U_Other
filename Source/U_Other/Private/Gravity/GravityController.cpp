  // Fill out your copyright notice in the Description page of Project Settings.


#include "Gravity/GravityController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

  void AGravityController::UpdateRotation(float DeltaTime)
  {
    FVector GravityDirection = FVector::DownVector;
    if (ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn()))
    {
      if (UCharacterMovementComponent* MoveComp = PlayerCharacter->GetCharacterMovement()){
        GravityDirection = MoveComp->GetGravityDirection();
      }
    }
    
    // 월드 공간에서 현재 컨트롤 회전을 가져옵니다.
    FRotator ViewRotation = GetControlRotation();
    
    // 중력 변화가 있었다면 그에 따른 회전을 더합니다.
    // 카메라가 중력 회전에 자동으로 보정되지 않게 하려면 이 코드 블록을 삭제하세요.
    if (!LastFrameGravity.Equals(FVector::ZeroVector))
    {
      const FQuat DeltaGravityRotation = FQuat::FindBetweenNormals(LastFrameGravity, GravityDirection);
      const FQuat WrappedCameraRotation = DeltaGravityRotation * FQuat(ViewRotation);
      
      ViewRotation = WrappedCameraRotation.Rotator();
    }
    LastFrameGravity = GravityDirection;
    
    // 뷰 회전을 월드 공간에서 중력 기준 공간으로 변환합니다.
    // 이제 커스텀 중력이 없는 것처럼 회전을 다룰 수 있습니다.
    ViewRotation = GetGravityRelativeRotation(ViewRotation, GravityDirection);
    
    // ViewRotation에 적용할 회전 변화량을 계산합니다.
    FRotator DeltaRot(RotationInput);
    if (PlayerCameraManager)
    {
      ACharacter* PlayerCharacter = Cast<ACharacter>(GetPawn());
      PlayerCameraManager->ProcessViewRotation(DeltaTime, ViewRotation, DeltaRot);
      
      // 카메라가 중력 기준으로 항상 수평을 유지하도록 롤을 0으로 설정합니다.
      ViewRotation.Roll = 0;
      
      // 회전을 다시 월드 공간으로 변환하고 현재 컨트롤 회전으로 설정합니다.
      SetControlRotation(GetGravityWorldRotation(ViewRotation, GravityDirection));
    }
    
    APawn* const P = GetPawnOrSpectator();
    if (P)
    {
      P->FaceRotation(ViewRotation, DeltaTime);
    }
  }

  FRotator AGravityController::GetGravityRelativeRotation(FRotator Rotation, FVector GravityDirection)
  {
    if (!GravityDirection.Equals(FVector::DownVector))
    {
      FQuat GravityRotation = FQuat::FindBetweenNormals(GravityDirection, FVector::DownVector);
      return (GravityRotation * Rotation.Quaternion()).Rotator();
    }
    return Rotation;
  }

  FRotator AGravityController::GetGravityWorldRotation(FRotator Rotation, FVector GravityDirection)
  {
    if (!GravityDirection.Equals(FVector::DownVector))
    {
      FQuat GravityRotation = FQuat::FindBetweenNormals(FVector::DownVector, GravityDirection);
      return (GravityRotation * Rotation.Quaternion()).Rotator();
    }
    return Rotation;
  }
