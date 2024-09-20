// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "GameplayTagContainer.h"
#include "AttackChargingCommand.generated.h"

class UBaseStateObject;
class UBaseAbilityObject;
/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UAttackChargingCommand : public UBaseCommand
{
	GENERATED_BODY()

public:
	UAttackChargingCommand();

	virtual void ActionExecute_Implementation(const FInputPayLoad& InputPayLoad) override;

	void ProcessInput(const FInputPayLoad& InputPayLoad, UBaseStateObject* CurrentState, UBaseAbilityObject* CurrentAbility);
	void HandleMovement(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,UBaseAbilityObject* CurrentAbility);
	void HandleDodge(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,UBaseAbilityObject* CurrentAbility);
	void HandleSpecialAttack(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,UBaseAbilityObject* CurrentAbility);
};
