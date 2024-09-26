// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
	void FwdBakMoveCheck();

public:
// 카메라 시점 타겟팅
	UFUNCTION(BlueprintCallable)
	void  InGameLockOn();

	UFUNCTION(BlueprintCallable)
	void InGameLockDown();
	
	void FwdBakLerp(FVector ActorLocation, USpringArmComponent* Arm);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsTarget() {return bIsTarget;}

	UFUNCTION(BlueprintCallable)
	void SetIsTarget(bool TargetOnBool) {bIsTarget = TargetOnBool;}

	UFUNCTION(BlueprintCallable)
	void TargetingCameraMoving(ACharacter* PCharacter);

	UFUNCTION(BlueprintCallable)
	void InitCameraMovingLerp();
	//타겟팅 end

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|InGameCamera")
	UBaseCameraComponent* InGameCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Camera|UltimateCamera")
	UBaseCameraComponent* UltimateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UBaseCameraComponent* CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsInBox =true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UBaseCombatComponent* CombatComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USpringArmComponent* ArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bIsTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bLerping = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool SetInitTime =false;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FwdBakTimeDuration = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FwdBakCurrentTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FwdBakMoveStart = -1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bFwdBakLerping = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Combat")
	class UCurveFloat* FwdBakTimeCurve;
	
};
