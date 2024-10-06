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
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // 콜리전 컴포넌트 생성 및 초기화
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(30.0f);

    // 충돌 설정 (Overlap)
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // 물리적으로 처리하지 않고 겹침만 감지
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic); // 객체 타입 설정
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // 모든 채널을 무시
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Pawn과의 Overlap 이벤트만 처리

    // Overlap 이벤트 바인딩
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackEnemy_shuriken::OnShurikenOverlap);

    RootComponent = CollisionComponent;

    // SkeletalMesh 설정
    shuriken = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("shuriken"));
    shuriken->SetWorldScale3D(FVector(4.0f, 4.0f, 4.0f));
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

    // 표창을 5초 후에 파괴
    GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ABlackEnemy_shuriken::DestroyShuriken, 5.0f, false);

    // 플레이어 위치를 기준으로 표창 방향 설정
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerActor)
    {
        FVector PlayerLocation = PlayerActor->GetActorLocation();
        FVector ShurikenLocation = GetActorLocation();

        MoveDirection = (PlayerLocation - ShurikenLocation).GetSafeNormal();

        // 표창이 플레이어를 향하도록 회전
        FRotator TargetRotation = MoveDirection.Rotation();
        TargetRotation.Pitch -= 90.0f;
        SetActorRotation(TargetRotation);
    }
}

// Called every frame
void ABlackEnemy_shuriken::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 표창 이동 처리
    float Speed = 1300.0f;  // 속도
    FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
    SetActorLocation(NewLocation);

    // 표창의 회전 처리
    FRotator RotationChange = FRotator(0.0f, 720.0f * DeltaTime, 0.0f);
    AddActorLocalRotation(RotationChange);
}

// 표창 파괴
void ABlackEnemy_shuriken::DestroyShuriken()
{
    Destroy();
}

// Overlap 발생 시 호출되는 함수
void ABlackEnemy_shuriken::OnShurikenOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 0번 플레이어 가져오기
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // 플레이어와 충돌했는지 확인
    if (OtherActor && OtherActor == PlayerActor)
    {
        // 표창 파괴
        Destroy();
    }
}