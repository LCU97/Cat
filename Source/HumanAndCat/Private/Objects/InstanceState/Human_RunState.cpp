// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceState/Human_RunState.h"

#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_RunState::UHuman_RunState()
{
	StateGameplayTag = StateTags::State_Run;
}

void UHuman_RunState::TickState_Implementation(float Delta)
{
	Super::TickState_Implementation(Delta);

	UBaseStateObject* LocalFallState = StateManager->GetStateOfGameplayTag(StateTags::State_Falling);
	if (!StateManager->TryChangeStateOfClass(LocalFallState->GetClass()))
	{
		UBaseStateObject* LocalIdleState = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);
		StateManager->TryChangeStateOfClass(LocalIdleState->GetClass());
	}
}

bool UHuman_RunState::CanPerformState_Implementation()
{
	if(OwnerCharacter->GetVelocity().Length() >0.f && !OwnerCharacter->GetMovementComponent()->IsFalling())
	{		
		return Super::CanPerformState_Implementation();

	}
	return false;
}
