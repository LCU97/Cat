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

	// WeaponComponent Func
	UFUNCTION(BlueprintCallable)
	void RegisterStateAndAbility(ABaseWeapon* CheckingWeaponType);

	UFUNCTION(BlueprintCallable)
	void UnregisterStateAndAility();

	UFUNCTION(BlueprintCallable)
	void Equip();

	UFUNCTION(BlueprintCallable)
	void UnEquip();

public:	
	// 무기 바뀐거 애님인스턴스에게 알려주기
	UPROPERTY(BlueprintAssignable)
	FOnWeaponNameChanged OnWeaponNameChanged;

	// Var
private:
	// 현재 무기 의 tag 에 따른 DataAsset 입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, UWeaponProperties*> WeaponTypes;
	
	// 현재 무기와 관련한 멤버 입니다.Start
	UPROPERTY(EditAnywhere, Category = "WeaponType")
	ABaseWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "WeaponType")
	UWeaponProperties* CurrentWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType", meta = (AllowPrivateAccess = "true"))
	FGameplayTag CurrentWeaponTag;

	UPROPERTY(EditAnywhere, Category = "WeaponType")
	EWeaponName CurrentWeaponName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CurrentWeaponLength;

	// 현재 무기와 관련한 멤버 End~!!!

	// 처음 시작 시 기초 무기와 관련한 멤버! Start
	UPROPERTY(EditAnywhere,	BlueprintReadWrite, Category = "WeaponType", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseWeapon> BasicWeapon;

	UPROPERTY(EditAnywhere,	Category = "WeaponType")
	ABaseWeapon* BasicWeaponInstanced;
	// 처음 시작 시 기초 무기와 관련한 멤버! End!!

	// Onwer 를 형변환!
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEquip;
};
