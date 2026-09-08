// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

//https://dev.epicgames.com/documentation/unreal-engine/coder-03-configure-character-movement-with-cplusplus-in-unreal-engine#%EC%99%84%EC%84%B1%EB%90%9C%EC%BD%94%EB%93%9C


// Sets default values
AUCharacter::AUCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SetRootComponent(Capsule);
	Capsule->SetCapsuleSize(35.f, 90.f);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Capsule);
	SpringArm->SetRelativeRotation(FRotator(-40.0f, 0.f, 0.0f));

	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Capsule);
	SkeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.f, 0.0f));
	SkeletalMesh->SetRelativeLocation(FVector(0.0f, 0.f, -89.0f));
}

// Called when the game starts or when spawned
void AUCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			if (IMC_UC)
			{
				inputSystem->AddMappingContext(IMC_UC, 0);
			}
		}
	}
}

// Called every frame
void AUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Controller)
	{
		FVector direction = (MovementInput.X * GetActorRightVector() + MovementInput.Y * GetActorForwardVector()).GetSafeNormal();
		AddActorWorldOffset(direction * MoveSpeed * DeltaTime, true);
		
		//yaw 값을 통한 이동방향에 따른 캐릭터 정면 이동 (degree)
		float targetYaw = FMath::RadiansToDegrees(FMath::Atan2(direction.Y, direction.X)) - 90.f;
		SkeletalMesh->SetWorldRotation(FRotator(0.0f, targetYaw, 0.0f));
	}
}

// Called to bind functionality to input
void AUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input != nullptr)
	{
		if (IA_Move != nullptr)
		{
			Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AUCharacter::Move);
			Input->BindAction(IA_Move, ETriggerEvent::Completed, this, &AUCharacter::Stay);
		}
	}
}

void AUCharacter::Move(const FInputActionValue& value)
{
	MovementInput = value.Get<FVector2D>();
}

void AUCharacter::Stay(const FInputActionValue& value)
{
	MovementInput = FVector2D::ZeroVector;
}
