// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportComponent.h"

#include "AsteroidsGameModeBase.h"
#include "AsteroidsPawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTeleportComponent::UTeleportComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UTeleportComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	GameMode = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void UTeleportComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckIfOutsideBounds();
}

void UTeleportComponent::CheckIfOutsideBounds()
{
	if(!GameMode) return;
	AAsteroidsPawn *PlayerPawn = GameMode->GetPlayerPawn();
	if(!PlayerPawn) return;
	
	if(FMath::Abs(Owner->GetActorLocation().X) > PlayerPawn->GetActorLocation().X + GameMode->GetDeadZoneX())
	{
		//TP to other side
		FVector NewLocation = Owner->GetActorLocation();
		NewLocation.X = -NewLocation.X;
		Owner->SetActorLocation(NewLocation);
	}
	if(FMath::Abs(Owner->GetActorLocation().Y) > PlayerPawn->GetActorLocation().Y + GameMode->GetDeadZoneY())
	{
		//TP to other side
		FVector NewLocation = Owner->GetActorLocation();
		NewLocation.Y = -NewLocation.Y;
		Owner->SetActorLocation(NewLocation);
	}
}