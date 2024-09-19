// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInCombatChanged, bool, CombatBool);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class HUMANANDCAT_API UBaseCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	public:

	// Get, Set
	UFUNCTION(BlueprintCallable, Category="Get")
	bool GetInCombat() {return bInCombat;}
	
	UFUNCTION(BlueprintCallable, Category="Set")
	void SetInCombat(bool NewCombet) { bInCombat = NewCombet; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bInCombat = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	AActor* TargetActor = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	TArray<AActor*> FocusingTargets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	float TargetingRadius = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target")
	UClass* TargetClass = nullptr;

	

	UPROPERTY(BlueprintAssignable)
	FOnInCombatChanged OnInCombatChanged;
	
};
