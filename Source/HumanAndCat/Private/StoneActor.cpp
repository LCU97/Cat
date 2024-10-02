// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneActor.h"

// Sets default values
AStoneActor::AStoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	StoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StoneMesh"));
	RootComponent = StoneMesh;

	ZSpeed = 0;
	ZAmplitude = 50;

	XSpeed = 0;
	XAmplitude = 50;

	YSpeed = 0;
	YAmplitude = 50;
}

// Called when the game starts or when spawned
void AStoneActor::BeginPlay()
{
	Super::BeginPlay();
	

	InitialLocation = GetActorLocation();
}

// Called every frame
void AStoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// 경과 시간 누적
	ElapsedTime += DeltaTime;

	// 경과 시간에 따라 스톤 엑터의 Z축 위치 업데이트 (사인파 기반 상하 움직임)
	FVector NewLocation = InitialLocation;
	NewLocation.Z += ZAmplitude * FMath::Sin(ZSpeed * ElapsedTime);
	NewLocation.X += XAmplitude * FMath::Sin(XSpeed * ElapsedTime);
	NewLocation.Y += YAmplitude * FMath::Sin(YSpeed * ElapsedTime);




	SetActorLocation(NewLocation);
}

