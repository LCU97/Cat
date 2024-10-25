// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Components/BaseAbilityManagerComponent.h"
#include "HumanAndCat/Public/Objects/BaseAbilityObject.h"

UBaseAbilityManagerComponent::UBaseAbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBaseAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBaseAbilityManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(CurrentAbility)
	{
		CurrentAbility->TickAbility(DeltaTime);
	}
}

void UBaseAbilityManagerComponent::InitializeAbilityManager_Implementation()
{
	
}

void UBaseAbilityManagerComponent::PerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityObj)
{
	// 어빌리티 실행 시도 합니다.
	// 매개변수 Condition 이 false로 들어가기 때문에 어빌리티 변경 가능한지 시도하지 않고 무조건 실행하려고 시도 합니다. 
	TryPerformAbilityOfClass(AbilityObj, false);
}

bool UBaseAbilityManagerComponent::TryPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityObj, bool Condition)
{
	if(!AbilityObj) return false;

	UBaseAbilityObject* NewAbilityObject = nullptr;

	// 어빌리티가 존재하는지 확인하고 가져옵니다.
	GetAbilityOfClass(AbilityObj, NewAbilityObject);

	if(NewAbilityObject == nullptr)
	{
		// 없다면 생성합니다.
		ContructAbilityOfClass(AbilityObj, NewAbilityObject);
	}

	if(NewAbilityObject)
	{
		// Condition 이 true 라면 어빌리티 실행 가능한지 확인합니다.
		if(Condition)
		{
			if(!NewAbilityObject->CanActivateAbility())
			{				
				return false;
			}
		}
		// 새로운 어빌리티를 실행합니다.
		NewAbilityObject->StartAbility();
	}
	return false;
}

bool UBaseAbilityManagerComponent::TryPerformAbilitiesOfClass(TArray<TSubclassOf<UBaseAbilityObject>> AbilityObj,
	bool Condition)
{
	// 배열로 들어온 어빌리티 클래스들 중 실행 가능한 Ability 를 실행합니다.
	for(int32 i = 0; i< AbilityObj.Num(); ++i)
	{
		if(AbilityObj[i])
		{
			if(TryPerformAbilityOfClass(AbilityObj[i]), Condition)
			{
				return true;
			}
		}
	}
	return false;
}

void UBaseAbilityManagerComponent::SetCurrentActivateAbility(UBaseAbilityObject* NewAbility)
{
	CurrentAbility = NewAbility;
}

bool UBaseAbilityManagerComponent::GetAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility,
	UBaseAbilityObject*& FoundAbility)
{
	// 현재 활성화 되어 있는 Ability 들 중에 매개변수 WantToAbility 가 존재하면
	// 반환합니다.
	for(int32 i = 0; i < AbilityList.Num(); ++i)
	{
		if(AbilityList[i])
		{
			if(AbilityList[i]->GetClass() == WantToAbility)
			{
				FoundAbility = AbilityList[i];
				return true;
			}
		}
	}
	FoundAbility = nullptr;
	return false;
}

bool UBaseAbilityManagerComponent::GetCanPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility)
{
	// 매개변수 WantToAbility 가 존재하는지 확인하고 실행 가능한지만 체크합니다.
	// WantToAbility 를 실행하지는 않습니다.
	if(WantToAbility)
	{
		UBaseAbilityObject* NewAbility = nullptr;
		GetAbilityOfClass(WantToAbility, NewAbility);

		if(!NewAbility)
		{
			ContructAbilityOfClass(WantToAbility, NewAbility);
		}
		return NewAbility->CanActivateAbility();
	}
	return false;
}

FGameplayTag UBaseAbilityManagerComponent::GetCurrentAbilityTag()
{
	if(CurrentAbility)	return CurrentAbility->AbilityGameplayTag;
	return {};
}

UBaseAbilityObject* UBaseAbilityManagerComponent::GetAbilityOfGameplayTag(FGameplayTag AbilityTag)
{
	// GameplayTag 를 활용해서 활성화된 어빌리티 중 AbilityTag 를 가지는 어빌리티를 반환합니다.
	UBaseAbilityObject* LocalAbility = nullptr;
	for(int32 i = 0; i < AbilityList.Num(); ++i)
	{
		if(AbilityList[i])
		{
			if(AbilityList[i]->AbilityGameplayTag == AbilityTag)
			{
				LocalAbility = AbilityList[i];
				return LocalAbility;
			}
		}
	}
	return LocalAbility;
}

UBaseAbilityObject* UBaseAbilityManagerComponent::GetCurrentAbility()
{
	return CurrentAbility;
}

void UBaseAbilityManagerComponent::ContructAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility,
                                                          UBaseAbilityObject*& ConstructAbility)
{
	// 어빌리티를 생성하고 초기화합니다.
	ConstructAbility = nullptr;
	if(WantToAbility)
	{
		UBaseAbilityObject* NewAbilityObject = NewObject<UBaseAbilityObject>(GetOwner(), WantToAbility);

		AbilityList.AddUnique(NewAbilityObject);
		NewAbilityObject->SetPerformingActor(GetOwner());
		NewAbilityObject->ConstructAbility();
		ConstructAbility = NewAbilityObject;
	}
}

void UBaseAbilityManagerComponent::ClearAbilityManager()
{
	CurrentAbility = nullptr;
	AbilityList.Empty();
}

