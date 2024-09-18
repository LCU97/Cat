// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/BasePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Components/BaseStateManagerComponent.h"

ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	StateManager = CreateDefaultSubobject<UBaseStateManagerComponent>(TEXT("StateManager"));
	
}

void ABasePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(APawn* PlayerPawn = GetPawn())
	{
		StateManager->InitializeStateManagerComponent(PlayerPawn);
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

