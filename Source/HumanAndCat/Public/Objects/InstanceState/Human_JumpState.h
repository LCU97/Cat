// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_JumpState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : Jump"))
class HUMANANDCAT_API UHuman_JumpState : public UBaseStateObject
{
	GENERATED_BODY()
public:
	UHuman_JumpState();
	
public:
	virtual void StartState_Implementation() override;
	
	virtual void TickState_Implementation(float TickTime) override;

	virtual void EndState_Implementation() override;
};
