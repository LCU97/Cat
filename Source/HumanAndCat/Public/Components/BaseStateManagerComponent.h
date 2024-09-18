// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "BaseStateManagerComponent.generated.h"

class UBaseStateObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HUMANANDCAT_API UBaseStateManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseStateManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeStateManagerComponent(AActor* PerformActor);

	UFUNCTION(BlueprintCallable)
	void ChangeStateOfClass(TSubclassOf<UBaseStateObject> State);

	UFUNCTION(BlueprintCallable)
	bool TryChangeStateOfTag(FGameplayTag StateGameplayTag, bool Condition = true);

	UFUNCTION(BlueprintCallable)
	bool TryChangeStateOfClass(TSubclassOf<UBaseStateObject> State, bool Condition = true);
	
	UFUNCTION(BlueprintCallable)
	bool TryChangeStatesOfClass(TArray<TSubclassOf<UBaseStateObject>> States, bool Condition);
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentActivateState(UBaseStateObject* NewCurrentState);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBaseStateObject* GetCurrentActivateState() { return CurrentActivateState;}

	// 활성화 가능 상태라면 현재상태를 end 하지 않고 새로운 상태를 start 하지 않고 실행한다.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetCanPerformStateOfClass(TSubclassOf<UBaseStateObject> WantToState);
	
	UFUNCTION(BlueprintCallable, BlueprintPure,BlueprintPure)
	void GetStateOfClass(TSubclassOf<UBaseStateObject> SearchState, UBaseStateObject*& FoundState);

	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintPure)
	UBaseStateObject* GetStateOfGameplayTag(FGameplayTag StateGameplayTag);

	UFUNCTION(BlueprintCallable)
	void ConstructStateOfClass(TSubclassOf<UBaseStateObject> CreateState, UBaseStateObject*& CreatedState);

	UFUNCTION(BlueprintCallable)
	void ClearStatesComponent();

	UFUNCTION(BlueprintCallable)
	void SetPreActivateState(UBaseStateObject* State) { PreActivateState = State; }

	UFUNCTION(BlueprintCallable,BlueprintPure)
	UBaseStateObject* GetPreActivateState() { return PreActivateState; }
	
public:
	// 현재 캐릭터 상황에 따른 활성화되어있는 상태를 담는 배열
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UBaseStateObject*> ActivateStates;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AActor* PerformingActor;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBaseStateObject* CurrentActivateState;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBaseStateObject* PreActivateState;
};
