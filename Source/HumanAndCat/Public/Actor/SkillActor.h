// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SkillActor.generated.h"

UCLASS()
class HUMANANDCAT_API ASkillActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkillActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void AttackingContinuous();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UNiagaraComponent* NiagaraComponent;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<class ABaseEnemy*> Enemys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	float AttackStat;

	class APlayerController* PlayerController;
	
	FTimerHandle AttackTimerHandle;
};
