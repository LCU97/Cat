// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoneActor.generated.h"

UCLASS()
class HUMANANDCAT_API AStoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	UStaticMeshComponent* StoneMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float ZSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float ZAmplitude;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float XSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float XAmplitude;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float YSpeed;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float YAmplitude;





	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	FVector InitialLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Stone")
	float ElapsedTime;


};
