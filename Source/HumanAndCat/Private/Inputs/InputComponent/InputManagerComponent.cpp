// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputComponent/InputManagerComponent.h"

#include "Components/BaseAbilityManagerComponent.h"
#include "Components/BaseStateManagerComponent.h"
#include "Inputs/Handlers/InputHandler.h"
#include "Inputs/InputBuffer/InputBufferingObject.h"


// Sets default values for this component's properties
UInputManagerComponent::UInputManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	
	// ...
}


// Called when the game starts
void UInputManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerController = Cast<AController>(GetOwner());
	OwnerActor = OwnerController->GetPawn();
	StateManagerComponent = OwnerController->GetComponentByClass<UBaseStateManagerComponent>();
	AbilityManagerComponent = OwnerActor->GetComponentByClass<UBaseAbilityManagerComponent>();
	
}


// Called every frame
void UInputManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInputManagerComponent::BufferCreateOpen()
{
	bIsBufferOpesn = true;
}

void UInputManagerComponent::BufferCreateClose()
{
	bIsBufferOpesn = false;

	if(IsValid(InputHandler))
	{
		InputHandler->ExecuteCommand();
		InputHandler->ClearBuffering();
		InputHandler->MarkAsGarbage();
	}
	InputHandler = nullptr;
}

bool UInputManagerComponent::IsBufferOpen()
{
	return bIsBufferOpesn;
}

void UInputManagerComponent::CreateBufferingObject(UInputAction* Input, FGameplayTag Tag)
{
	if(!bIsBufferOpesn || !InputHandler)
	{
		return;
	}
	UInputBufferingObject* NewBuffer = NewObject<UInputBufferingObject>(GetOwner(), UInputBufferingObject::StaticClass());
	NewBuffer->InputAction = Input;
	NewBuffer->InputTag = Tag;
	NewBuffer->OuterActor = OwnerActor;
	NewBuffer->OuterController = OwnerController;
	NewBuffer->InputManager = this;
	NewBuffer->StateObject = StateManagerComponent->GetCurrentActivateState();
	NewBuffer->AbilityObject = AbilityManagerComponent->GetCurrentAbility();

	if(InputHandler->AddBufferingObject(NewBuffer))
	{
		if(InputHandler->GetInputPropertyType() == EInputPropertyType::Immediately)
		{
			BufferCreateClose();
		}
	}
	else
	{
		NewBuffer->MarkAsGarbage();
	}
}

void UInputManagerComponent::SetInputHandler(UInputHandler* NewHandler)
{
	if(IsValid(InputHandler))
	{
		InputHandler =	nullptr;
	}
	InputHandler = NewHandler;
}

APawn* UInputManagerComponent::GetPlayerPawn()
{
	if(AController* Controller = Cast<AController>(GetOwner()))
	{
		return Controller->GetPawn();
	}
	return nullptr;
}

