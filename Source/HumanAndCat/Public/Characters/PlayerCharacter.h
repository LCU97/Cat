// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "Interfaces/Interface_GameplayTagControl.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class HUMANANDCAT_API APlayerCharacter : public ACharacter, public IInterface_GameplayTagControl, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	// IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	// IInterface_GameplayTagControl
	virtual void AddGameplayTag(FGameplayTag Tag) override;
	virtual void RemoveGameplayTag(FGameplayTag Tag) override;

	bool GetCurrentGameplayTag(FGameplayTag ParentTag,FGameplayTag& OutTag);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer PlayerGameplayTags;
};
