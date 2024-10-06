// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActor.h"
#include "FireBallSkill.generated.h"

UCLASS()
class HUMANANDCAT_API AFireBallSkill : public ASkillActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireBallSkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void LaunchFireball(const FVector& CenterDirection, const FVector& Direction);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class USphereComponent* CollisionComponent;

	float SphereRadius = 20.f;;

	FVector StartCollosionLocation;
	FVector Dir;
};
