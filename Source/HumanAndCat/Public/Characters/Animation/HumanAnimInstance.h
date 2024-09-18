// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DataAsset/WeaponProperties.h"
#include "HumanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UHumanAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	public:

	UFUNCTION(BlueprintCallable)
	void SetWeaponName(EWeaponName NewWeapon) { WeaponName = NewWeapon;}

	UFUNCTION(BlueprintCallable)
	void SetInCombat(bool CombatBool) {bInCombat = CombatBool; }
	
public:
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsFalling;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsWeaponComponentBound;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsCombatComponentBound;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	bool bInCombat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	EWeaponName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float RunSpeed;

	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	class ACharacter* PlayerCharacter;
};
