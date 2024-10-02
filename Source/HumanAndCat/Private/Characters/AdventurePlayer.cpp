// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AdventurePlayer.h"

#include "Camera/CameraActor.h"
#include "Cameras/BaseCameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utilities/HumanAndCatTags.h"
#include "Actor/NPC.h"
#include "Components/InventoryActorComponent.h"

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

	DefaultInventory = CreateDefaultSubobject<UInventoryActorComponent>(TEXT("DefaultInventory"));
	DefaultInventory->MaxInventorySize = 30;
}

// Called when the game starts or when spawned
void AAdventurePlayer::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TraceTimerHandle;
	GetWorldTimerManager().SetTimer(TraceTimerHandle, this, &AAdventurePlayer::PerformInteractionTrace, 0.2f, true);
	
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

void AAdventurePlayer::UpdateMoney(int64 inputVal)
{
	int64 _result;
	_result = CurrentMoney + inputVal;

	if (_result < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Not Enough Money!"));
	}
	else
	{
		CurrentMoney = _result;
	}
}

void AAdventurePlayer::PerformInteractionTrace()
{
	FVector _Start = GetActorLocation();
	FVector _End = GetActorLocation() + GetActorForwardVector()*2000.f;
	FHitResult _HitOut;

	FCollisionQueryParams _TraceParams;
	_TraceParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(_HitOut, _Start, _End, ECC_GameTraceChannel1, _TraceParams);

	if (bHit)
	{
		AActor* HitActor = _HitOut.GetActor();
	
		if (HitActor)
		{
			// 해당 액터에 특정 인터페이스를 소유하는지 여부 알고 싶으면 캐스팅 해보자
			IInteractableInterface* InteractableActor = Cast<IInteractableInterface>(HitActor);
			if (InteractableActor)
			{
				if (CachedInteractActor != HitActor) // compare with the previous interactable actor (=CachedInteractActor)
				{
					UE_LOG(LogTemp, Log, TEXT("different actor"));
					if(CachedInteractActor)
					{
						IInteractableInterface* CachedInteractable = Cast<IInteractableInterface>(CachedInteractActor);
						if (CachedInteractable)
						{
							CachedInteractable->HideWidget();
						}
					}

					CachedInteractActor = HitActor;
					InteractableActor->DisplayWidget();
				}
			};
		}
	}
	else // No Hit
	{
		if (CachedInteractActor)
		{
			IInteractableInterface* CachedInteractable = Cast<IInteractableInterface>(CachedInteractActor);
			if (CachedInteractable)
			{
				CachedInteractable->HideWidget();
			}
			CachedInteractActor = nullptr;
		}
	}
}


