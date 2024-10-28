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
	// 입력 버퍼 생성을 차단하고 Command 를 Excute 합니다.
	// 핸들러에 저장되어있던 Buffer 를 전부 지우고 핸들러 자체도 GC 에게 마킹해줍니다.
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
	// 입력 버퍼를 생성하고 초기화합니다.
	UInputBufferingObject* NewBuffer = NewObject<UInputBufferingObject>(GetOwner(), UInputBufferingObject::StaticClass());
	NewBuffer->SetInputAction(Input);
	NewBuffer->InputTag = Tag;
	NewBuffer->SetOuterActor(OwnerActor);
	NewBuffer->SetOuterController(OwnerController);
	NewBuffer->SetInputManager(this);
	NewBuffer->SetStateObject(StateManagerComponent->GetCurrentActivateState());
	NewBuffer->SetAbilityObejct(AbilityManagerComponent->GetCurrentAbility());

	// 핸들러에게 해당 입력 버퍼를 받아서 저장할건지 확인하고 저장합니다.
	if(InputHandler->AddBufferingObject(NewBuffer))
	{
		// 만약 핸들러의 타입이 즉시 실행이면 바로 Command 를 실행합니다.
		if(InputHandler->GetInputPropertyType() == EInputPropertyType::Immediately)
		{
			BufferCreateClose();
		}
	}
	else
	{
		// 핸들러에서 이 입력버퍼를 받지 않으면 바로 삭제 마킹을 합니다.
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

