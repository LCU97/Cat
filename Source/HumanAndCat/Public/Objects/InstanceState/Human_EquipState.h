// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_EquipState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : Equip"))
class HUMANANDCAT_API UHuman_EquipState : public UBaseStateObject
{
	GENERATED_BODY()
	public:
	UHuman_EquipState();
public:
	virtual void StartState_Implementation() override;
	virtual void EndState_Implementation() override;

	virtual bool CanPerformState_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBaseAbilityObject> EquipAbility;	
};
