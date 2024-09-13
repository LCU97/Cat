// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "WeaponProperties.generated.h"

class UBaseStateObject;
class UBaseAbilityObject;
class UInputAction;

USTRUCT(BlueprintType)
struct FAbilityList
{
	GENERATED_BODY()
	UBaseAbilityObject* AbilityObject;
	TArray<UAnimMontage*> AbilitiesMontage;
};

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UWeaponProperties : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TArray<TSubclassOf<UBaseStateObject>> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<FAbilityList> Abilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TMap<UInputAction*, FGameplayTag> Inputs;
};
