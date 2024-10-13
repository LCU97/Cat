// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorCollider.generated.h"

UCLASS()
class HUMANANDCAT_API ADoorCollider : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorCollider();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* colliderComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* niagaraFxComp;

protected:
	UFUNCTION()
	void OverlapLevelLoadBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category="Level")
	FName levelToLoad;
};