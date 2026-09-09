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
	float CurrentMoveSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float DefaultMoveSpeed = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float SprintMoveSpeed = 800.f;
	
	bool bIsDashing = false;
	
	FVector2D MovementInput;
	
	void Move(const FInputActionValue& value);
	void Stay(const FInputActionValue& value);
	void Sprint(const FInputActionValue& value);
	
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
