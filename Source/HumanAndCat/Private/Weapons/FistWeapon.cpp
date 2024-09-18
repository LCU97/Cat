// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FistWeapon.h"


// Sets default values
AFistWeapon::AFistWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponTag = WeaponTags::Weapon_Fist;
	EquipSocket = FName(TEXT("FistEquipSocket"));
	UnEquipSocket = FName(TEXT("FistUnEquipSocket"));
}

// Called when the game starts or when spawned
void AFistWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFistWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

