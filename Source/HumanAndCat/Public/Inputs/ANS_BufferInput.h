// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_BufferInput.generated.h"

class UInputHandler;
class UInputManagerComponent;
/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UANS_BufferInput : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UANS_BufferInput();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;

protected:
	UInputManagerComponent* GetOwnerInputManagerComponent(USkeletalMeshComponent* MeshComp) const;

protected:
	UPROPERTY(Instanced, BlueprintReadOnly, EditAnywhere, Category="ANS Buffer Input")
	UInputHandler* InputCommandHandler;

private:
	UPROPERTY()
	UInputHandler* NewInputCommandHandler;
	
};
