// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_AttackState.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/InstanceAbility/Human_NormalAttackAbility.h"
#include "Objects/InstanceAbility/Human_SpecialAttackAbility.h"
#include "Objects/InstanceAbility/Human_UltimateAttackAbility.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_AttackState::UHuman_AttackState()
{
		
	StateGameplayTag = StateTags::State_Attack;

	BlockedState.AddTag(StateTags::State_Equip);
	BlockedState.AddTag(StateTags::State_UnEquip);
	BlockedState.AddTag(StateTags::State_Jump);
	BlockedState.AddTag(StateTags::State_Attack);
	BlockedState.AddTag(StateTags::State_Falling);
	BlockedState.AddTag(StateTags::State_Dodge);
}

bool UHuman_AttackState::CanPerformState_Implementation()
{
	/*if(StateManager->GetPreActivateState()->StateGameplayTag == StateTags::State_AttackCharge)
	{
		// 차징 어택 어빌리티를 실행합니다.
		TSubclassOf<UBaseAbilityObject> SpecialAttackAbility = UHuman_SpecialAttackAbility::StaticClass();
		AttackAbilities.AddUnique(SpecialAttackAbility);
	}
	else
	{
		// 노말 어빌리티를 실행합니다.
		TSubclassOf<UBaseAbilityObject> NormalAttackAbility = UHuman_NormalAttackAbility::StaticClass();
		AttackAbilities.AddUnique(NormalAttackAbility);
	}*/
	if(WantToAbility == AbilityTags::Ability_Attack_NormalAttack)
	{
		if(!AttackAbilities.IsEmpty())
		{
			AttackAbilities.Empty();
		}
		// 노말 어빌리티를 실행합니다.
		TSubclassOf<UBaseAbilityObject> NormalAttackAbility = UHuman_NormalAttackAbility::StaticClass();
		AttackAbilities.AddUnique(NormalAttackAbility);		
	}
	else if(WantToAbility == AbilityTags::Ability_Attack_SpecialAttack)
	{
		TSubclassOf<UBaseAbilityObject> SpecialAttackAbility = UHuman_SpecialAttackAbility::StaticClass();
		if(!AttackAbilities.IsEmpty())
		{
			AttackAbilities.Empty();
		}
		AttackAbilities.AddUnique(SpecialAttackAbility);
		StateManager->bIsSpecialAttack = false;
	}
	else if(WantToAbility == AbilityTags::Ability_Attack_UltimateAttack)
	{
		TSubclassOf<UBaseAbilityObject> UltimateAttackAbility = UHuman_UltimateAttackAbility::StaticClass();
		if(!AttackAbilities.IsEmpty())
		{
			AttackAbilities.Empty();
		}
		AttackAbilities.AddUnique(UltimateAttackAbility);
		StateManager->bIsSpecialAttack = false;
	}

	
	/*if(StateManager->bIsSpecialAttack)
	{
		// 차징 어택 어빌리티를 실행합니다.
		TSubclassOf<UBaseAbilityObject> SpecialAttackAbility = UHuman_SpecialAttackAbility::StaticClass();
		if(!AttackAbilities.IsEmpty())
		{
			AttackAbilities.Empty();
		}
		AttackAbilities.AddUnique(SpecialAttackAbility);
		StateManager->bIsSpecialAttack = false;
	}
	else
	{
		if(!AttackAbilities.IsEmpty())
		{
			AttackAbilities.Empty();
		}
		// 노말 어빌리티를 실행합니다.
		TSubclassOf<UBaseAbilityObject> NormalAttackAbility = UHuman_NormalAttackAbility::StaticClass();
		AttackAbilities.AddUnique(NormalAttackAbility);
	}*/
	
	return Super::CanPerformState_Implementation() && CheckAbilityExecute(AttackAbilities);
}

void UHuman_AttackState::ConstructState_Implementation()
{
	Super::ConstructState_Implementation();
}

void UHuman_AttackState::StartState_Implementation()
{
	Super::StartState_Implementation();
	AbilityManager->PerformAbilityOfClass(CurrentAbility);
	AttackAbilities.Empty();
}

void UHuman_AttackState::EndState_Implementation()
{	
	Super::EndState_Implementation();
	
	WantToAbility = FGameplayTag();
	
	UBaseStateObject* LocalIdle = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
	if(LocalIdle)
	{
		if(!StateManager->TryChangeStateOfClass(LocalIdle->GetClass()))
		{
			UBaseStateObject* LocalRun = StateManager->GetStateOfGameplayTag(StateTags::State_Run);
			StateManager->TryChangeStateOfClass(LocalRun->GetClass());
		}
	}
}

void UHuman_AttackState::SetWantAbilityTag(FGameplayTag Tag)
{
	WantToAbility = Tag;
}
