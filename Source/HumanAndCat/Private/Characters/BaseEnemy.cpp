// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"


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

void ABaseEnemy::MonsterAttackTrace(FName MonsterSoket, float _EndPoint, float Size,float EnemyA)
{
	FVector _StartLocation = GetMesh()->GetSocketLocation(MonsterSoket);

	FRotator SocketRotation = GetMesh()->GetSocketRotation(MonsterSoket);

	FVector ForwardVector = SocketRotation.Vector();

	FVector _EndLocation = _StartLocation + ForwardVector * _EndPoint;


	FHitResult _HitOut;

	// 충돌 무시할 액터 설정 (자기 자신 무시)
	FCollisionQueryParams _TraceParams;
	_TraceParams.AddIgnoredActor(this);

	// 구체 충돌 모양 생성 (반지름은 Size 사용)
	FCollisionShape SphereCollisionShape = FCollisionShape::MakeSphere(Size);


	// SweepSingleByChannel을 사용하여 구체 기반 충돌 감지
	if (!bHasAttackedPlayer && GetWorld()->SweepSingleByChannel(_HitOut, _StartLocation, _EndLocation, FQuat::Identity, ECC_GameTraceChannel2, SphereCollisionShape, _TraceParams))
	{
		AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (PlayerActor && _HitOut.GetActor())
		{
			if (_HitOut.GetActor() == PlayerActor)
			{
				// 플레이어를 공격한 상태로 설정
				bHasAttackedPlayer = true;

				// 디버그 라인 그리기 (충돌 경로 시각화)
				//DrawDebugSphere(GetWorld(), _StartLocation, Size, 12, FColor::Green, false, 2.0f); // 시작점
				//DrawDebugSphere(GetWorld(), _EndLocation, Size, 12, FColor::Red, false, 2.0f);    // 끝점



				// 데미지 적용
				TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
				UGameplayStatics::ApplyDamage(_HitOut.GetActor(), EnemyA, GetController(), this, DamageType);

				// 2초 후에 공격 상태 초기화DrawDebugSphere(GetWorld(), _StartLocation, Size, 12, FColor::Green, false, 2.0f); // 시작점
				DrawDebugSphere(GetWorld(), _EndLocation, Size, 12, FColor::Red, false, 2.0f);    // 끝점
				GetWorldTimerManager().SetTimer(TimerHandle_ResetAttack, this, &ABaseEnemy::ResetAttack, 2.f, false);
			}
		}
	}
}

void ABaseEnemy::ResetAttack()
{
	bHasAttackedPlayer = false;
}

