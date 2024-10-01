// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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


	if (GetWorld()->LineTraceSingleByChannel(_HitOut, _StartLocation, _EndLocation, ECC_GameTraceChannel1, _TraceParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *_HitOut.GetActor()->GetName());

	DrawDebugLine(GetWorld(), _StartLocation, _EndLocation, FColor::Green, false, 2, 0, Size);

		AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerActor && _HitOut.GetActor())
		{
			if (_HitOut.GetActor() == PlayerActor)
			{
				//UGameplayStatics::ApplyDamage(PlayerActor,);
			}
		}
	}
	
}


//FVector _StartLocation = GetMesh()->GetSocketLocation(StartPoint);
//
//FVector _EndLocation = _StartLocation + (GetActorForwardVector() * EndPoint);
//
//FHitResult _HitOut;
//FCollisionQueryParams _TraceParams;
//_TraceParams.AddIgnoredActor(this);
//
//DrawDebugLine(GetWorld(), _StartLocation, _EndLocation, FColor::Green, false, 5.f, 0, 2.f);
//
//
//if (GetWorld()->LineTraceSingleByChannel(_HitOut, _StartLocation, _EndLocation, ECC_GameTraceChannel1, _TraceParams))
//{
//
//}



//    FVector _StartLocation = GetMesh()->GetSocketLocation(MonsterSoket);
	//FVector _EndLocation = GetMesh()->GetSocketLocation(MonsterSoketEnd);
	//
	//FRotator SocketRotation = GetMesh()->GetSocketRotation(MonsterSoket);
	//
	//FVector ForwardVector = SocketRotation.Vector();
	//
	////_EndLocation = _StartLocation + ForwardVector * _EndLocation;
	//
	//
	//FHitResult _HitOut;
	//FCollisionQueryParams _TraceParams;
	//_TraceParams.AddIgnoredActor(this);
	//
	//
	//    DrawDebugLine(GetWorld(), _StartLocation, _EndLocation, FColor::Green, false, 2, 0, Size);
	//
	//if (GetWorld()->LineTraceSingleByChannel(_HitOut, _StartLocation, _EndLocation, ECC_GameTraceChannel1, _TraceParams))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("SIBAL"));
	//
	//
	//	AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	//	if (PlayerActor && _HitOut.GetActor())
	//	{
	//		if (_HitOut.GetActor() == PlayerActor)
	//		{
	//			//UGameplayStatics::ApplyDamage(PlayerActor,);
	//		}
	//	}
	//}