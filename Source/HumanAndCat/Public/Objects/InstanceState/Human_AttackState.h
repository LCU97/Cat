// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_AttackState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="State : Attack"))
class HUMANANDCAT_API UHuman_AttackState : public UBaseStateObject
{
	GENERATED_BODY()
	
public:
	UHuman_AttackState();

public:
	virtual bool CanPerformState_Implementation() override;

	virtual void ConstructState_Implementation() override;

	virtual void StartState_Implementation() override;
	

	virtual void EndState_Implementation() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UBaseAbilityObject>> AttackAbilities;
	
};
