// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CatCharacter.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class HUMANANDCAT_API ACatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(VisibleAnywhere,Category = "Camera")
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere,Category = "Camera")
	class UCameraComponent* cameraComp;

public:
	UPROPERTY(EditAnywhere,category = "Input")
	UInputMappingContext* PlayerMappingContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category ="Input")
	UInputAction* MoveIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpIA;


	void Move(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void InputJump(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Control Option")
	bool isInvertLookUp = false;
};
