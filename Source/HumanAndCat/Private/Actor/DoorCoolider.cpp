// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DoorCoolider.h"

#include "NiagaraComponent.h"
#include "Characters/AdventurePlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADoorCoolider::ADoorCoolider()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(ColliderComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(GetRootComponent());

	NiagaraFxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	NiagaraFxComp->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADoorCoolider::BeginPlay()
{
	Super::BeginPlay();

	ColliderComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorCoolider::OverlapLevelLoadBeing);
}

// Called every frame
void ADoorCoolider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ADoorCoolider::OverlapLevelLoadBeing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAdventurePlayer* PCharacter = Cast<AAdventurePlayer>(OtherActor);

	if(PCharacter && LevelToLoad != "")
	{
		FLatentActionInfo LatentActionInfo;
		LatentActionInfo.ExecutionFunction = FName("EndOverlap");
		LatentActionInfo.UUID = __LINE__;
		LatentActionInfo.Linkage = 0;
		LatentActionInfo.CallbackTarget = this;		
		UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, false,LatentActionInfo );
	}
}

void ADoorCoolider::EndOverlap()
{
	Destroy();
}
