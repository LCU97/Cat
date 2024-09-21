// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Controllers/CatAIController.h"

ACatAIController::ACatAIController()
{
	
}

void ACatAIController::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* CatAiCharacter = Cast<ACharacter>(GetPawn());
	if (CatAiCharacter)
	{
		CatAiCharacter->bUseControllerRotationYaw = false;
		CatAiCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		CatAiCharacter->GetCharacterMovement()->MaxAcceleration = 500.f;
		CatAiCharacter->GetCharacterMovement()->BrakingDecelerationWalking = 350.f;
	}

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACatAIController::FollowPlayer, 0.5f, true);
}

void ACatAIController::FollowPlayer()
{
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, AcceptanceRadius);
	}
}
