// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Utilities/HumanAndCatTags.h"
#include "BaseWeapon.generated.h"

class UWeaponComponent;
class ASkillActor;

UCLASS()
class HUMANANDCAT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Get Set

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Get")
	FName GetEquipSocket(){return EquipSocket;}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Get")
	FName GetUnEquipSocket(){return UnEquipSocket;}
	
	UFUNCTION(BlueprintCallable)
	void SetWeaponManager(UWeaponComponent* WeaponComp) { WeaponManager = WeaponComp;}

	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	UFUNCTION(BlueprintCallable)
	virtual void UnEquip();

	UFUNCTION(BlueprintCallable)
	virtual void SkillAttack(TSubclassOf<ASkillActor> SkillActor);

	UFUNCTION(BlueprintCallable)
	virtual void SkillAttack2(TSubclassOf<ASkillActor> SkillActor);
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGameplayTag WeaponTag;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWeaponComponent* WeaponManager;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName EquipSocket;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName UnEquipSocket;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float TraceLength;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAttackable;
};
