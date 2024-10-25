// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceAbility/Human_SpecialAttackAbility.h"

#include "Components/BaseCombatComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/BaseStateObject.h"
#include "Utilities/HumanAndCatTags.h"


UHuman_SpecialAttackAbility::UHuman_SpecialAttackAbility()
{
	AbilityGameplayTag = AbilityTags::Ability_Attack_SpecialAttack;
}

void UHuman_SpecialAttackAbility::StartAbility_Implementation()
{
	Super::StartAbility_Implementation();

	TArray<UAnimMontage*> AnimMontages = GetAnimMontages(GetClass());

	if(AnimMontages.IsEmpty())
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Idle, false);
	}
	
	PlayAbilityMontage(AnimMontages[0]);
}

void UHuman_SpecialAttackAbility::EndAbility_Implementation()
{
	Super::EndAbility_Implementation();
	
	StateManager->GetCurrentActivateState()->WantToAbility = FGameplayTag();
	
	if(!StateManager->TryChangeStateOfTag(StateTags::State_Idle))
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Run);
	}	
}

bool UHuman_SpecialAttackAbility::CanActivateAbility_Implementation()
{
	TArray<UAnimMontage*> Montages = GetAnimMontages(GetClass());
	if(Montages.IsEmpty())
	{
		return false;
	}

	UBaseCombatComponent* CombatComponent = PerformingActor->GetComponentByClass<UBaseCombatComponent>();
	if(CombatComponent)
	{
		if(!CombatComponent->GetInCombat())
		{
			return false;
		}
	}
	
	return Super::CanActivateAbility_Implementation();
}
