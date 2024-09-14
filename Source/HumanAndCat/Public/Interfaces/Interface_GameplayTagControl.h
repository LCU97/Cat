// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "Interface_GameplayTagControl.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UInterface_GameplayTagControl : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HUMANANDCAT_API IInterface_GameplayTagControl
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Blueprintable)
	virtual void AddGameplayTag(FGameplayTag Tag) = 0;

	UFUNCTION(Blueprintable)
	virtual void RemoveGameplayTag(FGameplayTag Tag) = 0;	
};
