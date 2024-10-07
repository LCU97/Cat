// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "SwordWeapon.generated.h"

UCLASS()
class HUMANANDCAT_API ASwordWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwordWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SkillAttack(TSubclassOf<ASkillActor> SkillActor) override;
	virtual void SkillAttack2(TSubclassOf<ASkillActor> SkillActor) override;
	
};
