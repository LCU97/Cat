// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackEnemyCharacter.h"
#include "BlackEnemyAIController.h"

// Sets default values
ABlackEnemyCharacter::ABlackEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetWorldLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	weaponSkeletaMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	weaponSkeletaMeshComp->SetupAttachment(GetMesh(), FName("hand_Weapon_rSocket"));


	MaskSkeletaMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MaskMesh"));
	MaskSkeletaMeshComp->SetupAttachment(GetMesh(), FName("LipUp_mSocket"));

	shuriken = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("shurikenMesh"));
	shuriken->SetupAttachment(GetMesh(), FName("shuriken_lSocket"));

}

// Called when the game starts or when spawned
void ABlackEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (AIControllerClass == nullptr)
	//{
	//	AIControllerClass = ABlackEnemyAIController::StaticClass();
	//}
	
}

// Called every frame
void ABlackEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABlackEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABlackEnemyCharacter::WhenItHit()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AnimInstance->Montage_IsPlaying(nullptr)) 
	{
		AnimInstance->Montage_Stop(0.2f);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMontage(TEXT("/Script/Engine.AnimMontage'/Game/SJS/EnemyAnimations/Anim_Dame_2_Montage.Anim_Dame_2_Montage'"));

	if (HitMontage.Succeeded() && AnimInstance)
	{
		AnimInstance->Montage_Play(HitMontage.Object); 
	}

	if (EnemyStat.Hp <= 0)
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> dieMontage(TEXT("/Script/Engine.AnimMontage'/Game/SJS/EnemyAnimations/Anim_Death_Montage.Anim_Death_Montage'"));
		if (AnimInstance && AnimInstance->Montage_IsPlaying(nullptr)) 
		{
			AnimInstance->Montage_Stop(0.1f);
		}
		AnimInstance->Montage_Play(dieMontage.Object);

		// 2초 뒤에 캐릭터를 파괴하는 타이머 설정
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_Destroy, 
			this,               
			&ABlackEnemyCharacter::OnDeathMontageFinished, 
			1.0f,              
			false                
		);

	}

}

float ABlackEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABlackEnemyCharacter::OnDeathMontageFinished()
{
	Destroy();
}