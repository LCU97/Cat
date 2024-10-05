// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HumanAndCat/Public/Characters/PlayerCharacter.h"
#include "InputActionValue.h"
#include "Interfaces/Interface_Collision.h"
#include "AdventurePlayer.generated.h"

UCLASS()
class HUMANANDCAT_API AAdventurePlayer : public APlayerCharacter, public IInterface_Collision
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAdventurePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IAInteractItemShop;
	
	void PlayerInteractItemShop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WhenItHit() override;
	virtual void WhenItHit_Implementation();
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UBaseCameraComponent* InGameCamera;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UBaseCameraComponent* UltimateCamera;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int64 CurrentMoney = 9999;

	UFUNCTION(BlueprintCallable)
	void UpdateMoney(int64 inputVal);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UInventoryActorComponent* DefaultInventory;

	void PerformInteractionTrace();
	
	AActor* CachedInteractActor;
};
