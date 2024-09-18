// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_UnEquipState.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/BaseAbilityObject.h"
#include "Objects/InstanceAbility/Human_UnEquipAbility.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_UnEquipState::UHuman_UnEquipState()
{
	
	UnEquipAbility = UHuman_UnEquipAbility::StaticClass();

	StateGameplayTag = StateTags::State_UnEquip;
	
	BlockedState.AddTag(StateTags::State_Attack);
	BlockedState.AddTag(StateTags::State_Jump);
	BlockedState.AddTag(StateTags::State_AttackCharge);
	BlockedState.AddTag(StateTags::State_Dodge);
	BlockedState.AddTag(StateTags::State_UnEquip);
	BlockedState.AddTag(StateTags::State_Equip);
}

void UHuman_UnEquipState::StartState_Implementation()
{
	Super::StartState_Implementation();
	AbilityManager->PerformAbilityOfClass(GetCurrentAbility());
}

void UHuman_UnEquipState::EndState_Implementation()
{
	Super::EndState_Implementation();
	const UBaseStateObject* LocalStateObject = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
	if(!LocalStateObject) return;

	StateManager->TryChangeStateOfClass(LocalStateObject->GetClass());
}

bool UHuman_UnEquipState::CanPerformState_Implementation()
{
	TArray<TSubclassOf<UBaseAbilityObject>> UnEquipAbilities;
	UnEquipAbilities.Add(UnEquipAbility);
	return CheckAbilityExecute(UnEquipAbilities);
}
