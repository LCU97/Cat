// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CatPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"


// Sets default values
ACatPlayer::ACatPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void ACatPlayer::BeginPlay()
{
	Super::BeginPlay();
	


}

// Called every frame
void ACatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		EnhancedInputComponent->BindAction(CatMoveIA, ETriggerEvent::Triggered, this, &ACatPlayer::CatMove);

		EnhancedInputComponent->BindAction(CatLookUpIA, ETriggerEvent::Triggered, this, &ACatPlayer::CatLookUp);

		EnhancedInputComponent->BindAction(CatTurnIA, ETriggerEvent::Triggered, this, &ACatPlayer::CatTurn);

		EnhancedInputComponent->BindAction(CatJumpIA, ETriggerEvent::Triggered, this, &ACatPlayer::CatInputJump);

		EnhancedInputComponent->BindAction(CatTargetArmLength, ETriggerEvent::Triggered, this, &ACatPlayer::CatInputArm);
	}
}

void ACatPlayer::CatMove(const FInputActionValue& Value)
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

void ACatPlayer::CatLookUp(const FInputActionValue& Value)
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

void ACatPlayer::CatTurn(const FInputActionValue& Value)
{
	const float _CurrentValue = Value.Get<float>();

	AddControllerYawInput(_CurrentValue);
}

void ACatPlayer::CatInputJump(const FInputActionValue& Value)
{
	Jump();
}

void ACatPlayer::CatInputArm(const FInputActionValue& Value)
{
	if (Value.Get<float>() > 0) SpringArm->TargetArmLength += Value.Get<float>() - 10;
	else SpringArm->TargetArmLength += Value.Get<float>() + 10;

}

