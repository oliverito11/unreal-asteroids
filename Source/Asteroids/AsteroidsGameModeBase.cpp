// Copyright Epic Games, Inc. All Rights Reserved.


#include "AsteroidsGameModeBase.h"

#include "AsteroidActor.h"
#include "AsteroidsPawn.h"
#include "ShipActor.h"
#include "GameFramework/PlayerState.h"

AAsteroidsGameModeBase::AAsteroidsGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroidsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerPawn();
}

void AAsteroidsGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RandomSpawnTime -= DeltaSeconds;
	if(RandomSpawnTime <= 0)
	{
		RandomSpawnTime = MaxRandomSpawnTime;
		SpawnAsteroid();
	}
}

void AAsteroidsGameModeBase::StartSpawn() const
{
	const int32 NumberOfSpawns = FMath::RandRange(MinAsteroids, MaxAsteroids);
	
	for (int32 i = 0; i < NumberOfSpawns; i++)
	{
		SpawnAsteroid();
	}
}

void AAsteroidsGameModeBase::SetPlayerPawn()
{
	const APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if(!PlayerController) return;

	const APlayerState *PlayerState = PlayerController->GetPlayerState<APlayerState>();
	if(!PlayerState) return;

	PlayerPawn = Cast<AAsteroidsPawn>(PlayerState->GetPawn());
}


void AAsteroidsGameModeBase::SpawnAsteroid() const
{
	FVector SpawnLocation;
	do
	{
		SpawnLocation = {FMath::FRandRange(-DeadZoneX, DeadZoneX), FMath::FRandRange(-DeadZoneY, DeadZoneY), 0};
	}
	while (PlayerShipActor && FVector::Dist(SpawnLocation, PlayerShipActor->GetActorLocation()) <= SpawnAsteroidDeadZone);

	GetWorld()->SpawnActor<AAsteroidActor>(AsteroidClass, SpawnLocation, FRotator::ZeroRotator);
	UE_LOG(LogTemp, Warning, TEXT("New asteroid just spawned!"));
}
