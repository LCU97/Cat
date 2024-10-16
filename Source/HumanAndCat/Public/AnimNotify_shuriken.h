// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_shuriken.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UAnimNotify_shuriken : public UAnimNotify
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere,Category = "shuriken")
	TSubclassOf<class ABlackEnemy_shuriken> ShurikenClass;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


};