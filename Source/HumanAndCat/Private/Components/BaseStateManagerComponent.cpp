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

	// 현재 활성화 중인 State 에서 Frame 별로 적용되야할 함수를 불러옵니다.
	if(CurrentActivateState)
	{
		CurrentActivateState->TickState((DeltaTime));
	}
}

// State 를 변경합니다. 이때, Condition 은 고려하지 않습니다. (false)
void UBaseStateManagerComponent::ChangeStateOfClass(TSubclassOf<UBaseStateObject> State)
{
	TryChangeStateOfClass(State, false);
}

// GamePlayTag 를 활용해 State 변경 시도합니다.
bool UBaseStateManagerComponent::TryChangeStateOfTag(FGameplayTag StateGameplayTag, bool Condition, FGameplayTag AbilityTag)
{
	// Tag 를 이용해 원하는 State 를 찾고 해당 State 로 변경 시도 합니다.
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
		// 활성화되어 있는 State 들 중에 원하는 State 가 있다면 가져옵니다.
		UBaseStateObject* LocalState = nullptr;
		GetStateOfClass(State, LocalState);

		if(LocalState)
		{
			// 해당 State 가 UInterface_IndividualStatteFunc 를 상속 받았다면
			// 매개변수 AbilityTag 를 이용해 사용할 Ability 를 미리 State 에게 알려줍니다.
			if(LocalState->Implements<UInterface_IndividualStatteFunc>())
			{
				IInterface_IndividualStatteFunc* IndividualStatteFunc = Cast<IInterface_IndividualStatteFunc>(LocalState);
				if(IndividualStatteFunc)
				{
					IndividualStatteFunc->SetWantAbilityTag(AbilityTag);
				}
			}
			// Condition 이 true 라면 상태 변환이 가능한지 체크 합니다.
			if(Condition)
			{
				if(LocalState->CanPerformState())
				{
					// 상태 변환이 가능하므로 현재 상태를 End 합니다.
					if(CurrentActivateState)
					{
						CurrentActivateState->EndState();
					}
					// 상태를 변경합니다.
					CurrentActivateState = LocalState;
					// 변경된 상태를 Start 합니다.
					CurrentActivateState->StartState();
					return true;
				}
			}
			else
			{
				// Condition 이 false 면 상태 변환이 가능한지 체크하지 않고 바로 변환합니다.
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
			// 원하는 State 가 없다면 생성합니다.
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
	// 여러 상태들 중 변경 가능한 상태로 변경 합니다.
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
	// 매개변수의 State로 변경 가능한지 여부만 파악합니다.
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
	// 원하는 매개변수 State 가 활성화되어있다면 반환하고 없다면 null 을 반환합니다.
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
	// GameplayTag 를 활용해 원하는 State 가 존재하는지 확인하고 반환합니다.
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
		// 원하는 State 를 생성합니다.
		LocalState = NewObject<UBaseStateObject>(GetOwner(), CreateState);

		// 활성화 State 를 관리하는 배열에 넣어주고 생성된 State 를 초기화합니다.
		ActivateStates.AddUnique(LocalState);
		LocalState->SetRegisterPerformActor(PerformingActor);

		LocalState->ConstructState();
		// 최종 생성된 State 를 반환해줍니다.
		CreatedState = LocalState;
	}
}

void UBaseStateManagerComponent::ClearStatesComponent()
{
	ActivateStates.Empty();
	CurrentActivateState = nullptr;
}

