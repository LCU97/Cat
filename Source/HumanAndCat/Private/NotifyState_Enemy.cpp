// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Enemy.h"

void UNotifyState_Enemy::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UNotifyState_Enemy::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	ABaseEnemy* EnemyCharacter = Cast<ABaseEnemy>(MeshComp->GetOwner());

	if (EnemyCharacter)
	{
		EnemyCharacter->MonsterAttackTrace(StartSoketName, _EndPoint, _Size);
	}
}

void UNotifyState_Enemy::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}
