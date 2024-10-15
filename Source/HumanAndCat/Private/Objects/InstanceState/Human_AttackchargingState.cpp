// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_AttackchargingState.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseCombatComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/InstanceAbility/Human_AttackChargingAbility.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_AttackchargingState::UHuman_AttackchargingState()
{
	StateGameplayTag = StateTags::State_AttackCharge;

	BlockedState.AddTag(StateTags::State_Jump);
	BlockedState.AddTag(StateTags::State_UnEquip);
	BlockedState.AddTag(StateTags::State_Equip);
	BlockedState.AddTag(StateTags::State_Attack);
}

void UHuman_AttackchargingState::StartState_Implementation()
{
	Super::StartState_Implementation();
	TSubclassOf<UBaseAbilityObject> ChargingAbility = UHuman_AttackChargingAbility::StaticClass();
	CurrentAbility = ChargingAbility;
	AbilityManager->PerformAbilityOfClass(CurrentAbility);
}

void UHuman_AttackchargingState::EndState_Implementation()
{
	Super::EndState_Implementation();
}

void UHuman_AttackchargingState::TickState_Implementation(float DeltaTime)
{
	Super::TickState_Implementation(DeltaTime);

	
}

bool UHuman_AttackchargingState::CanPerformState_Implementation()
{
	UBaseCombatComponent* CombatComponent = PerformingActor->GetComponentByClass<UBaseCombatComponent>();
	if(!CombatComponent) return false;
	if(!CombatComponent->GetInCombat()) return false;
		
	
	TArray<TSubclassOf<UBaseAbilityObject>> ChargingAbilities;
	
	// TODO 어빌리티 만들어서 넣을것
	TSubclassOf<UBaseAbilityObject> ChargingAbility = UHuman_AttackChargingAbility::StaticClass();
	ChargingAbilities.AddUnique(ChargingAbility);
	
	return Super::CanPerformState_Implementation() && CheckAbilityExecute(ChargingAbilities);
}
