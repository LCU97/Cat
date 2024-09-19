// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseAbilityObject.h"
#include "Human_SpecialAttackAbility.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UHuman_SpecialAttackAbility : public UBaseAbilityObject
{
	GENERATED_BODY()
public:
	UHuman_SpecialAttackAbility();

public:
	virtual void StartAbility_Implementation() override;
	virtual void EndAbility_Implementation() override;

	virtual bool CanActivateAbility_Implementation() override;
	
};
