// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Objects/BaseStateObject.h"

#include "HumanAndCat/Public/Objects/BaseAbilityObject.h"
#include "HumanAndCat/Public/Components/BaseStateManagerComponent.h"
#include "HumanAndCat/Public/Components/BaseAbilityManagerComponent.h"
#include "GameFramework/Character.h"

UBaseStateObject::UBaseStateObject()
{
}

void UBaseStateObject::ConstructState_Implementation()
{
	if(const ACharacter* OwnerCharacter = Cast<ACharacter>(PerformingActor))
	{
		const AController* Controller = OwnerCharacter->GetController();
		StateManager = Controller->GetComponentByClass<UBaseStateManagerComponent>();
	}
}

void UBaseStateObject::StartState_Implementation()
{
	if(!StateManager) return;

	// 현재 상태를 상태매니저에게 알려주며 설정
	
	StateManager->SetCurrentActivateState(this);

	// 현재 상태를 캐릭터 클래스에게 알려줘야한다.
	// TODO

	// 블루프린트에서 추가 기능 넣을 수 있음
}

void UBaseStateObject::TickState_Implementation(float Delta)
{
	// 블루프린트에서 재정의 
}

void UBaseStateObject::EndState_Implementation()
{
	if(!StateManager) return;

	if(GetIsStateCurrentlyActive())
	{
		StateManager->SetCurrentActivateState(nullptr);

		// 현재 플레이어에게서 해당 상태의 태그를 삭제 시켜주자
	}
	
}

bool UBaseStateObject::RestartState_Implementation(bool Checking)
{
	if(Checking)
	{
		if(!CanPerformState())
		{
			return false;
		}
	}

	StartState();

	return true;
}

TSubclassOf<UBaseAbilityObject> UBaseStateObject::GetAbilityObject()
{	
	return CurrentAbility;
}

void UBaseStateObject::SetAbilityObject(TSubclassOf<UBaseAbilityObject> AbilityObject)
{
	CurrentAbility = AbilityObject;
}

bool UBaseStateObject::GetIsStateCurrentlyActive()
{
	if(!StateManager) return false;
	
	return StateManager->GetCurrentActivateState() == this;
}

bool UBaseStateObject::CanPerformState_Implementation()
{
	// 블루프린트에서 재정의
	return true;
}

bool UBaseStateObject::CheckAbilityExecute_Implementation(const TArray<TSubclassOf<UBaseAbilityObject>>& AbilityObjects)
{
	UBaseAbilityManagerComponent* AbilityManagerComponent = PerformingActor->GetComponentByClass<UBaseAbilityManagerComponent>();
	if(!AbilityManagerComponent) return false;

	for(const TSubclassOf<UBaseAbilityObject> AbilityObject : AbilityObjects)
	{
		// 어빌리티매니저에서 해당 어빌리티가 사용가능한지 확인하고 틀리면 컨티뉴


		// 사용가능하면 해당 어빌리티를 어빌리티매니저로부터 받아오고 유효한지 체크한 후에 현재 어빌리티로 등록한다.

		return true;
	}
	return true;
}
