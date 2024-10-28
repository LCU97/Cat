// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/Handlers/InputHandler.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Inputs/Interface_InputCommand.h"
#include "Inputs/InputBuffer/InputBufferingObject.h"
#include "Inputs/InputCommand/BaseCommand.h"
#include "Objects/BaseStateObject.h"
#include "Objects/BaseAbilityObject.h"

UInputHandler::UInputHandler()
{
}

bool UInputHandler::AddBufferingObject(UInputBufferingObject* NewBufferingObject)
{
	if(!NewBufferingObject) return false;

	// 생성된 입력 버퍼가 허용되는 입력을 포함하고 있는지 확인하고 포함 할 때에만
	// 우선순위를 정해주고 저장합니다.
	UInputAction* InputAction = NewBufferingObject->GetInputAction();
	if(InputAction != nullptr && AllowedInputActions.Contains(InputAction))
	{
		NewBufferingObject->SetPriority(AllowedInputActions[InputAction]);
		InputBufferingObjects.Add(NewBufferingObject);
		return true;
	}
	return false;
}

void UInputHandler::ClearBuffering()
{
	InputBufferingObjects.Empty();
}

UInputBufferingObject* UInputHandler::SelectInputBufferingObject()
{
	// 최종적으로 사용할 InputBuffer 를 설정합니다.
	if(InputBufferingObjects.IsEmpty())
	{
		return nullptr;
	}
	
	switch (InputBufferType)
	{
		// 즉시 실행 타입이라면 바로 들어온 입력 버퍼를 선정합니다.
	case EInputPropertyType::Immediately:
		return InputBufferingObjects[0];
		// Last 면 이 입력버퍼가 저장된 자료구조의 마지막 요소를 선택합니다.
	case EInputPropertyType::Last:
		return InputBufferingObjects.Last();
		// 입력 버퍼의 우선순위를 보고 가장 높은 우선순위의 버퍼를 선택합니다.
	case EInputPropertyType::Priority:
		return SelectBufferingObjectByPriority();
		
	default: return nullptr;
	}
}

UInputBufferingObject* UInputHandler::SelectBufferingObjectByPriority()
{
	// 정렬 우선순위 기준
	InputBufferingObjects.Sort([](const UInputBufferingObject& A, const UInputBufferingObject& B) {
		return A.GetPriority() < B.GetPriority();
	});

	TArray<UInputBufferingObject*> PriorityBufferingObjects;
	int32 HighestPriority = InputBufferingObjects[0]->GetPriority();

	// 현재 입력 버퍼를 중 가장 높은 우선순위를 입력들을 따로 저장합니다.
	for(UInputBufferingObject* BufferingObject : InputBufferingObjects)
	{
		if(BufferingObject->GetPriority() == HighestPriority)
		{
			PriorityBufferingObjects.Add(BufferingObject);
		}
		else
		{
			break; // 이미 정렬되있으니 나가도 괜찮
		}
	}
	// 그 중 랜덤하게 선택하여 최종 입력 버퍼를 선택합니다.
	if(PriorityBufferingObjects.Num()>1)
	{
		int32 Rand = FMath::RandRange(0, PriorityBufferingObjects.Num() - 1);
		return PriorityBufferingObjects[Rand];
	}

	// 하나 밖에 없으면 그냥 선택
	return PriorityBufferingObjects[0];
}

void UInputHandler::SetupCommand(UInputBufferingObject* BufferObject)
{
	if(!BufferObject->GetStateObject()) return;

	FGameplayTag& CurrentStateTag = BufferObject->GetStateObject()->StateGameplayTag;

	// StateCommandMap 에 CurrentStateTag 가 있는지 확인합니다.
	if(StateCommandMap.Contains(CurrentStateTag))
	{
		// 존재하면 해당 Command 를 바인드합니다.
		if(UBaseCommand* Command = StateCommandMap[CurrentStateTag])
		{
			BindCommand(Command);
		}
	}
}

UBaseStateManagerComponent* UInputHandler::GetStateManager(AController* Con)
{
	if(Con)
	{
		return Con->GetComponentByClass<UBaseStateManagerComponent>();
	}
	return nullptr;
}

UBaseAbilityManagerComponent* UInputHandler::GetAbilityManager(AActor* Actor)
{
	if(Actor)
	{
		return Actor->GetComponentByClass<UBaseAbilityManagerComponent>();
	}
	return nullptr;
}

void UInputHandler::BindCommand(UObject* CommandObject)
{
	if(!CommandObject) return;

	if(!CommandObject->Implements<UInterface_InputCommand>())
	{
		return;
	}

	// 사용할 Command 가 Excute 용 인터페이스가 존재하는 확인 한 후
	// TScriptInterface로 안전하게 랲핑합니다.
	TScriptInterface<IInterface_InputCommand> InputCommand;
	InputCommand.SetObject(CommandObject);
	InputCommand.SetInterface(Cast<IInterface_InputCommand>(CommandObject));

	// InputCommands 에 사용할 커맨드를 Push 합니다.
	if(InputCommand.GetInterface() != nullptr)
	{
		InputCommands.AddUnique(InputCommand);
	}
}

// 최종 커맨드를 실행합니다.
void UInputHandler::ExecuteCommand()
{
	AActor* OuterActor = Cast<AActor>(GetOuter());
	if(!OuterActor) return;

	// 최종 입력 버퍼를 설정합니다.
	SelectBufferingObject = SelectInputBufferingObject();
	if(!SelectBufferingObject) return;

	// 커맨드 셋팅으로 사용할 InputCommands 를 추가합니다.
	SetupCommand(SelectBufferingObject);	
	if(!SelectBufferingObject) return;
	
	// 추가된 모든 커맨드를 실행합니다.
	for(TScriptInterface<IInterface_InputCommand> InputCommand : InputCommands)
	{
		if(InputCommand.GetInterface() != nullptr)
		{
			InputCommand->Execute_ActionExecute(InputCommand.GetObject(), SelectBufferingObject);
		}
	}	
}
