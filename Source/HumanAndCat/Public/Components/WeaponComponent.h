// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "HumanAndCat/Public//DataAsset/WeaponProperties.h"
#include "WeaponComponent.generated.h"


class ABaseWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponNameChanged, EWeaponName, NewWeaponName);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HUMANANDCAT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	//WeaopnComponent Base Function
	UFUNCTION(BlueprintCallable)
	void InitWeaponComponent();
	void UpdateStates();
	void UpdateAbilities();

	// Get Set
public:
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Get")
	TMap<FGameplayTag, UWeaponProperties*> GetWeapontype() {return WeaponTypes;}
	
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Get")
	void GetCurrentWeapon(ABaseWeapon*& CurrentActiveWeapon) {CurrentActiveWeapon = CurrentWeapon;}

	UFUNCTION(BlueprintCallable)
	void GetCurrentWeaponType(UWeaponProperties*& Types) {Types = CurrentWeaponType;}
	
	UFUNCTION(BlueprintCallable)
	void GetCurrentWeaponTag(FGameplayTag& Tags) {Tags = CurrentWeaponTag;}
	
	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetCurrentWeapon(ABaseWeapon* NewWeapon) {CurrentWeapon = NewWeapon;}

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeaponType(UWeaponProperties* Types) {CurrentWeaponType = Types;}\

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeaponTag(FGameplayTag Tags) {CurrentWeaponTag = Tags;}
	public:
	// WeaponComponent Func
	UFUNCTION(BlueprintCallable)
	void RegisterStateAndAbility(ABaseWeapon* CheckingWeaponType);

	UFUNCTION(BlueprintCallable)
	void UnregisterStateAndAility();

	UFUNCTION(BlueprintCallable)
	void Equip();

	UFUNCTION(BlueprintCallable)
	void UnEquip();
	
	// Var
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	TMap<FGameplayTag, UWeaponProperties*> WeaponTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	ABaseWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	UWeaponProperties* CurrentWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	FGameplayTag CurrentWeaponTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	EWeaponName CurrentWeaponName;
	
	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "WeaponType")
	TSubclassOf<ABaseWeapon> BasicWeapon;

	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "WeaponType")
	ABaseWeapon* BasicWeaponInstanced;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentWeaponLength;

	// 무기 바뀐거 애님인스턴스에게 알려주기
	UPROPERTY(BlueprintAssignable)
	FOnWeaponNameChanged OnWeaponNameChanged;
};
