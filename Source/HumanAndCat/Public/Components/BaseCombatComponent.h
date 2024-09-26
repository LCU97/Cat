// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCombatComponent.generated.h"

class UCameraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInCombatChanged, bool, CombatBool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInFocusing, bool, FocusBool);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HUMANANDCAT_API UBaseCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
// 타겟팅 함수
	UFUNCTION(BlueprintCallable)
	void InitCombatComponent(UCameraComponent* CameraComponent);
	
	UFUNCTION(BlueprintCallable)
	void SearchTargetActor();

	UFUNCTION(BlueprintCallable)
	void FindInRandgeTargets();

	UFUNCTION(BlueprintCallable)
	void SelectTarget();

	UFUNCTION(BlueprintCallable)
	float CalculateAngleFromCamera(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void DisableLockOn();


	UFUNCTION(BlueprintCallable)
	void LockOnTarget();

	UFUNCTION(BlueprintCallable)
	bool CanBeTargeted(AActor* Target);
// 타겟팅 함수 ~~end
	// Get, Set
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetInCombat() {return bInCombat;}
	
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetInCombat(bool NewCombet) { bInCombat = NewCombet; }

public:

	// 공격 상태 확인 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bInCombat = false;

	// 실제 타겟팅 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	AActor* TargetActor = nullptr;

	// 타겟팅 가능한 영역 안에 있는 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	TArray<AActor*> FocusingTargets;

	// 타겟팅 할 액터를 찾는 원의 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	float TargetingRadius = 1500.f;

	// 실제 타겟팅 액터로 선정될 액터가 어떤 클래스를 포함하는지 예) Character, Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	UClass* TargetClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetsType;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* OwnerCamera = nullptr;

	UPROPERTY(BlueprintAssignable)
	FOnInCombatChanged OnInCombatChanged;

	
	UPROPERTY(BlueprintAssignable)
	FOnInFocusing OnInFocusing;

};
