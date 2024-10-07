// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SwordWeapon.h"

#include "Actor/EarthquakeSkill.h"
#include "Actor/SplitEarthSkill.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/TextFilterExpressionEvaluator.h"


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

void ASwordWeapon::SkillAttack(TSubclassOf<ASkillActor> SkillActor)
{
	Super::SkillAttack(SkillActor);

	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!PCharacter) return;

	FTransform transform = PCharacter->GetMesh()->GetSocketTransform(FName("SplitEarth"));
	FVector Forward = transform.GetRotation().GetForwardVector();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	ASplitEarthSkill* SplitEarthSkill = GetWorld()->SpawnActor<ASplitEarthSkill>(SkillActor, transform.GetLocation(), Forward.Rotation(), SpawnParams);
	if(SplitEarthSkill)
	{
		SplitEarthSkill->LaunchSplitEarth(transform.GetLocation(), PCharacter->GetActorForwardVector());
	}
}

void ASwordWeapon::SkillAttack2(TSubclassOf<ASkillActor> SkillActor)
{
	Super::SkillAttack2(SkillActor);

	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!PCharacter) return;

	FVector Forward = WeaponManager->GetOwner()->GetActorForwardVector();

	FVector NewLocation = PCharacter->GetActorLocation() + Forward * 10.f;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AEarthquakeSkill* EarthquakeSkill = GetWorld()->SpawnActor<AEarthquakeSkill>(SkillActor, NewLocation, Forward.Rotation(), SpawnParams);
	if(EarthquakeSkill)
	{
		EarthquakeSkill->LaunchEarthquake(NewLocation);
	}
		

}

