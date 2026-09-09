// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/Pawn.h"
#include "UCharacter.generated.h"

UCLASS()
class U_OTHER_API AUCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	//입력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputMappingContext* IMC_UC;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* IA_Sprint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* IA_Look;
	
	//이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentMoveSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float DefaultMoveSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintMoveSpeed = 800.f;
	
	//달리기 유무
	bool bIsDashing = false;
	
	FVector2D MovementInput;
	
	//스태미너
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentStamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Max_Stamina = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Plus_Stamina = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Minus_Stamina = 10.f;
	
	//타이머
	float CurrentTime = 0.f;
	
	void Move(const FInputActionValue& value);
	void Stay(const FInputActionValue& value);
	void Sprint();
	void Look(const FInputActionValue& value);

	//카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* Camera;
	
	//스프링암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;
	
	//캡슐
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* Capsule;
	
	//스켈레탈 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMesh;
};
