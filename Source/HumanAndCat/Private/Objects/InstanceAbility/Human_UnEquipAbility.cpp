// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceAbility/Human_UnEquipAbility.h"

#include "Components/BaseCombatComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Objects/BaseStateObject.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_UnEquipAbility::UHuman_UnEquipAbility()
{
	AbilityGameplayTag = AbilityTags::Ability_UnEquip;
}

void UHuman_UnEquipAbility::StartAbility_Implementation()
{
	Super::StartAbility_Implementation();

	TArray<UAnimMontage*> Montages = GetAnimMontages(GetClass());
	
	PlayAbilityMontage(Montages[0]);

	ACharacter* PCharacter = Cast<ACharacter>(PerformingActor);

	if(PCharacter)
	{
		PCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.f;
	}

	UBaseCombatComponent* CombatComponent = PerformingActor->FindComponentByClass<UBaseCombatComponent>();
	if(CombatComponent)
	{
		CombatComponent->SetInCombat(false);
		if(CombatComponent->OnInCombatChanged.IsBound())
		{
			CombatComponent->OnInCombatChanged.Broadcast(false);
		}
	}
}

void UHuman_UnEquipAbility::EndAbility_Implementation()
{
	Super::EndAbility_Implementation();
	UBaseStateObject* IdleState = StateManager->GetStateOfGameplayTag(StateTags::State_Idle);

	if(IdleState)
	{
		StateManager->ChangeStateOfClass(IdleState->GetClass());
	}
}

bool UHuman_UnEquipAbility::CanActivateAbility_Implementation()
{	
	if(StateManager)
	{
		if(!StateManager->GetCurrentActivateState())
		{
			return false;
		}
	}
	
	TArray<UAnimMontage*> Montages = GetAnimMontages(GetClass());
	if(Montages.IsEmpty())
	{
		return false;
	}
	UBaseStateObject* LocalState = StateManager->GetCurrentActivateState();
	FGameplayTag LocalGameplayTag = LocalState->StateGameplayTag; 
	if(!(LocalGameplayTag == StateTags::State_Idle || LocalGameplayTag == StateTags::State_Run))
	{
		return false;
	}
	
	UBaseCombatComponent* CombatComponent = PerformingActor->FindComponentByClass<UBaseCombatComponent>();
	if(!CombatComponent) return false;

	if(!CombatComponent->GetInCombat())
	{
		return false;
	}
	
	return true;
}
