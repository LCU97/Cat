// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_FallingState.h"

#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_FallingState::UHuman_FallingState()
{
	StateGameplayTag = StateTags::State_Falling;
}

void UHuman_FallingState::TickState_Implementation(float Delta)
{
	Super::TickState_Implementation(Delta);
	RotateToTarget(0.f);
	UBaseStateObject* LocalIdleState = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
	if(StateManager->TryChangeStateOfClass(LocalIdleState->GetClass()))
	{
		return;
	}

	UBaseStateObject* LocalRunState = StateManager->GetStateOfGameplayTag(StateTags::State_Run);
	if(StateManager->TryChangeStateOfClass(LocalRunState->GetClass()))
	{
		return;
	}
	
}

bool UHuman_FallingState::CanPerformState_Implementation()
{
	FVector CurrentVec = OwnerCharacter->GetVelocity();
	return (CurrentVec.Z < 0.f && OwnerCharacter->GetMovementComponent()->IsFalling()) ? true : false;
}
