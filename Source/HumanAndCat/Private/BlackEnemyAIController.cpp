// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

void ABlackEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void ABlackEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    //GetWorld()->GetTimerManager().SetTimer(ChaseTimerHandle, this, &AMyAIController::StartChasingPlayer, 0.5f, true);
}

void ABlackEnemyAIController::ChasePlayer()
{
    MoveToActor(PlayerPawn, 500.0f);
}
