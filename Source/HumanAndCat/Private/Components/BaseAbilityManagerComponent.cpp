// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Components/BaseAbilityManagerComponent.h"

#include "HumanAndCat/Public/Objects/BaseAbilityObject.h"


// Sets default values for this component's properties
UBaseAbilityManagerComponent::UBaseAbilityManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
	TryPerformAbilityOfClass(AbilityObj);
}

bool UBaseAbilityManagerComponent::TryPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityObj, bool Condition)
{
	if(!AbilityObj) return false;

	UBaseAbilityObject* NewAbilityObject = nullptr;

	GetAbilityOfClass(AbilityObj, NewAbilityObject);

	if(NewAbilityObject == nullptr)
	{
		ContructAbilityOfClass(AbilityObj, NewAbilityObject);
	}

	if(NewAbilityObject)
	{
		if(Condition)
		{
			if(!NewAbilityObject->CanActivateAbility())
			{
				return false;
			}
		}
		NewAbilityObject->StartAbility();
	}
	return false;
}

bool UBaseAbilityManagerComponent::TryPerformAbilitiesOfClass(TArray<TSubclassOf<UBaseAbilityObject>> AbilityObj,
	bool Condition)
{
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

