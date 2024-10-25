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
	bool RestartState(bool Checking = true);

	// 상태가 종료되면 불려질 함수
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Events")
	void EndState();

	// 현재 능력 반환
	UFUNCTION(BlueprintPure,BlueprintCallable, Category= "State|Ability|Get")
	TSubclassOf<UBaseAbilityObject> GetAbilityObject();

	// 실행 가능한 능력을 찾습니다.	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "State|Ability")
	bool CheckAbilityExecute(UPARAM(ref) const TArray<TSubclassOf<UBaseAbilityObject>>& AbilityObjects);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	bool CanPerformState();

	// TargetObject
	UFUNCTION(BlueprintCallable)
	void RotateToTarget(float Alpha);

public:
	
	// Get, Set-----------------------------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = "State|Component|Get")
	UBaseStateManagerComponent* GetStateManager() const {return StateManager;}

	UFUNCTION(BlueprintCallable, Category = "State|Component|Set")
	void SetStateManager(UBaseStateManagerComponent* NewStateManager) { StateManager = NewStateManager;}

	UFUNCTION(BlueprintCallable)
	void SetRegisterPerformActor(AActor* PerformActor) { PerformingActor = PerformActor; }
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	void GetPerformingActor(AActor*& CurrentPerformActor) const { CurrentPerformActor = PerformingActor;}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<UBaseAbilityObject> GetCurrentAbility(){return CurrentAbility;}
	
	UFUNCTION(BlueprintPure)
	bool GetIsStateCurrentlyActive();

	// 새 능력 선택
	UFUNCTION(BlueprintCallable, Category = "State|Ability|Set")
	void SetAbilityObject(TSubclassOf<UBaseAbilityObject> AbilityObject);

public:
	
	// 해당 상태의 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "State|Property")
	FGameplayTag StateGameplayTag;
	
	// 각 상태별 원하는 Ability 가 있다면 여기에 저장합니다.
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag WantToAbility;
	
protected:

	// 해당 상태를 관리하는 상태 매니저
	UPROPERTY(BlueprintReadWrite, Category = "State|Component")
	UBaseStateManagerComponent* StateManager;

	UPROPERTY(BlueprintReadWrite, Category= "State|Component")
	UBaseAbilityManagerComponent* AbilityManager;

	// 실제 사용되어질 능력
	UPROPERTY(BlueprintReadWrite, Category = "State|Ability")
	TSubclassOf<UBaseAbilityObject> CurrentAbility;

	// 해당 상태에서 사용 가능한 능력을 배열로 관리합니다.
	UPROPERTY(BlueprintReadWrite, Category = "State|Ability")
	TArray<TSubclassOf<UBaseAbilityObject> > EnableAbilities;

	// State 를 사용하는 캐릭터
	UPROPERTY()
	AActor* PerformingActor;

	// Character 로 형변환
	UPROPERTY(BlueprintReadWrite, Category= "State|Normal")
	ACharacter* OwnerCharacter;

	// 현재 상태로 변경 시도 할 때 현재 상태가 이 컨테이너에 존재한다면 상태 변환 불가능
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category= "State|Normal")
	FGameplayTagContainer BlockedState;

	
};
