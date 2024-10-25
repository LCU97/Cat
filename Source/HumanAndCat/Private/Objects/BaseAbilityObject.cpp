// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Objects/BaseAbilityObject.h"

#include "Components/BaseStateManagerComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "HumanAndCat/Public/Components/BaseAbilityManagerComponent.h"
#include "Interfaces/Interface_GameplayTagControl.h"

UBaseAbilityObject::UBaseAbilityObject()
{
}

// Ability 객체가 생성되고 나서 초기화 함수입니다.
void UBaseAbilityObject::ConstructAbility_Implementation()
{
	AbilityManager = PerformingActor->GetComponentByClass<UBaseAbilityManagerComponent>();
	ACharacter* PCharacter = Cast<ACharacter>(PerformingActor);

	if(PCharacter)
	{
		AController* PController = PCharacter->GetController();
		if(PController)
		{
			StateManager = PController->FindComponentByClass<UBaseStateManagerComponent>();
		}
	}
}

// 실제 어빌리티를 실행합니다. 상속 가능
void UBaseAbilityObject::StartAbility_Implementation()
{
	if(AbilityManager)
	{
		AbilityManager->SetCurrentActivateAbility(this);
		// 플레이어에게 능력 태그를 너어줘야한다.
		if(IInterface_GameplayTagControl* GameplayTagControl = Cast<IInterface_GameplayTagControl>(PerformingActor))
		{
			GameplayTagControl->AddGameplayTag(AbilityGameplayTag);
		}
	}
}

void UBaseAbilityObject::TickAbility_Implementation(float Delta)
{
}

void UBaseAbilityObject::EndAbility_Implementation()
{
	// 플레이어에게 해당 능력 태그를 없애주어야한다.
	if(IInterface_GameplayTagControl* GameplayTagControl = Cast<IInterface_GameplayTagControl>(PerformingActor))
	{
		GameplayTagControl->RemoveGameplayTag(AbilityGameplayTag);
	}
}

void UBaseAbilityObject::CancelAbility_Implementation()
{
}

void UBaseAbilityObject::ApplyAbilityCoolDown()
{
	// 해당 어빌리티의 재사용이 쿨타임을 적용합니다. 
	bAbilityOnCoolDown = false;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::CoolDownReset, CooldownTime, false);
}

void UBaseAbilityObject::CoolDownReset()
{
	bAbilityOnCoolDown = true;
}

float UBaseAbilityObject::PlayAbilityMontage(UAnimMontage* MontageAbility, float InplayRate,
	EMontagePlayReturnType ReturnMontageType, float StartMontageTime, FName StartSection, bool bStopAllMontage)
{
	const ACharacter* Character = Cast<ACharacter>(PerformingActor);
	if(!Character) return 0.0f;

	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if(!AnimInstance) return 0.0f;

	// 어빌리티가 가지는 몽타주를 실행합니다.
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

TArray<UAnimMontage*> UBaseAbilityObject::GetAnimMontages(TSubclassOf<UBaseAbilityObject> SearchAbility)
{
	// 몽타주를 담는 배열
	TArray<UAnimMontage*> LocalAnmontages;

	// WeaponComponent 의 DataAsset 을 가져와 사용 할 수 있는 몽타주 중에 SearchAbility 가
	// 있으면 가져옵니다.
	UWeaponComponent* WeaponComponent = PerformingActor->FindComponentByClass<UWeaponComponent>();
	if(WeaponComponent)
	{
		UWeaponProperties* WeaponType;
		WeaponComponent->GetCurrentWeaponType(WeaponType);

		if(WeaponType)
		{
			for(auto abilityMontage : WeaponType->Abilities)
			{
				if(abilityMontage.AbilityObject == SearchAbility)
				{
					LocalAnmontages = abilityMontage.AbilitiesMontage;
					return LocalAnmontages;
				}
			}
		}
	}
	return LocalAnmontages;
}

UAnimMontage* UBaseAbilityObject::GetCurrentAbilityMontage()
{
	return AbilityMontage;
}

bool UBaseAbilityObject::GetIsActivateAbility()
{
	// 현재 사용중인 어빌리티가 자신과 맞는지 체크합니다.
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
