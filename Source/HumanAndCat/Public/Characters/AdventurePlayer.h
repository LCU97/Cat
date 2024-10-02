// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HumanAndCat/Public/Characters/PlayerCharacter.h"
#include "AdventurePlayer.generated.h"

UCLASS()
class HUMANANDCAT_API AAdventurePlayer : public APlayerCharacter
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
