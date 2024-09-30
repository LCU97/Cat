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

	//AI컨트룰러 할당
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

