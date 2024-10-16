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

	UInputAction* InputAction = NewBufferingObject->InputAction;
	if(InputAction != nullptr && AllowedInputActions.Contains(InputAction))
	{
		NewBufferingObject->Priority = AllowedInputActions[InputAction];
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
	if(InputBufferingObjects.IsEmpty())
	{
		return nullptr;
	}

	switch (InputBufferType)
	{
	case EInputPropertyType::Immediately:
		return InputBufferingObjects[0];
	case EInputPropertyType::Last:
		return InputBufferingObjects.Last();
	case EInputPropertyType::Priority:
		return SelectBufferingObjectByPriority();
		
	default: return nullptr;
	}
}

UInputBufferingObject* UInputHandler::SelectBufferingObjectByPriority()
{
	InputBufferingObjects.Sort([](const UInputBufferingObject& A, const UInputBufferingObject& B) {
		return A.Priority < B.Priority;
	});

	TArray<UInputBufferingObject*> PriorityBufferingObjects;
	int32 HighestPriority = InputBufferingObjects[0]->Priority;

	for(UInputBufferingObject* BufferingObject : InputBufferingObjects)
	{
		if(BufferingObject->Priority == HighestPriority)
		{
			PriorityBufferingObjects.Add(BufferingObject);
		}
		else
		{
			break; // 이미 정렬되있으니 나가도 괜찮
		}
	}
	if(PriorityBufferingObjects.Num()>1)
	{
		int32 Rand = FMath::RandRange(0, PriorityBufferingObjects.Num() - 1);
		return PriorityBufferingObjects[Rand];
	}
	
	return PriorityBufferingObjects[0];
}

void UInputHandler::SetupCommand(FInputPayLoad& InputPayLoad)
{
	UBaseStateObject* CurrentState = Cast<UBaseStateObject>(InputPayLoad.StateObject);
	if(!CurrentState)
		return;

	FGameplayTag& CurrentStateTag = CurrentState->StateGameplayTag;

	if(StateCommandMap.Contains(CurrentStateTag))
	{
		if(UBaseCommand* Command = StateCommandMap[CurrentStateTag])
		{
			BindCommand(Command);
		}
	}
}

void UInputHandler::SetupCommand(UInputBufferingObject* BufferObject)
{
	if(!BufferObject->StateObject) return;

	FGameplayTag& CurrentStateTag = BufferObject->StateObject->StateGameplayTag;

	
	if(StateCommandMap.Contains(CurrentStateTag))
	{
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

	TScriptInterface<IInterface_InputCommand> InputCommand;
	InputCommand.SetObject(CommandObject);
	InputCommand.SetInterface(Cast<IInterface_InputCommand>(CommandObject));

	if(InputCommand.GetInterface() != nullptr)
	{
		InputCommands.AddUnique(InputCommand);
	}
}

void UInputHandler::ExecuteCommand()
{
	AActor* OuterActor = Cast<AActor>(GetOuter());
	if(!OuterActor) return;

	SelectBufferingObject = SelectInputBufferingObject();
	if(!SelectBufferingObject) return;

	SetupCommand(SelectBufferingObject);
	
	if(!SelectBufferingObject) return;

	for(TScriptInterface<IInterface_InputCommand> InputCommand : InputCommands)
	{
		if(InputCommand.GetInterface() != nullptr)
		{
			InputCommand->Execute_ActionExecute(InputCommand.GetObject(), SelectBufferingObject);
		}
	}
	
}
