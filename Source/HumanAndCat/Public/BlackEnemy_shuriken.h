// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "BlackEnemy_shuriken.generated.h"

UCLASS()
class HUMANANDCAT_API ABlackEnemy_shuriken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackEnemy_shuriken();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* shuriken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USphereComponent* CollisionComponent;

	// 나이아가라 컴포넌트 추가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UNiagaraComponent* NiagaraEffect;

	UFUNCTION()
	void DestroyShuriken();

	FTimerHandle TimerHandle_Destroy;


 // 충돌 감지 함수
    UFUNCTION()
    void OnShurikenOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	FVector MoveDirection;


};