// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DataAsset/WeaponProperties.h"
#include "HumanAnimInstance.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewWeaponNameChanged, EWeaponName, NewWeaponName);
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

	UFUNCTION(BlueprintCallable)
	void SetFocusing(bool FocusBool) { bFocusing = FocusBool; }
	
public:
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsFalling;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsWeaponComponentBound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsCombatComponentBound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsTargetingBound;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bInCombat;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bFocusing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	EWeaponName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class ACharacter* PlayerCharacter;

	FOnNewWeaponNameChanged OnNewWeaponNameChanged;
};
