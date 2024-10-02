// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MidBossFSM.generated.h"

UENUM(BlueprintType)
enum class EMidBossState: uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUMANANDCAT_API UMidBossFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMidBossFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EMidBossState mState = EMidBossState::Idle;
	
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2;
	float currentTime = 0;

	UPROPERTY(VisibleAnywhere, Category=FSM)
	class AAdventurePlayer* player;

	UPROPERTY()
	class AMidBoss* me;

	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float attackDelayTime = 2.0f;

	void OnDamageProcess();		// event function

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	int32 hp = 3;

	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 2.0f;

	UPROPERTY(EditAnywhere, Category=FSM)
	float dieSpeed = 50.0f;

	UPROPERTY()
	class UMidBossAnim *anim;

	UPROPERTY()
	class AAIController *ai;

	FVector randomPos;
	bool GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector &dest);	
};
