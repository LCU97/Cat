// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Notify/ANS_UltiCameraMoving.h"

#include "Components/CameraManagerComponent.h"

UANS_UltiCameraMoving::UANS_UltiCameraMoving()
{
}

void UANS_UltiCameraMoving::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	//Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	StartCameraMovement(MeshComp,TotalDuration);
}

void UANS_UltiCameraMoving::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	EndCameraMovement(MeshComp);
	//Super::NotifyEnd(MeshComp, Animation, EventReference);
}

FString UANS_UltiCameraMoving::GetNotifyName_Implementation() const
{
	return  FString(TEXT("UltiCameraMoving"));
}

void UANS_UltiCameraMoving::StartCameraMovement(USkeletalMeshComponent* MeshComp, float Duration)
{
	if(!IsValid(MeshComp))
		return;

	AActor* PActor = MeshComp->GetOwner();
	if(!IsValid(PActor)) return;

	 UCameraManagerComponent* CameraManager = PActor->GetComponentByClass<UCameraManagerComponent>();
	if(CameraManager == nullptr) return;

	CameraManager->ChangeUltiCamera(Duration);
}

void UANS_UltiCameraMoving::EndCameraMovement(USkeletalMeshComponent* MeshComp)
{
	if(!IsValid(MeshComp))
		return;

	AActor* PActor = MeshComp->GetOwner();
	if(!IsValid(PActor)) return;

	UCameraManagerComponent* CameraManager = PActor->GetComponentByClass<UCameraManagerComponent>();
	if(CameraManager == nullptr) return;

	CameraManager->ChangeInGameCamera();	
}
