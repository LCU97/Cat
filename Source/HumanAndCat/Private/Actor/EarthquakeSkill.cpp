// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EarthquakeSkill.h"

#include "Characters/BaseEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEarthquakeSkill::AEarthquakeSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent")); 
	CollisionComponent->InitSphereRadius(300.0f); 
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); 
	CollisionComponent->SetupAttachment(GetRootComponent());
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkillActor::OnCapsuleOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASkillActor::OnCapsuleEndOverlap);
	
	InitialLifeSpan = 0.5f;
}

// Called when the game starts or when spawned
void AEarthquakeSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEarthquakeSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InitialLifeSpan -= DeltaTime;
	if(InitialLifeSpan <= 0.f)
	{
		Destroy();
	}
}

void AEarthquakeSkill::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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

void AEarthquakeSkill::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

void AEarthquakeSkill::LaunchEarthquake(const FVector& CenterDirection)
{
	ACharacter* PCha = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if(!PCha) return;
	StartCollosionLocation = CenterDirection;
	CollisionComponent->SetWorldLocation(StartCollosionLocation);
}

