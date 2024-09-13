// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "BaseStateObject.generated.h"

class UBaseStateManagerComponent;
class UBaseAbilityObject;
class UBaseAbilityManagerComponent;

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UBaseStateObject : public UObject
{
	GENERATED_BODY()
public:
	UBaseStateObject();

public:
	// 상태 생성 후 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	void ConstructState();

	// 상태의 시작 시 호출
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	void StartState();

	// 상태가 활성화되면 프레임마다 불려질 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	void TickState(float Delta);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	bool RestartState(bool Checking);

	// 상태가 종료되면 불려질 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	void EndState();

public:
	// 현재 능력 반환
	UFUNCTION(BlueprintPure, Category= "State|Ability|Get")
	TSubclassOf<UBaseAbilityObject> GetAbilityObject();

	// 새 능력 선택
	UFUNCTION(BlueprintCallable, Category = "State|Ability|Set")
	void SetAbilityObject(TSubclassOf<UBaseAbilityObject> AbilityObject);

	// 실행 가능한 능력을 찾습니다.	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "State|Ability")
	bool CheckAbilityExecute(UPARAM(ref) const TArray<TSubclassOf<UBaseAbilityObject>>& AbilityObjects);

	UFUNCTION(BlueprintCallable, Category = "State|Component|Get")
	UBaseStateManagerComponent* GetStateManager() const {return StateManager;}

	UFUNCTION(BlueprintCallable, Category = "State|Component|Set")
	void SetStateManager(UBaseStateManagerComponent* NewStateManager) { StateManager = NewStateManager;}

	UFUNCTION(BlueprintCallable)
	void SetRegisterPerformActor(AActor* PerformActor) { PerformActor = PerformActor; }
	
	UFUNCTION(BlueprintPure)
	void GetPerformingActor(AActor*& CurrentPerformActor) const { CurrentPerformActor = PerformingActor;}

	UFUNCTION(BlueprintPure)
	bool GetIsStateCurrentlyActive();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	bool CanPerformState();
	
public:
	// 해당 상태의 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State|Property")
	FGameplayTag StateGameplayTag;

	// 해당 상태를 관리하는 상태 매니저
	UPROPERTY(BlueprintReadWrite, Category = "State|Component")
	UBaseStateManagerComponent* StateManager;

	// 실제 사용되어질 능력
	UPROPERTY(BlueprintReadWrite, Category = "State|Ability")
	TSubclassOf<UBaseAbilityObject> CurrentAbility;

	// 해당 상태에서 사용 가능한 능력을 배열로 관리합니다.
	UPROPERTY(BlueprintReadWrite, Category = "State|Ability")
	TArray<TSubclassOf<UBaseAbilityObject> > EnableAbilities;

	public:
	UPROPERTY()
	AActor* PerformingActor;

	
};
