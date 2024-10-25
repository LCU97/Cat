// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/ANS_BufferInput.h"
#include "Inputs/Handlers/InputHandler.h"
#include "Inputs/InputComponent/InputManagerComponent.h"

UANS_BufferInput::UANS_BufferInput()
{
}

void UANS_BufferInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	if (UInputManagerComponent* InputManagerComponent = GetOwnerInputManagerComponent(MeshComp))
	{
		// 설정된 핸들러를 새 핸들러에 저장하고 이것을 InputComponent 에게 넘겨줍니다.
		NewInputCommandHandler = DuplicateObject(InputCommandHandler, MeshComp->GetOwner());
		InputManagerComponent->SetInputHandler(NewInputCommandHandler);
		// InputBuffer 생성을 시작합니다.
		InputManagerComponent->BufferCreateOpen();
	}
}

void UANS_BufferInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (UInputManagerComponent* InputManagerComponent = GetOwnerInputManagerComponent(MeshComp))
	{
		// InputBuffer 생성을 차단하고 다음 행동을 처리합니다.
		if (InputManagerComponent->IsBufferOpen())
			InputManagerComponent->BufferCreateClose();
	}
}

FString UANS_BufferInput::GetNotifyName_Implementation() const
{
	return FString(TEXT("InputSystem"));
}

UInputManagerComponent* UANS_BufferInput::GetOwnerInputManagerComponent(USkeletalMeshComponent* MeshComp) const
{
	// InputComponent 를 반환합니다.
	if (!IsValid(MeshComp))
	{
		return nullptr;
	}
	 APawn* OwnerPawn = Cast<APawn>(MeshComp->GetOwner());
	if (!IsValid(OwnerPawn))
	{
		return nullptr;
	}
	 AController* OwnerController = OwnerPawn->GetController();
	if (!IsValid(OwnerController))
	{
		return nullptr;
	}
	return Cast<UInputManagerComponent>(OwnerController->GetComponentByClass(UInputManagerComponent::StaticClass()));
}
