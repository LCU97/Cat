// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Characters/BaseEnemy.h"
#include "NotifyState_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UNotifyState_Enemy : public UAnimNotifyState
{
	GENERATED_BODY()


public:


	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "MonsterLineTrace")
	FName StartSoketName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "MonsterLineTrace")
	float _EndPoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "MonsterLineTrace")
	float _Size;

	UPROPERTY()
	ABaseEnemy* EnemyCharacter;

};
