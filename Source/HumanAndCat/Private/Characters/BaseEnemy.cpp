// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	bHasAttackedPlayer = false;


}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseEnemy::MonsterAttackTrace(FName MonsterSoket, float _EndPoint, float Size)
{
	FVector _StartLocation = GetMesh()->GetSocketLocation(MonsterSoket);

	FRotator SocketRotation = GetMesh()->GetSocketRotation(MonsterSoket);

	FVector ForwardVector = SocketRotation.Vector();

	FVector _EndLocation = _StartLocation + ForwardVector * _EndPoint;


	FHitResult _HitOut;

	FCollisionQueryParams _TraceParams;
	_TraceParams.AddIgnoredActor(this);



	

	if (!bHasAttackedPlayer && GetWorld()->LineTraceSingleByChannel(_HitOut, _StartLocation, _EndLocation, ECC_GameTraceChannel2, _TraceParams))
	{
		AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (PlayerActor && _HitOut.GetActor())
		{
			if (_HitOut.GetActor() == PlayerActor)
			{
				DrawDebugLine(GetWorld(), _StartLocation, _EndLocation, FColor::Red, false, 2, 0, Size);
				bHasAttackedPlayer = true;

				GetWorldTimerManager().SetTimer(TimerHandle_ResetAttack, this, &ABaseEnemy::ResetAttack, 2.f, false);

			}
		}
	}

}

void ABaseEnemy::ResetAttack()
{
	bHasAttackedPlayer = false;
}

