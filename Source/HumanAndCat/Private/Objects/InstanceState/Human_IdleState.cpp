// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_IdleState.h"

#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_IdleState::UHuman_IdleState()
{
	StateGameplayTag = StateTags::State_Idle;
}

void UHuman_IdleState::TickState_Implementation(float Delta)
{
	Super::TickState_Implementation(Delta);

	UBaseStateObject* LocalFallingState = StateManager->GetStateOfGameplayTag(StateTags::State_Falling);

	if(!StateManager->TryChangeStateOfClass(LocalFallingState->GetClass()))
	{
		UBaseStateObject* LocalWalkState = StateManager->GetStateOfGameplayTag(StateTags::State_Run);
		StateManager->TryChangeStateOfClass(LocalWalkState->GetClass());
	}
}

bool UHuman_IdleState::CanPerformState_Implementation()
{
	FVector OwnerVelocity = OwnerCharacter->GetVelocity();
	
	return OwnerVelocity.Length() == 0.f ? true : false;
}
