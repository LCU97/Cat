// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "InputBufferingObject.generated.h"

class UBaseAbilityObject;
class UInputManagerComponent;
class UBaseStateObject;
class UInputAction;

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UInputBufferingObject : public UObject
{
	GENERATED_BODY()
public:
	UInputBufferingObject();

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadWrite)
	int32 Priority;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> OuterActor;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AController> OuterController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInputManagerComponent> InputManager;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBaseStateObject> StateObject;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UBaseAbilityObject> AbilityObject;
};
