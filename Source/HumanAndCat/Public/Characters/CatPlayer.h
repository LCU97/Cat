// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CatPlayer.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS()
class HUMANANDCAT_API ACatPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* Camera;

public:

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category ="Input")
	UInputAction* CatMoveIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CatLookUpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CatTurnIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CatJumpIA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CatTargetArmLength;

	void CatMove(const FInputActionValue& Value);
	void CatLookUp(const FInputActionValue& Value);
	void CatTurn(const FInputActionValue& Value);
	void CatInputJump(const FInputActionValue& Value);
	void CatInputArm(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Control Option")
	bool isInvertLookUp = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Control Option")
	bool bIsPossess = false;
};
