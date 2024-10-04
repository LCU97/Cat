// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "StaffWeapon.generated.h"

UCLASS()
class HUMANANDCAT_API AStaffWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStaffWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Equip() override;

	virtual void UnEquip() override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NiagaraComponent;
};

