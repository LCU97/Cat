// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCombatComponent.generated.h"

class UCameraComponent;

// 1. 전투 상태에 들어갔는지 확인 가능하며 Delegate 를 활용해 전투 상태 시 다른 클래스의 함수를 BroadCast 하는 역할.
// 2. 타겟팅 기능을 포함.
// 3. 헤더에서는 주요 멤버 주석, cpp 에서는 주요 함수 주석을 달았습니다.

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

// 타겟팅 함수 ~~end
	
	// Get, Set
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetInCombat() {return bInCombat;}
	
	UFUNCTION(BlueprintCallable, Category="Get")
	AActor* GetTargetActor() { return TargetActor; }
	
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetInCombat(bool NewCombet) { bInCombat = NewCombet; }

public:
	// 델리게이트를 활용한 공격 시작 시 혹은 포커싱 시작 시 event 효과
	UPROPERTY(BlueprintAssignable)
	FOnInCombatChanged OnInCombatChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnInFocusing OnInFocusing;
	

	
private:
	
	// 실제 타겟팅 액터
	UPROPERTY(EditAnywhere,  Category="Target")
	AActor* TargetActor = nullptr;

	// 타겟팅 가능한 영역 안에 있는 액터
	UPROPERTY(EditAnywhere,  Category="Target")
	TArray<AActor*> FocusingTargets;

	// 타겟팅 할 액터를 찾는 원의 반경
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta = (AllowPrivateAccess = "true"))
	float TargetingRadius = 1500.f;

	// 실제 타겟팅 액터로 선정될 액터가 어떤 클래스를 포함하는지 예) Character, Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta = (AllowPrivateAccess = "true"))
	UClass* TargetClass = nullptr;

	// 타겟팅 액터의 오브젝트 타입 선정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetsType;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* OwnerCamera = nullptr;
	
	// 공격 상태 확인 변수
	UPROPERTY(EditAnywhere, Category="Combat")
	bool bInCombat = false;

	UPROPERTY(EditAnywhere, Category="Combat")
	bool bIsTarget = false;
};
