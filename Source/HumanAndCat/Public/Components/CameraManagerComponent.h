// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CameraManagerComponent.generated.h"

// 1. 타겟팅 시 카메라의 움직임을 직접 제어합니다.
// 2. 궁극기 용 카메라를 가지고 궁극기 스킬 사용 시 카메라를 스위칭 합니다.
// 3. 헤더파일에서는 멤버에 주석, cpp 파일에서 함수에 주석을 달았습니다.

class UBaseCameraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUMANANDCAT_API UCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCameraManagerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void InitCameraManager(UBaseCameraComponent* InGame, UBaseCameraComponent* Ultimate);
	

public:
	UFUNCTION(BlueprintCallable)
	void ChangeUltiCamera(float Duration);

	UFUNCTION(BlueprintCallable)
	void ChangeInGameCamera();
	
	// 궁극기 카메라 관련 기능
	UFUNCTION()
	void UltiMoving();	

	// 궁극기 카메라 관련 기능 end
	
	// 카메라 시점 타겟팅
	UFUNCTION(BlueprintCallable)
	void  InGameLockOn();

	UFUNCTION(BlueprintCallable)
	void InGameLockDown();
	
	//void FwdBakLerp(FVector ActorLocation, USpringArmComponent* Arm);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsTarget() {return bIsTarget;}

	UFUNCTION(BlueprintCallable)
	void SetIsTarget(bool TargetOnBool) {bIsTarget = TargetOnBool;}

	UFUNCTION(BlueprintCallable)
	void TargetingCameraMoving(ACharacter* PCharacter);

	UFUNCTION(BlueprintCallable)
	void InitCameraMovingLerp();
	// 타겟팅 end

	UFUNCTION()
	UBaseCameraComponent* GetInGameCamera() {return InGameCamera;};
	
private:
	// 타겟팅 관련 카메라 멤버
	
	// 평상시 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera|InGameCamera", meta = (AllowPrivateAccess = "true"))
	UBaseCameraComponent* InGameCamera;

	// 현재 사용 중인 카메라
	UPROPERTY(EditAnywhere, Category = "Camera")
	UBaseCameraComponent* CurrentCamera;

	// 뷰 좌표계의 특정 영역에 대한 캐릭터의 위치가 InOut 을 확인하는 변수
	UPROPERTY()
	bool bIsInBox =true;

	// 자주 사용하는 컴포넌트들을 캐싱합니다.
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UBaseCombatComponent* CombatComponent;
		
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USpringArmComponent* ArmComponent;

	// 타겟팅 중인지 확인하는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bIsTarget = false;

	// 카메라가 보간하여 움직이고 있는지 확인하는 변수
	UPROPERTY(EditAnywhere,  Category = "Combat")
	bool bLerping = false;

	// 보간을 취소하기 위해 제어되는 변수
	UPROPERTY(EditAnywhere,  Category = "Combat")
	bool SetInitTime =false;

	// ----------------------------------------------------------------------------------------------------------
	// 궁극기 카메라 관련 멤버
	
	// 궁극기용 카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Camera|UltimateCamera", meta = (AllowPrivateAccess = "true"))
	UBaseCameraComponent* UltimateCamera;
	
	// 궁극기 카메라 관련
	UPROPERTY()
	float UltiLerpDuration= -1;

	UPROPERTY()
	float UltiMovintStartTime;
	// 궁극기 카메라 관련 End

	UPROPERTY()
	APlayerController* PCon;
	
	float StandardDis =500.f;
};
