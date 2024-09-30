// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BlackEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API ABlackEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaSeconds) override;

private:
    // 플레이어를 추적하기 위한 함수
    void ChasePlayer();

    // 플레이어를 찾아서 저장할 변수
    APawn* PlayerPawn;
	
};
