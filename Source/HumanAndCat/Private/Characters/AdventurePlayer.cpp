// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AdventurePlayer.h"

#include "Camera/CameraActor.h"
#include "Cameras/BaseCameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utilities/HumanAndCatTags.h"


// Sets default values
AAdventurePlayer::AAdventurePlayer()
{
	// Set this character to call Tick() every frame.  You can turn th
	// is off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());

	InGameCamera = CreateDefaultSubobject<UBaseCameraComponent>(TEXT("InGameCamera"));
	InGameCamera->SetupAttachment(SpringArm);
	InGameCamera->CameraTag = CameraTags::Camera_InGame;
	
	UltimateCamera = CreateDefaultSubobject<UBaseCameraComponent>(TEXT("UltiCamera"));
	UltimateCamera->SetupAttachment(GetRootComponent());
	UltimateCamera->CameraTag = CameraTags::Camera_Ultimate;
}

// Called when the game starts or when spawned
void AAdventurePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdventurePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAdventurePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


