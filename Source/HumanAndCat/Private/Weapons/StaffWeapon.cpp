// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/StaffWeapon.h"
#include "NiagaraComponent.h"
#include "Actor/SkillActor.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AStaffWeapon::AStaffWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponTag = WeaponTags::Weapon_Staff;
	EquipSocket = FName(TEXT("StaffEquipSocket"));
	UnEquipSocket = FName(TEXT("StaffUnEquipSocket"));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AStaffWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaffWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaffWeapon::Equip()
{
	Super::Equip();
	if(NiagaraComponent->GetAsset())
	{
		NiagaraComponent->SetActive(true);
	}
}

void AStaffWeapon::UnEquip()
{
	Super::UnEquip();
	if(NiagaraComponent->GetAsset())
	{
		NiagaraComponent->SetActive(false);
	}
}

void AStaffWeapon::SkillAttack(TSubclassOf<ASkillActor> SkillActor)
{
	Super::SkillAttack(SkillActor);

	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	if(!PCharacter) return;
	
	FTransform SpawnTransform;

	FRotator StartRotator = PCharacter->GetControlRotation();

	FRotator SpawnRotator = FRotator(0, StartRotator.Yaw, 0);

	FVector ForwardVec = PCharacter->GetActorForwardVector();

	FVector SpawnLocation = PCharacter->GetActorLocation() + (ForwardVec * 1000.f);
	SpawnLocation.Z = PCharacter->GetActorLocation().Z;

	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotator.Quaternion());

	if(SkillActor)
	{
		ASkillActor* SpawnedSkill = GetWorld()->SpawnActor<ASkillActor>(SkillActor, SpawnTransform);
	}
}

