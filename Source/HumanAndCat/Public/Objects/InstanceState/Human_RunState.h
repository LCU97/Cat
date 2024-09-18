// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_RunState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : Run"))
class HUMANANDCAT_API UHuman_RunState : public UBaseStateObject
{
	GENERATED_BODY()
	public:
	UHuman_RunState();

	public:
	virtual void TickState_Implementation(float Delta) override;

	virtual bool CanPerformState_Implementation() override;
};
