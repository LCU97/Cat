// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAndCat/Public/Components/BaseStateManagerComponent.h"

#include "InterchangeTranslatorBase.h"
#include "HumanAndCat/Public/Objects/BaseStateObject.h"
#include "Interfaces/Interface_IndividualStatteFunc.h"

// Sets default values for this component's properties
UBaseStateManagerComponent::UBaseStateManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseStateManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseStateManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(CurrentActivateState)
	{
		CurrentActivateState->TickState((DeltaTime));
	}
}

void UBaseStateManagerComponent::ChangeStateOfClass(TSubclassOf<UBaseStateObject> State)
{
	TryChangeStateOfClass(State, false);
}

bool UBaseStateManagerComponent::TryChangeStateOfTag(FGameplayTag StateGameplayTag, bool Condition, FGameplayTag AbilityTag)
{
	if(UBaseStateObject* ChangeState = GetStateOfGameplayTag(StateGameplayTag))
	{
		return TryChangeStateOfClass(ChangeState->GetClass(), Condition, AbilityTag);
	}
	return false;
}

bool UBaseStateManagerComponent::TryChangeStateOfClass(TSubclassOf<UBaseStateObject> State, bool Condition, FGameplayTag AbilityTag)
{
	if(State)
	{
		UBaseStateObject* LocalState = nullptr;
		GetStateOfClass(State, LocalState);

		if(LocalState)
		{
			if(LocalState->Implements<UInterface_IndividualStatteFunc>())
			{
				IInterface_IndividualStatteFunc* IndividualStatteFunc = Cast<IInterface_IndividualStatteFunc>(LocalState);
				if(IndividualStatteFunc)
				{
					IndividualStatteFunc->SetWantAbilityTag(AbilityTag);
				}
			}
			if(Condition)
			{
				if(LocalState->CanPerformState())
				{
					if(CurrentActivateState)
					{
						CurrentActivateState->EndState();
					}

					
					CurrentActivateState = LocalState;
					
					CurrentActivateState->StartState();
					return true;
				}
			}
			else
			{
				if(CurrentActivateState)
				{
					CurrentActivateState->EndState();
				}
				CurrentActivateState = LocalState;

				CurrentActivateState->StartState();
				return true;
			}
			return false;
		}
		else
		{
			ConstructStateOfClass(State, LocalState);
			if(LocalState->Implements<UInterface_IndividualStatteFunc>())
			{
				IInterface_IndividualStatteFunc* IndividualStatteFunc = Cast<IInterface_IndividualStatteFunc>(LocalState);
				if(IndividualStatteFunc)
				{
					IndividualStatteFunc->SetWantAbilityTag(AbilityTag);
				}
			}
			if(Condition)
			{
				if(LocalState->CanPerformState())
				{
					if(CurrentActivateState)
					{
						CurrentActivateState->EndState();
					}

					CurrentActivateState = LocalState;

					CurrentActivateState->StartState();
					return true;
				}
			}
			else
			{
				if(CurrentActivateState)
				{
					CurrentActivateState->EndState();
				}
				CurrentActivateState = LocalState;
				CurrentActivateState->StartState();
				return true;
			}
		}
	}
	
	return false;
}

bool UBaseStateManagerComponent::TryChangeStatesOfClass(TArray<TSubclassOf<UBaseStateObject>> States, bool Condition)
{
	bool LocalBool = false;
	for(int32 i = 0; i < States.Num(); i++)
	{
		if(States[i])
		{
			LocalBool = TryChangeStateOfClass(States[i], Condition);
			if(LocalBool)
			{
				return true;
			}
		}
	}
	return false;
}

void UBaseStateManagerComponent::InitializeStateManagerComponent_Implementation(AActor* PerformActor)
{
	PerformingActor = PerformActor;
}

void UBaseStateManagerComponent::SetCurrentActivateState(UBaseStateObject* NewCurrentState)
{
	CurrentActivateState = NewCurrentState;
}

bool UBaseStateManagerComponent::GetCanPerformStateOfClass(TSubclassOf<UBaseStateObject> WantToState)
{
	if(WantToState)
	{
		UBaseStateObject* LocalState = nullptr;
		GetStateOfClass(WantToState, LocalState);
		if(LocalState)
		{
			return LocalState->CanPerformState();
		}
		else
		{
			UBaseStateObject* LocalConstructState;
			ConstructStateOfClass(WantToState, LocalConstructState);

			return LocalConstructState->CanPerformState();
		}
	}
	return false;
}

void UBaseStateManagerComponent::GetStateOfClass(TSubclassOf<UBaseStateObject> SearchState, UBaseStateObject*& FoundState)
{
	for(int32 i = 0; i < ActivateStates.Num(); ++i)
	{
		if(ActivateStates[i])
		{
			if(ActivateStates[i]->GetClass() == SearchState)
			{
				FoundState = ActivateStates[i];
				return;
			}
		}
	}
	FoundState = nullptr;
}

UBaseStateObject* UBaseStateManagerComponent::GetStateOfGameplayTag(FGameplayTag StateGameplayTag)
{
	for(int32 i =0; i<ActivateStates.Num(); ++i)
	{
		if(ActivateStates[i])
		{
			if(ActivateStates[i]->StateGameplayTag == StateGameplayTag)
			{
				return ActivateStates[i];
			}
		}
	}
	return nullptr;
}

void UBaseStateManagerComponent::ConstructStateOfClass(TSubclassOf<UBaseStateObject> CreateState, UBaseStateObject*& CreatedState)
{
	CreatedState = nullptr;
	if(CreateState)
	{
		UBaseStateObject* LocalState = nullptr;
		LocalState = NewObject<UBaseStateObject>(GetOwner(), CreateState);

		ActivateStates.AddUnique(LocalState);
		LocalState->SetRegisterPerformActor(PerformingActor);

		LocalState->ConstructState();
		CreatedState = LocalState;
	}
}

void UBaseStateManagerComponent::ClearStatesComponent()
{
	ActivateStates.Empty();
	CurrentActivateState = nullptr;
}

