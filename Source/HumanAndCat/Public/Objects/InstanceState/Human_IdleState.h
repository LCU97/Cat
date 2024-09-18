// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_IdleState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : Idle"))
class HUMANANDCAT_API UHuman_IdleState : public UBaseStateObject
{
	GENERATED_BODY()
	public:
	UHuman_IdleState();

	public:
	virtual void TickState_Implementation(float Delta) override;

	virtual bool CanPerformState_Implementation() override;
};
