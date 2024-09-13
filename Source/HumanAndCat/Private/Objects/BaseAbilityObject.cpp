// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Objects/BaseAbilityObject.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HumanAndCat/Public/Components/BaseAbilityManagerComponent.h"

UBaseAbilityObject::UBaseAbilityObject()
{
}

void UBaseAbilityObject::ConstructAbility_Implementation()
{
	AbilityManager = PerformingActor->GetComponentByClass<UBaseAbilityManagerComponent>();
}

void UBaseAbilityObject::StartAbility_Implementation()
{
	if(AbilityManager)
	{
		AbilityManager->SetCurrentActivateAbility(this);
		// 플레이어에게 능력 태그를 너어줘야한다.
		
	}
}

void UBaseAbilityObject::TickAbility_Implementation(float Delta)
{
}

void UBaseAbilityObject::EndAbility_Implementation()
{
	// 플레이어에게 해당 능력 태그를 없애주어야한다.
}

void UBaseAbilityObject::CancelAbility_Implementation()
{
}

void UBaseAbilityObject::ApplyAbilityCoolDown()
{
	if(CooldownTime > 0 )
	{
		bAbilityOnCoolDown = true;
		UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CoolDownReset")), CooldownTime, false);

	}
}

void UBaseAbilityObject::CoolDownReset()
{
	bAbilityOnCoolDown = false;
}

float UBaseAbilityObject::PlayAbilityMontage(UAnimMontage* MontageAbility, float InplayRate,
	EMontagePlayReturnType ReturnMontageType, float StartMontageTime, FName StartSection, bool bStopAllMontage)
{
	const ACharacter* Character = Cast<ACharacter>(PerformingActor);
	if(!Character) return 0.0f;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if(!AnimInstance) return 0.0f;

	float MontageLenth = AnimInstance->Montage_Play(MontageAbility, InplayRate, ReturnMontageType, StartMontageTime,  bStopAllMontage);
	
	SetActivateAbilityMontage(MontageAbility);
	
	if(!StartSection.IsNone())
	{
		AnimInstance->Montage_JumpToSection(StartSection,MontageAbility);
	}
	return MontageLenth;
}

bool UBaseAbilityObject::CanActivateAbility_Implementation()
{
	return GetOnCoolDown();
}

bool UBaseAbilityObject::CanReActivateAbility_Implementation()
{
	return GetOnCoolDown();
}

bool UBaseAbilityObject::GetOnCoolDown()
{
	return bAbilityOnCoolDown;
}

void UBaseAbilityObject::GetPerformingActor(AActor*& Actor)
{
	Actor = PerformingActor;
}

UAnimMontage* UBaseAbilityObject::GetCurrentAbilityMontage()
{
	return AbilityMontage;
}

bool UBaseAbilityObject::GetIsActivateAbility()
{
	if(UBaseAbilityObject* CurrentAbility = AbilityManager->GetCurrentAbility())
	{
		return  this == CurrentAbility;
	}
	return false;
}

UBaseAbilityManagerComponent* UBaseAbilityObject::GetAbilityManagerComponent()
{
	return AbilityManager;
}

void UBaseAbilityObject::SetAbilityManagerComponent(UBaseAbilityManagerComponent* AbilityManagerComponent)
{
	AbilityManager = AbilityManagerComponent;
}

void UBaseAbilityObject::SetPerformingActor(AActor* NewActor)
{
	PerformingActor = NewActor;
}

void UBaseAbilityObject::SetActivateAbilityMontage(UAnimMontage* NewMontage)
{
	AbilityMontage = NewMontage;
}
