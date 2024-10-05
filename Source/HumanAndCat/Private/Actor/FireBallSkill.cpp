// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FireBallSkill.h"

#include "Components/SphereComponent.h"


// Sets default values
AFireBallSkill::AFireBallSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(50.0f); 
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll")); 
	CollisionComponent->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AFireBallSkill::BeginPlay()
{
	Super::BeginPlay();
		
	
}

// Called every frame
void AFireBallSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFireBallSkill::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCapsuleOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AFireBallSkill::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCapsuleEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

