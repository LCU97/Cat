// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/NPC.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Misc/MapErrors.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComp);

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(RootComponent);

	// just creating the widget component
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	InteractWidget->SetupAttachment(SkeletalMeshComp);
	InteractWidget->SetWidgetSpace(EWidgetSpace::World);
	InteractWidget->SetDrawSize(FVector2D(50.f, 50.f));

	if  (InteractWidgetClass)		// set as a InterWidgetClass
	{
		InteractWidget->SetWidgetClass(InteractWidgetClass);
	}
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	InteractWidget->SetVisibility(false);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::Interact()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->SetViewTargetWithBlend(this, 1.f);
	OurPlayerController->SetInputMode(FInputModeUIOnly());
	OurPlayerController->SetShowMouseCursor(true);

	HideWidget();

	if (ItemShopWidgetClass)
	{
		ItemShopWidget = CreateWidget<UUserWidget>(GetWorld(), ItemShopWidgetClass);

		// refer the variable in BP
		FProperty* _NPCProperty = ItemShopWidget->GetClass()->FindPropertyByName(TEXT("OwnerNPC"));
		if (_NPCProperty)
		{
			FObjectProperty* ObjectProperty = CastField<FObjectProperty>(_NPCProperty);
			if (ObjectProperty && ObjectProperty->PropertyClass == ANPC::StaticClass())
			{
				ObjectProperty->SetObjectPropertyValue_InContainer(ItemShopWidget, this); // assign ObjectProperty <- this 
			}
		}
		if (ItemShopWidget)
		{
			ItemShopWidget->AddToViewport();
		}
	}
}

void ANPC::DisplayWidget()
{
	if (InteractWidget)
	{
		InteractWidget->SetVisibility(true);
	}
}

void ANPC::HideWidget()
{
	if (InteractWidget)
	{
		InteractWidget->SetVisibility(false);
	}
}


