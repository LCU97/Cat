// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyState_Enemy.h"

void UNotifyState_Enemy::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	 EnemyCharacter = Cast<ABaseEnemy>(MeshComp->GetOwner());
}

void UNotifyState_Enemy::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{

	if (EnemyCharacter)
	{
		EnemyCharacter->MonsterAttackTrace(StartSoketName, _EndPoint, _Size, EnemyATK);
	}
}

void UNotifyState_Enemy::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}
