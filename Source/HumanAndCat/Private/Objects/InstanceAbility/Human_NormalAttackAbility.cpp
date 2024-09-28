// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceAbility/Human_NormalAttackAbility.h"

#include "Components/BaseCombatComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Objects/BaseStateObject.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_NormalAttackAbility::UHuman_NormalAttackAbility()
{
	AbilityGameplayTag = AbilityTags::Ability_Attack_NormalAttack;
}

void UHuman_NormalAttackAbility::StartAbility_Implementation()
{
	Super::StartAbility_Implementation();

	AttackMontages	= GetAnimMontages(GetClass());

	if(AttackMontages.IsEmpty())
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Idle);
	}

	PlayAbilityMontage(AttackMontages[AttackComboIndex]);

	if(AttackComboIndex + 1 >= AttackMontages.Num())
	{
		AttackComboIndex = 0;
	}
	else
	{
		AttackComboIndex++;
	}
	
	
}

void UHuman_NormalAttackAbility::EndAbility_Implementation()
{
	Super::EndAbility_Implementation();
	AttackComboIndex = 0;
	StateManager->CurrentActivateState->WantToAbility = FGameplayTag();
	if(!StateManager->TryChangeStateOfTag(StateTags::State_Idle))
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Run);
	}
}

void UHuman_NormalAttackAbility::CancelAbility_Implementation()
{
	AttackComboIndex = 0;
	Super::CancelAbility_Implementation();	
}

bool UHuman_NormalAttackAbility::CanActivateAbility_Implementation()
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

	return true;
}
