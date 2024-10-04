// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MidBoss.h"
#include "Components/MidBossFSM.h"


// Sets default values
AMidBoss::AMidBoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT(
															"/Script/Engine.SkeletalMesh'/Game/JEP/Monster/DragonTheSoulEaterSKJEP.DragonTheSoulEaterSKJEP'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-88), FRotator(0,-90,0));
		GetMesh()->SetRelativeScale3D(FVector(0.84f));
	}
	
	fsm = CreateDefaultSubobject<UMidBossFSM>(TEXT("FSM"));

	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT(
		"/Script/Engine.AnimBlueprint'/Game/JEP/Blueprints/ABP_MidBoss.ABP_MidBoss'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}
}

// Called when the game starts or when spawned
void AMidBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMidBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMidBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

