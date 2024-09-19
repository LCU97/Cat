// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/InstanceAbility/Human_AttackChargingAbility.h"

#include "Components/BaseCombatComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Utilities/HumanAndCatTags.h"

UHuman_AttackChargingAbility::UHuman_AttackChargingAbility()
{
	
	AbilityGameplayTag = AbilityTags::Ability_AttackCharge;
}

void UHuman_AttackChargingAbility::StartAbility_Implementation()
{
	Super::StartAbility_Implementation();

	TArray<UAnimMontage*> Montages	= GetAnimMontages(GetClass());

	if(Montages.IsEmpty())
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Idle);
	}

	// 차징 어빌리티가 여러개면 램덤
	int32 Rand = FMath::RandRange(0, Montages.Num()-1);
	PlayAbilityMontage(Montages[Rand]);
}

void UHuman_AttackChargingAbility::EndAbility_Implementation()
{
	Super::EndAbility_Implementation();

	if(!StateManager->TryChangeStateOfTag(StateTags::State_Idle))
	{
		StateManager->TryChangeStateOfTag(StateTags::State_Run);
	}
}

bool UHuman_AttackChargingAbility::CanActivateAbility_Implementation()
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
