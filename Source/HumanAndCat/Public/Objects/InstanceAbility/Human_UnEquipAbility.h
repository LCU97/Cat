// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseAbilityObject.h"
#include "Human_UnEquipAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="Ability : UnEquip"))
class HUMANANDCAT_API UHuman_UnEquipAbility : public UBaseAbilityObject
{
	GENERATED_BODY()

	public:
	UHuman_UnEquipAbility();
public:

	virtual void StartAbility_Implementation() override;
	virtual void EndAbility_Implementation() override;

	virtual bool CanActivateAbility_Implementation() override;
};
