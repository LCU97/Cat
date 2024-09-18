// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_UnEquipState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : UnEquip"))
class HUMANANDCAT_API UHuman_UnEquipState : public UBaseStateObject
{
	GENERATED_BODY()
public:
	UHuman_UnEquipState();

public:
	virtual void StartState_Implementation() override;
	virtual void EndState_Implementation() override;

	virtual bool CanPerformState_Implementation() override;

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseAbilityObject> UnEquipAbility;
};
