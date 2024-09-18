// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/BaseStateObject.h"
#include "Human_DeathState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName= "State : Death"))
class HUMANANDCAT_API UHuman_DeathState : public UBaseStateObject
{
	GENERATED_BODY()
};
