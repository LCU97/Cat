// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interface_IndividualStatteFunc.h"
#include "Objects/BaseStateObject.h"
#include "Human_AttackState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="State : Attack"))
class HUMANANDCAT_API UHuman_AttackState : public UBaseStateObject, public IInterface_IndividualStatteFunc
{
	GENERATED_BODY()
	
public:
	UHuman_AttackState();

public:
	virtual bool CanPerformState_Implementation() override;

	virtual void ConstructState_Implementation() override;

	virtual void StartState_Implementation() override;
	
	virtual void EndState_Implementation() override;

	// IInterface_IndividualStatteFunc
	virtual void SetWantAbilityTag(FGameplayTag Tag) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UBaseAbilityObject>> AttackAbilities;
	
};
