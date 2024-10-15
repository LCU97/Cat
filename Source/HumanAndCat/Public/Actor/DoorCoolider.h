// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorCoolider.generated.h"

UCLASS()
class HUMANANDCAT_API ADoorCoolider : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorCoolider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OverlapLevelLoadBeing(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap();

public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ColliderComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraFxComp;

	UPROPERTY(EditAnywhere, Category = "Level")
	FName LevelToLoad;
	
};
