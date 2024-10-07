// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SplitEarthSkill.h"

#include "Characters/BaseEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASplitEarthSkill::ASplitEarthSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent")); 
	CollisionComponent->InitSphereRadius(20.0f); 
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); 
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkillActor::OnCapsuleOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASkillActor::OnCapsuleEndOverlap);
	
	InitialLifeSpan = 1.f;
}

// Called when the game starts or when spawned
void ASplitEarthSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplitEarthSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitialLifeSpan -= DeltaTime;
	if(InitialLifeSpan <= 0.f)
	{
		Destroy();
	}
	SphereRadius += 300.f * DeltaTime;
	CollisionComponent->SetSphereRadius(SphereRadius);

	float MoveSpeed = 1050.f;
	
	FVector NewLocation = CollisionComponent->GetComponentLocation() + Dir * MoveSpeed * DeltaTime;
	CollisionComponent->SetWorldLocation(NewLocation);
}

void ASplitEarthSkill::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(OtherActor) && OtherActor != this)
	{
		ABaseEnemy* Enemy = Cast<ABaseEnemy>(OtherActor);
		if(Enemy && !Enemys.Contains(Enemy))
		{
			UGameplayStatics::ApplyDamage(Enemy, AttackStat, PlayerController, this, UDamageType::StaticClass());
			Enemys.AddUnique(Enemy);
		}
	}
}

void ASplitEarthSkill::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void ASplitEarthSkill::LaunchSplitEarth(const FVector& CenterDirection, const FVector& Direction)
{
	ACharacter* PCha = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!PCha) return;
	StartCollosionLocation = CenterDirection;
	Dir = Direction.GetSafeNormal();
	CollisionComponent->SetWorldLocation(StartCollosionLocation);
}

