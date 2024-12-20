// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "BaseAbilityObject.generated.h"

class UBaseStateManagerComponent;
class UBaseAbilityManagerComponent;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UBaseAbilityObject : public UObject
{
	GENERATED_BODY()
public:
	UBaseAbilityObject();

	public:
 // 어빌리티 기본 기능
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void ConstructAbility();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void StartAbility();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void TickAbility(float Delta);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void EndAbility();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void CancelAbility();

	// 쿨타임이 필요한 능력이라면 startability 할 때 넣어주자!!
	UFUNCTION(BlueprintCallable, Category="Ability")
	void ApplyAbilityCoolDown();

	UFUNCTION(BlueprintCallable, Category="Ability")
	void CoolDownReset();

	UFUNCTION(BlueprintCallable, Category="Ability")
	float PlayAbilityMontage(UAnimMontage* MontageAbility, float InplayRate = 1.f, EMontagePlayReturnType ReturnMontageType = EMontagePlayReturnType::MontageLength,
		float StartMontageTime =0.f, FName StartSection = NAME_None, bool bStopAllMontage = true);

	// 어빌리티 실행가능해? 쿨타임 중인지로 확인함
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	bool CanActivateAbility();

	// 다시 실행 가능한지도 쿨타임으로 체크함
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	bool CanReActivateAbility();
	
	// 어빌리티 기본 기능 끝
	
	// Get Set 시작
	// 쿨다운 중인지 확인
	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	bool GetOnCoolDown();

	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	void GetPerformingActor(AActor*& Actor);

	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	TArray<UAnimMontage*> GetAnimMontages(TSubclassOf<UBaseAbilityObject> SearchAbility);

	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	UAnimMontage* GetCurrentAbilityMontage();

	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	bool GetIsActivateAbility();

	UFUNCTION(BlueprintCallable, Category="Ability|Get")
	UBaseAbilityManagerComponent* GetAbilityManagerComponent();

	UFUNCTION(BlueprintCallable, Category="Ability|Set")
	void SetAbilityManagerComponent(UBaseAbilityManagerComponent* AbilityManagerComponent);

	UFUNCTION(BlueprintCallable, Category="Ability|Set")
	void SetPerformingActor(AActor* NewActor);

	UFUNCTION(BlueprintCallable, Category="Ability|Set")
	void SetActivateAbilityMontage(UAnimMontage* NewMontage);

public:
	// 해당 어빌리티를 특정해줄 Tag 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")
	FGameplayTag AbilityGameplayTag;
	
protected:
	// 실제 해당 어빌리티에서 실행 할 Montage 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")
	UAnimMontage* AbilityMontage;

	// 쿨타임 관련 멤버입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")
	bool bHasCooldown;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="Ability Var")
	float CooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")
	bool bAbilityOnCoolDown = true;

	FString CooldownResetFuncName = FString(TEXT("CooldownReset"));	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")

	// 매니저를 캐싱해둡니다.
	UBaseAbilityManagerComponent* AbilityManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability Var")
	UBaseStateManagerComponent* StateManager;
	
	UPROPERTY()
	AActor* PerformingActor;

};
