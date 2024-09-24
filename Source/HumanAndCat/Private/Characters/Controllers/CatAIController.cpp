#include "Characters/Controllers/CatAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ACatAIController::ACatAIController()
{
	ACharacter* CatAiCharacter = Cast<ACharacter>(GetPawn());
	if (CatAiCharacter)
	{
		CatAiCharacter->bUseControllerRotationYaw = false;
		CatAiCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		CatAiCharacter->GetCharacterMovement()->MaxAcceleration = 800.f;
		CatAiCharacter->GetCharacterMovement()->BrakingDecelerationWalking = 350.f;
	}
}

void ACatAIController::BeginPlay()
{
	Super::BeginPlay();

	//PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//GetWorldTimerManager().SetTimer(TimerHandle, this, &ACatAIController::FollowPlayer, 0.5f, true);
}

void ACatAIController::FollowPlayer()
{
	if (PlayerPawn)
	{
		//MoveToActor(PlayerPawn, AcceptanceRadius);
	}
}
