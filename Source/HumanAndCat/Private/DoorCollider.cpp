// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorCollider.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/AdventurePlayer.h"

// Sets default values
ADoorCollider::ADoorCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	colliderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliderComponent"));
	SetRootComponent(colliderComp);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComp->SetupAttachment(colliderComp);

	niagaraFxComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraFxComponent"));
	niagaraFxComp->SetupAttachment(colliderComp);
}


void ADoorCollider::BeginPlay()
{
	Super::BeginPlay();

	colliderComp->OnComponentBeginOverlap.AddDynamic(this, &ADoorCollider::OverlapLevelLoadBegin);
}


void ADoorCollider::OverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	AAdventurePlayer* _myCharacter = Cast<AAdventurePlayer>(OtherActor);
	if (OtherActor && levelToLoad != " ")
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "overlap");
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, levelToLoad, true, true, LatentInfo);
	}

}



