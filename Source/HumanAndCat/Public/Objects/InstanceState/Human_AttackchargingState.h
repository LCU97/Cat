// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_AttackchargingState.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UHuman_AttackchargingState : public UBaseStateObject
{
	GENERATED_BODY()
public:
	UHuman_AttackchargingState();

public:
	virtual void StartState_Implementation() override;
	virtual void EndState_Implementation() override;

	virtual void TickState_Implementation(float DeltaTime) override;

	virtual bool CanPerformState_Implementation() override;
};
