// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_EquipState.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/InstanceAbility/Human_EquipAbility.h"
#include "Utilities/HumanAndCatTags.h"


UHuman_EquipState::UHuman_EquipState()
{
	EquipAbility = UHuman_EquipAbility::StaticClass();

	StateGameplayTag = StateTags::State_Equip;

	BlockedState.AddTag(StateTags::State_Attack);
	BlockedState.AddTag(StateTags::State_Jump);
	BlockedState.AddTag(StateTags::State_AttackCharge);
	BlockedState.AddTag(StateTags::State_Dodge);
	BlockedState.AddTag(StateTags::State_UnEquip);
	BlockedState.AddTag(StateTags::State_Equip);
}

void UHuman_EquipState::StartState_Implementation()
{
	
	Super::StartState_Implementation();
	AbilityManager->PerformAbilityOfClass(GetCurrentAbility());
}

void UHuman_EquipState::EndState_Implementation()
{
	Super::EndState_Implementation();
	UBaseStateObject* LocalState = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
	if(!LocalState) return;

	StateManager->ChangeStateOfClass(LocalState->GetClass());
}

bool UHuman_EquipState::CanPerformState_Implementation()
{
	TArray<TSubclassOf<UBaseAbilityObject>> EquipAbilities;
	EquipAbilities.Add(EquipAbility);
	return CheckAbilityExecute(EquipAbilities);
	
}
