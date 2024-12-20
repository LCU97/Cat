// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputCommand/AttackChargingCommand.h"

#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "Inputs/InputBuffer/InputBufferingObject.h"
#include "Interfaces/Interface_IndividualStatteFunc.h"
#include "Objects/BaseAbilityObject.h"
#include "Objects/BaseStateObject.h"
#include "Utilities/HumanAndCatTags.h"

UAttackChargingCommand::UAttackChargingCommand()
{
}

void UAttackChargingCommand::ActionExecute_Implementation(UInputBufferingObject* BufferObject)
{
	UBaseStateObject* CurrentState = Cast<UBaseStateObject>(BufferObject->GetStateObject());
	UBaseAbilityObject* CurrentAbility = Cast<UBaseAbilityObject>(BufferObject->GetAbilityObject());

	if(!CurrentState || !CurrentAbility) return;

	ProcessInput(BufferObject, CurrentState, CurrentAbility);
	
}

void UAttackChargingCommand::ProcessInput(const UInputBufferingObject* BufferObject, UBaseStateObject* CurrentState,
	UBaseAbilityObject* CurrentAbility)
{
	FGameplayTag CurrentInputTag = BufferObject->InputTag;
	FGameplayTag CurrentAbilityTag = CurrentAbility->AbilityGameplayTag;
	

	if(CurrentInputTag == InputTags::Input_MoveForWard || CurrentInputTag == InputTags::Input_MoveRight)
	{
		HandleMovement(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if(CurrentInputTag == InputTags::Input_SpecialAttack)
	{
		HandleSpecialAttack(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if (CurrentInputTag == InputTags::Input_Dodge)
	{
		HandleDodge(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
}

void UAttackChargingCommand::HandleMovement(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{
	AActor* PerformingActor;
	CurrentState->GetPerformingActor(PerformingActor);

	FGameplayTag CurrentStateTag = CurrentState->StateGameplayTag;

	ACharacter* PerformingCharacter = Cast<ACharacter>(PerformingActor);
	if (!PerformingCharacter)
		return;

	if(AbilityTag == AbilityTags::Ability_AttackCharge ||
		CurrentStateTag == StateTags::State_AttackCharge)
	{
		PerformingCharacter->StopAnimMontage();
		CurrentAbility->EndAbility();
	}
}

void UAttackChargingCommand::HandleDodge(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{
	
}

void UAttackChargingCommand::HandleSpecialAttack(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{	
	if(AbilityTag == AbilityTags::Ability_AttackCharge)
	{
		UBaseStateObject* LocalAttack = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_Attack);
		if(LocalAttack)
		{
			if(!CurrentState->GetStateManager()->TryChangeStateOfClass(LocalAttack->GetClass(), true, AbilityTags::Ability_Attack_SpecialAttack))
			{
				UBaseStateObject* LocalIdle = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_Idle);
				if(LocalIdle)
				{
					if(!CurrentState->GetStateManager()->TryChangeStateOfClass(LocalIdle->GetClass()))
					{
						UBaseStateObject* LocalRun = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_Run);
					}
				}
			}
		}
			
	}
	
}
