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
    // �÷��̾ �����ϱ� ���� �Լ�
    void ChasePlayer();

    // �÷��̾ ã�Ƽ� ������ ����
    APawn* PlayerPawn;
	
};
