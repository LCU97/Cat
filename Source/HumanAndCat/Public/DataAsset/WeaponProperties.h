// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "WeaponProperties.generated.h"

class UBaseStateObject;
class UBaseAbilityObject;
class UInputAction;

USTRUCT(BlueprintType,Blueprintable)
struct FAbilityList
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UBaseAbilityObject> AbilityObject;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UAnimMontage*> AbilitiesMontage;
};

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	None UMETA(DisplayName = "None"),
	Fist UMETA(DisplayName = "Fist"),
	Sword UMETA(DisplayName = "Sword"),
	Staff UMETA(DisplayName = "Staff")
};

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UWeaponProperties : public UPrimaryDataAsset
{
	GENERATED_BODY()
 // 무기에 따른 상태와 어빌리티 입력 값 등을 설정하는 DA 입니다.
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "States")
	TArray<TSubclassOf<UBaseStateObject>> States;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<FAbilityList> Abilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs")
	TMap<UInputAction*, FGameplayTag> Inputs;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponName WeaponName;
};
