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

	// �浹 ������ ���� ���� (�ڱ� �ڽ� ����)
	FCollisionQueryParams _TraceParams;
	_TraceParams.AddIgnoredActor(this);

	// ��ü �浹 ��� ���� (�������� Size ���)
	FCollisionShape SphereCollisionShape = FCollisionShape::MakeSphere(Size);


	// SweepSingleByChannel�� ����Ͽ� ��ü ��� �浹 ����
	if (!bHasAttackedPlayer && GetWorld()->SweepSingleByChannel(_HitOut, _StartLocation, _EndLocation, FQuat::Identity, ECC_GameTraceChannel2, SphereCollisionShape, _TraceParams))
	{
		AActor* PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (PlayerActor && _HitOut.GetActor())
		{
			if (_HitOut.GetActor() == PlayerActor)
			{
				// �÷��̾ ������ ���·� ����
				bHasAttackedPlayer = true;

				// ����� ���� �׸��� (�浹 ��� �ð�ȭ)
				//DrawDebugSphere(GetWorld(), _StartLocation, Size, 12, FColor::Green, false, 2.0f); // ������
				//DrawDebugSphere(GetWorld(), _EndLocation, Size, 12, FColor::Red, false, 2.0f);    // ����



				// ������ ����
				TSubclassOf<UDamageType> DamageType = UDamageType::StaticClass();
				UGameplayStatics::ApplyDamage(_HitOut.GetActor(), EnemyA, GetController(), this, DamageType);

				// 2�� �Ŀ� ���� ���� �ʱ�ȭDrawDebugSphere(GetWorld(), _StartLocation, Size, 12, FColor::Green, false, 2.0f); // ������
				DrawDebugSphere(GetWorld(), _EndLocation, Size, 12, FColor::Red, false, 2.0f);    // ����
				GetWorldTimerManager().SetTimer(TimerHandle_ResetAttack, this, &ABaseEnemy::ResetAttack, 2.f, false);
			}
		}
	}
}

void ABaseEnemy::ResetAttack()
{
	bHasAttackedPlayer = false;
}

