// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputCommand/AttackStateCommand.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "Inputs/InputBuffer/InputBufferingObject.h"
#include "Interfaces/Interface_IndividualStatteFunc.h"
#include "Objects/BaseAbilityObject.h"
#include "Objects/BaseStateObject.h"
#include "Utilities/HumanAndCatTags.h"

UAttackStateCommand::UAttackStateCommand()
{
	
}

void UAttackStateCommand::ActionExecute_Implementation(UInputBufferingObject* BufferObject)
{
	UBaseStateObject* CurrentState = Cast<UBaseStateObject>(BufferObject->GetStateObject());
	UBaseAbilityObject* CurrentAbility = Cast<UBaseAbilityObject>(BufferObject->GetAbilityObject());

	if(!CurrentAbility || !CurrentState)
		return;


	ProcessInput(BufferObject, CurrentState,CurrentAbility);
}

void UAttackStateCommand::ProcessInput(const UInputBufferingObject* BufferObject, UBaseStateObject* CurrentState,
	UBaseAbilityObject* CurrentAbility)
{
	FGameplayTag InputTag = BufferObject->InputTag;
	FGameplayTag CurrentAbilityTag = CurrentAbility->AbilityGameplayTag;

	if(InputTag == InputTags::Input_NorMalAttack)
	{
		HandleAttack(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if(InputTag == InputTags::Input_MoveForWard || InputTag == InputTags::Input_MoveRight)
	{
		HandleMovement(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if(InputTag == InputTags::Input_Dodge)
	{
		HandleDodge(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if(InputTag == InputTags::Input_AttackCharging)
	{
		HandleAttackCharging(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
	else if (InputTag == InputTags::Input_UltimateAttack)
	{
		HandleUltimateAttack(CurrentState, CurrentAbilityTag, CurrentAbility);
	}
}

void UAttackStateCommand::HandleAttack(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
                                       UBaseAbilityObject* CurrentAbility)
{
	if(AbilityTag == AbilityTags::Ability_Attack_NormalAttack)
	{
		CurrentAbility->StartAbility();
	}
	else
	{

		CurrentState->RestartState();
	}
}

void UAttackStateCommand::HandleUltimateAttack(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{
	if(AbilityTag == AbilityTags::Ability_Attack_NormalAttack)
	{
		UBaseAbilityObject* AbilityObject = CurrentAbility->GetAbilityManagerComponent()->GetAbilityOfGameplayTag(AbilityTags::Ability_Attack_UltimateAttack);
		CurrentAbility->GetAbilityManagerComponent()->SetCurrentActivateAbility(AbilityObject);
		CurrentAbility->StartAbility();
	}
	else
	{

		CurrentState->RestartState();
	}
}


void UAttackStateCommand::HandleMovement(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
                                         UBaseAbilityObject* CurrentAbility)
{
	AActor* PerformingActor;
	CurrentState->GetPerformingActor(PerformingActor);

	ACharacter* PerformingCharacter = Cast<ACharacter>(PerformingActor);
	if (!PerformingCharacter)
		return;

	if(AbilityTag == AbilityTags::Ability_Attack_NormalAttack ||
		AbilityTag == AbilityTags::Ability_Attack_SpecialAttack)
	{
		PerformingCharacter->StopAnimMontage();
		CurrentAbility->EndAbility();
	}
}


void UAttackStateCommand::HandleDodge(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{
	// 회피 핸들 추가 
	
}

void UAttackStateCommand::HandleAttackCharging(UBaseStateObject* CurrentState, const FGameplayTag& AbilityTag,
	UBaseAbilityObject* CurrentAbility)
{
	if(AbilityTag == AbilityTags::Ability_Attack_NormalAttack)
	{
		UBaseStateObject* LocalCharge = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_AttackCharge);
		if(LocalCharge)
		{
			CurrentAbility->CancelAbility();
			AActor* PActor;
			CurrentAbility->GetPerformingActor(PActor);
			if(PActor)
			{
				ACharacter* PCharacter = Cast<ACharacter>(PActor);
				if(PCharacter)
				{
					PCharacter->StopAnimMontage();
				}
			}
			if(CurrentState->Implements<UInterface_IndividualStatteFunc>())
			{
				IInterface_IndividualStatteFunc* IndividualStatteFunc = Cast<IInterface_IndividualStatteFunc>(CurrentState);
				if(IndividualStatteFunc)
				{
					IndividualStatteFunc->SetWantAbilityTag(FGameplayTag());
				}
			}
			CurrentState->GetStateManager()->ChangeStateOfClass(LocalCharge->GetClass());
		}
	}
	else
	{
		UBaseStateObject* LocalIdle = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_Idle);
		if(LocalIdle)
		{
			if(!CurrentState->GetStateManager()->TryChangeStateOfClass(LocalIdle->GetClass()))
			{
				UBaseStateObject* LocalRun = CurrentState->GetStateManager()->GetStateOfGameplayTag(StateTags::State_Run);
				if(LocalRun)
				{
					CurrentState->GetStateManager()->TryChangeStateOfClass(LocalRun->GetClass());
				}
			}
		}
	}
}
