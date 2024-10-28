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

	// Get, Set
	TObjectPtr<UInputAction> GetInputAction() { return InputAction; }
	void SetInputAction(TObjectPtr<UInputAction> Input) { InputAction = Input; };

	int32 GetPriority() const { return Priority; }
	void SetPriority(int32 Idx) { this->Priority = Idx; }

	void SetOuterActor(const TObjectPtr<AActor>& Outer) { OuterActor = Outer; }
	void SetOuterController(const TObjectPtr<AController>& OuterCon) { OuterController = OuterCon; }

	void SetInputManager(const TObjectPtr<UInputManagerComponent>& InputManagerComp) { InputManager = InputManagerComp; }

	TObjectPtr<UBaseStateObject> GetStateObject() { return StateObject; }
	void SetStateObject(const TObjectPtr<UBaseStateObject>& State) { StateObject = State; }

	TObjectPtr<UBaseAbilityObject> GetAbilityObject() { return AbilityObject; }
	void SetAbilityObejct(const TObjectPtr<UBaseAbilityObject>& Ability) { AbilityObject = Ability; }
	
private:
	// 들어온 입력 값
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputAction = nullptr;
	
	// 이 버퍼의 우선순위
	UPROPERTY()
	int32 Priority;
	
	// 이 버퍼를 사용할 액터
	UPROPERTY()
	TObjectPtr<AActor> OuterActor;

	// 사용할 액터의 컨트롤러
	UPROPERTY()
	TObjectPtr<AController> OuterController;

	// Outer 가 가지는 입력 매니저
	UPROPERTY()
	TObjectPtr<UInputManagerComponent> InputManager;

	// Outer 가 사용중인 현재 State
	UPROPERTY()
	TObjectPtr<UBaseStateObject> StateObject;

	// Outer 가 사용중인 현재 Ability
	UPROPERTY()
	TObjectPtr<UBaseAbilityObject> AbilityObject;	
public:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FGameplayTag InputTag;

};
