// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractableInterface.h"
#include "NPC.generated.h"

UCLASS()
class HUMANANDCAT_API ANPC : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPC();

private:
	UPROPERTY(EditAnywhere, Category = "InteractWidget")
	TSubclassOf<class UUserWidget> InteractWidgetClass;

protected:
	UPROPERTY(EditAnywhere, Category = "InteractWidget")
	class UWidgetComponent* InteractWidget;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	class UBoxComponent* BoxComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	class USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "NPC")
	TSubclassOf<class UUserWidget> ItemShopWidgetClass;

	UPROPERTY()
	class UUserWidget* ItemShopWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	TArray<FName> ItemsOnSale;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual void DisplayWidget() override;

	virtual void HideWidget() override;
	

};

