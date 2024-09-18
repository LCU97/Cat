// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_JumpState.h"

#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_JumpState::UHuman_JumpState()
{
	StateGameplayTag = StateTags::State_Jump;

	BlockedState.AddTag(StateTags::State_Falling);
	BlockedState.AddTag(StateTags::State_Attack);
	BlockedState.AddTag(StateTags::State_AttackCharge);
	BlockedState.AddTag(StateTags::State_Dodge);
	BlockedState.AddTag(StateTags::State_Equip);
	BlockedState.AddTag(StateTags::State_UnEquip);
	BlockedState.AddTag(StateTags::State_Hit);
	BlockedState.AddTag(StateTags::State_Die);
}

void UHuman_JumpState::StartState_Implementation()
{
	Super::StartState_Implementation();
	OwnerCharacter->Jump();
}

void UHuman_JumpState::TickState_Implementation(float TickTime)
{
	Super::TickState_Implementation(TickTime);

	UBaseStateObject* LocalFallState = StateManager->GetStateOfGameplayTag(StateTags::State_Falling);
	StateManager->TryChangeStateOfClass(LocalFallState->GetClass());
}

void UHuman_JumpState::EndState_Implementation()
{
	if(!GetIsStateCurrentlyActive())return;

	OwnerCharacter->StopJumping();
	Super::EndState_Implementation();
}
