// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraManagerComponent.generated.h"


class UBaseCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUMANANDCAT_API UCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCameraManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void InitCameraManager(UBaseCameraComponent* InGame, UBaseCameraComponent* Ultimate);
public:
// 카메라 시점 타겟팅
	UFUNCTION(BlueprintCallable)
	void  InGameLockOn();

	UFUNCTION(BlueprintCallable)
	void InGameLockDown();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsTarget() {return bIsTarget;}

	UFUNCTION(BlueprintCallable)
	void SetIsTarget(bool TargetOnBool) {bIsTarget = TargetOnBool;}
	//타겟팅 end

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|InGameCamera")
	UBaseCameraComponent* InGameCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Camera|UltimateCamera")
	UBaseCameraComponent* UltimateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UBaseCameraComponent* CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UBaseCombatComponent* CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsTarget = false;
};
