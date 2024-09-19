// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SwordWeapon.h"


// Sets default values
ASwordWeapon::ASwordWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponTag = WeaponTags::Weapon_Sword;
	EquipSocket = FName(TEXT("SwordEquipSocket"));
	UnEquipSocket = FName(TEXT("SwordUnEquipSocket"));
}

// Called when the game starts or when spawned
void ASwordWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwordWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

