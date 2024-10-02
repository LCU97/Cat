// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_UltiCameraMoving.generated.h"

/**
 * 
 */
UCLASS()
class HUMANANDCAT_API UANS_UltiCameraMoving : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UANS_UltiCameraMoving();
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;

public:
	void StartCameraMovement(USkeletalMeshComponent* MeshComp, float Duration);

	void EndCameraMovement(USkeletalMeshComponent* MeshComp);

};
