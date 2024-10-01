// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackEnemy_shuriken.h"
#include "TimerManager.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Delegates/Delegate.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABlackEnemy_shuriken::ABlackEnemy_shuriken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(15.0f); 
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = CollisionComponent; 

	CollisionComponent->OnComponentHit.AddDynamic(this, &ABlackEnemy_shuriken::OnShurikenHit);

	shuriken = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("shuriken"));
	shuriken->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/GhostLady_S1/Meshes/Weapons/SK_ThrowKnife.SK_ThrowKnife' "));
	if (MeshAsset.Succeeded())
	{
		shuriken->SetSkeletalMesh(MeshAsset.Object);
	}
	shuriken->SetupAttachment(CollisionComponent); 

}

// Called when the game starts or when spawned
void ABlackEnemy_shuriken::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ABlackEnemy_shuriken::DestroyShuriken, 5.0f, false);

	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerActor)
	{
		FVector PlayerLocation = PlayerActor->GetActorLocation();
		FVector ShurikenLocation = GetActorLocation();

		MoveDirection = (PlayerLocation - ShurikenLocation).GetSafeNormal();

		FRotator TargetRotation = MoveDirection.Rotation();

		TargetRotation.Pitch -= 90.0f;  
		SetActorRotation(TargetRotation); 
	}
}

// Called every frame
void ABlackEnemy_shuriken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Speed = 800.0f;  // 속도

	FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;

	SetActorLocation(NewLocation);

	FRotator RotationChange = FRotator(0.0f, 720.0f * DeltaTime, 0.0f);
	AddActorLocalRotation(RotationChange);  
}

void ABlackEnemy_shuriken::DestroyShuriken()
{
	Destroy();  
}

void ABlackEnemy_shuriken::OnShurikenHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 0번 플레이어 가져오기
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// OtherActor가 0번 플레이어인지 확인
	if (OtherActor && OtherActor == PlayerActor)
	{
		// 충돌 시 표창 파괴
		Destroy();
	}
}