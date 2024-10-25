// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "BaseAbilityManagerComponent.generated.h"


class UBaseAbilityObject;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HUMANANDCAT_API UBaseAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseAbilityManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	// 기본 기능 설정
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeAbilityManager();

	// 해당 능력을 실행
	UFUNCTION(BlueprintCallable)
	void PerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityObj);

	// 해당 능력을 실행 가능한지 판별 및 실행
	UFUNCTION(BlueprintCallable)
	bool TryPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> AbilityObj, bool Condition = true);

	// 여러 능력 중 한가지라도 실행가능하면 실행 시도 합니다.
	UFUNCTION(BlueprintCallable)
	bool TryPerformAbilitiesOfClass(TArray<TSubclassOf<UBaseAbilityObject>> AbilityObj, bool Condition = true);

	// 어빌리티 생성
	UFUNCTION(BlueprintCallable)
	void ContructAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility, UBaseAbilityObject*& ConstructAbility);

	UFUNCTION(BlueprintCallable)
	void ClearAbilityManager();
	
	// Get, Set -----------------------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetCurrentActivateAbility(UBaseAbilityObject* NewAbility);

	// 특정 능력을 반환하고 싶을때
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility, UBaseAbilityObject*& FoundAbility);

	// 특정 능력을 실행가능한지 확인할때
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetCanPerformAbilityOfClass(TSubclassOf<UBaseAbilityObject> WantToAbility);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGameplayTag GetCurrentAbilityTag();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBaseAbilityObject* GetAbilityOfGameplayTag(FGameplayTag AbilityTag);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBaseAbilityObject* GetCurrentAbility();
	
private:
	UPROPERTY(visibleAnywhere)
	UBaseAbilityObject* CurrentAbility;

	UPROPERTY(VisibleAnywhere)
	TArray<UBaseAbilityObject*> AbilityList;
	
};
