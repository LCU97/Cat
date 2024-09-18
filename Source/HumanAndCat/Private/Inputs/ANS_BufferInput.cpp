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
		NewInputCommandHandler = DuplicateObject(InputCommandHandler, MeshComp->GetOwner());
		InputManagerComponent->SetInputHandler(NewInputCommandHandler);
		InputManagerComponent->BufferCreateOpen();
	}
}

void UANS_BufferInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (UInputManagerComponent* InputManagerComponent = GetOwnerInputManagerComponent(MeshComp))
	{
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
	if (!IsValid(MeshComp))
	{
		return nullptr;
	}

	const APawn* OwnerPawn = Cast<APawn>(MeshComp->GetOwner());
	if (!IsValid(OwnerPawn))
	{
		return nullptr;
	}

	const AController* OwnerController = OwnerPawn->GetController();
	if (!IsValid(OwnerController))
	{
		return nullptr;
	}

	return Cast<UInputManagerComponent>(OwnerController->GetComponentByClass(UInputManagerComponent::StaticClass()));
}
