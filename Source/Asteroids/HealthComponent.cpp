// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ShipActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHealthComponent::HitActor()
{
	AShipActor *PlayerShip = Cast<AShipActor>(GetOwner());
	if(!PlayerShip || PlayerShip->GetImmuneTime() >= 0) return;
	PlayerShip->Hit();
	UE_LOG(LogTemp, Warning, TEXT("Asteroid hit player"));
	CurrentHealth--;
	if(CurrentHealth <= 0)
	{
		Dead();
	}
}

void UHealthComponent::Dead()
{
	AActor *Owner = GetOwner();
	if(!Owner) return;
	Owner->Destroy();

	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	UGameplayStatics::OpenLevel(this, TEXT("Game"));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

