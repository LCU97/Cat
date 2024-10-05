// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FireFallingSkill.h"

#include "Characters/BaseEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AFireFallingSkill::AFireFallingSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFireFallingSkill::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(110.0f); // �ݰ� ����
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); // �浹 �������� ����
	RootComponent = CollisionComponent;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkillActor::OnCapsuleOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASkillActor::OnCapsuleEndOverlap);
}

// Called every frame
void AFireFallingSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitialLifeSpan -= DeltaTime;
	if(InitialLifeSpan <= 0.f)
	{
		Destroy();
	}
}

void AFireFallingSkill::AttackingContinuous()
{
	for(auto Enemy : Enemys)
	{
		if(IsValid(Enemy))
		{
			float f = UGameplayStatics::ApplyDamage(Enemy, AttackStat, PlayerController, this, UDamageType::StaticClass());
			UE_LOG(LogTemp, Warning, TEXT("%f"), f);
		}
	}
}

void AFireFallingSkill::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
		if(Enemy)
		{
			Enemys.AddUnique(Enemy);
		}
	}
}

void AFireFallingSkill::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor && OtherActor != this)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
		if(IsValid(Enemy) && Enemys.Contains(Enemy))
		{
			Enemys.Remove(Enemy);
		}
	}
}

