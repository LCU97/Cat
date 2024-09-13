// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "HumanAndCat/Public//DataAsset/WeaponProperties.h"
#include "WeaponComponent.generated.h"


class ABaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
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
	
	
	// Get Set
public:
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Get")
	TMap<FGameplayTag, UWeaponProperties*> GetWeapontype() {return WeaponType;}
	
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Get")
	void GetCurrentWeapon(ABaseWeapon*& CurrentActiveWeapon) {CurrentActiveWeapon = CurrentWeapon;}

	UFUNCTION(BlueprintCallable, Category = "Set")
	void SetCurrentWeapon(ABaseWeapon* NewWeapon) {CurrentWeapon = NewWeapon;}
	
	
	// Var
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	TMap<FGameplayTag, UWeaponProperties*> WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponType")
	ABaseWeapon* CurrentWeapon;
};
