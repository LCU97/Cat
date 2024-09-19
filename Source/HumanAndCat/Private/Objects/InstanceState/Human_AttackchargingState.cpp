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
}

void UHuman_AttackchargingState::StartState_Implementation()
{
	Super::StartState_Implementation();
	AbilityManager->PerformAbilityOfClass(CurrentAbility);
	StateManager->bIsSpecialAttack = true;
}

void UHuman_AttackchargingState::EndState_Implementation()
{
	Super::EndState_Implementation();
	//UBaseStateObject* LocalIdle = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
	//if(LocalIdle)
	//{
	//	if(!StateManager->TryChangeStateOfClass(LocalIdle->GetClass()))
	//	{
	//		UBaseStateObject* LocalRun = StateManager->GetStateOfGameplayTag(StateTags::State_Run);
	//		StateManager->TryChangeStateOfClass(LocalRun->GetClass());
	//	}
	//}
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