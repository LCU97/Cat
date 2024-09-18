// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseAbilityObject.h"
#include "Human_NormalAttackAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Ability : NormalAttack"))
class HUMANANDCAT_API UHuman_NormalAttackAbility : public UBaseAbilityObject
{
	GENERATED_BODY()

	public:
	UHuman_NormalAttackAbility();
public:
	virtual void StartAbility_Implementation() override;
	virtual void EndAbility_Implementation() override;
	virtual void CancelAbility_Implementation() override;

	virtual bool CanActivateAbility_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackComboIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> AttackMontages;
};
