// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseAbilityObject.h"
#include "Human_AttackChargingAbility.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UHuman_AttackChargingAbility : public UBaseAbilityObject
{
	GENERATED_BODY()
public:
	UHuman_AttackChargingAbility();
public:
	virtual void StartAbility_Implementation() override;
	virtual void EndAbility_Implementation() override;

	virtual bool CanActivateAbility_Implementation() override;

public:
};
