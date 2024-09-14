// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AdventurePlayer.h"



// Sets default values
AAdventurePlayer::AAdventurePlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAdventurePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdventurePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAdventurePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


