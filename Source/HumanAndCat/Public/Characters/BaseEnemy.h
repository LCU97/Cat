// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interface_Collision.h"
#include "BaseEnemy.generated.h"


USTRUCT(BlueprintType,Blueprintable)
struct FEnemyStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Hp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Atk;
	
};

UCLASS()
class HUMANANDCAT_API ABaseEnemy : public ACharacter, public IInterface_Collision
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void WhenItHit() override;
	virtual void WhenItHit_Implementation();
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEnemyStat EnemyStat;
	

public:

	void MonsterAttackTrace(FName MonsterSoket, float _EndPoint,float Size,float EnemyA);

	void ResetAttack();

private:
	bool bHasAttackedPlayer;	

	FTimerHandle TimerHandle_ResetAttack;
};
