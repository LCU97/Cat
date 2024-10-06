// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseEnemy.h"
#include "BlackEnemyCharacter.generated.h"


//USTRUCT(BlueprintType)
//struct FBlackEnemy
//{
//	GENERATED_BODY()
//
//	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
//	 float Hp;
//
//	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
//	 float AttackPower;
//
//	 FBlackEnemy()
//		 :Hp(500)
//		 , AttackPower(50)
//	 {}
//};

UCLASS()
class HUMANANDCAT_API ABlackEnemyCharacter : public ABaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlackEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void WhenItHit() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* weaponSkeletaMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* MaskSkeletaMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* shuriken;

	FTimerHandle TimerHandle_Destroy;

	void OnDeathMontageFinished();
};
