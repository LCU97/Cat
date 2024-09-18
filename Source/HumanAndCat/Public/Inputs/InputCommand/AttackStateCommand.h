// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "GameplayTagContainer.h"
#include "AttackStateCommand.generated.h"

class UBaseAbilityObject;
class UBaseStateObject;
/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UAttackStateCommand : public UBaseCommand
{
	GENERATED_BODY()
public:
	UAttackStateCommand();

	virtual void ActionExecute_Implementation(const FInputPayLoad& InputPayLoad) override;

	void ProcessInput(const FInputPayLoad& InputPayLoad, UBaseStateObject* CurrentState, UBaseAbilityObject* CurrentAbility);
	void HandleAttack(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag, UBaseAbilityObject* CurrentAbility);
	void HandleMovement(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,UBaseAbilityObject* CurrentAbility);
	void HandleDodge(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,UBaseAbilityObject* CurrentAbility);
	
};
