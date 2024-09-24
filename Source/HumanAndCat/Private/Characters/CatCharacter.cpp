// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CatCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ACatCharacter::ACatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.


	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> InitMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/LCH/Blueprints/Character/Cats/Meshes/Mesh_CatSkinny.Mesh_CatSkinny'"));

	//메쉬
	if (InitMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(InitMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, -0));
	}

	// 카메라암
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocationAndRotation(FVector(0, 0, 50), FRotator(-20, 0, 0));
	springArmComp->TargetArmLength = 530;
	springArmComp->bUsePawnControlRotation = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;

}

// Called when the game starts or when spawned
void ACatCharacter::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void ACatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ACatCharacter::Move);

		EnhancedInputComponent->BindAction(LookUpIA, ETriggerEvent::Triggered, this, &ACatCharacter::LookUp);

		EnhancedInputComponent->BindAction(TurnIA, ETriggerEvent::Triggered, this, &ACatCharacter::Turn);

		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &ACatCharacter::InputJump);
	}
}

void ACatCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>(); // FVector2D로 변경하여 XY 축 값만 가져옴.

	if (Controller)
	{
		// 전/후 이동 (X축)
		if (InputValue.Y != 0.0f)
		{
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0, ControlRotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, InputValue.Y);
		}

		// 좌/우 이동 (Y축)
		if (InputValue.X != 0.0f)
		{
			const FRotator ControlRotation = GetControlRotation();
			const FRotator YawRotation(0, ControlRotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, InputValue.X);
		}
	}
}

void ACatCharacter::LookUp(const FInputActionValue& Value)
{

	float _CurrentValue = Value.Get<float>();
	if (isInvertLookUp)
	{
		_CurrentValue = Value.Get<float>() * -1;
	}
	else
	{
		_CurrentValue = Value.Get<float>();
	}
	AddControllerPitchInput(_CurrentValue);
}

void ACatCharacter::Turn(const FInputActionValue& Value)
{
	const float _CurrentValue = Value.Get<float>();

	AddControllerYawInput(_CurrentValue);
}

void ACatCharacter::InputJump(const FInputActionValue& Value)
{
	Jump();
}

