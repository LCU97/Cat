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

    // �ݸ��� ������Ʈ ���� �� �ʱ�ȭ
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(30.0f);

    // �浹 ���� (Overlap)
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // ���������� ó������ �ʰ� ��ħ�� ����
    CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic); // ��ü Ÿ�� ����
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore); // ��� ä���� ����
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Pawn���� Overlap �̺�Ʈ�� ó��

    // Overlap �̺�Ʈ ���ε�
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackEnemy_shuriken::OnShurikenOverlap);

    RootComponent = CollisionComponent;

    // SkeletalMesh ����
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

    // ǥâ�� 5�� �Ŀ� �ı�
    GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &ABlackEnemy_shuriken::DestroyShuriken, 5.0f, false);

    // �÷��̾� ��ġ�� �������� ǥâ ���� ����
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerActor)
    {
        FVector PlayerLocation = PlayerActor->GetActorLocation();
        FVector ShurikenLocation = GetActorLocation();

        MoveDirection = (PlayerLocation - ShurikenLocation).GetSafeNormal();

        // ǥâ�� �÷��̾ ���ϵ��� ȸ��
        FRotator TargetRotation = MoveDirection.Rotation();
        TargetRotation.Pitch -= 90.0f;
        SetActorRotation(TargetRotation);
    }
}

// Called every frame
void ABlackEnemy_shuriken::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ǥâ �̵� ó��
    float Speed = 1300.0f;  // �ӵ�
    FVector NewLocation = GetActorLocation() + MoveDirection * Speed * DeltaTime;
    SetActorLocation(NewLocation);

    // ǥâ�� ȸ�� ó��
    FRotator RotationChange = FRotator(0.0f, 720.0f * DeltaTime, 0.0f);
    AddActorLocalRotation(RotationChange);
}

// ǥâ �ı�
void ABlackEnemy_shuriken::DestroyShuriken()
{
    Destroy();
}

// Overlap �߻� �� ȣ��Ǵ� �Լ�
void ABlackEnemy_shuriken::OnShurikenOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 0�� �÷��̾� ��������
    AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // �÷��̾�� �浹�ߴ��� Ȯ��
    if (OtherActor && OtherActor == PlayerActor)
    {
        // ǥâ �ı�
        Destroy();
    }
}