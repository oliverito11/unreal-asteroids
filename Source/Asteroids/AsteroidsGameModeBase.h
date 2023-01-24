// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidsGameModeBase.generated.h"

class AAsteroidsPawn;
class AShipActor;
class AAsteroidActor;
/**
 * 
 */
UCLASS()
class ASTEROIDS_API AAsteroidsGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAsteroidActor> AsteroidClass;

	UPROPERTY(EditDefaultsOnly)
	int32 MinAsteroids {5};

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAsteroids {20};

	UPROPERTY(VisibleAnywhere)
	AShipActor *PlayerShipActor;

	UPROPERTY(VisibleAnywhere)
	AAsteroidsPawn *PlayerPawn;

	UPROPERTY(EditDefaultsOnly)
	float MaxRandomSpawnTime {4};
	
	UPROPERTY(VisibleAnywhere)
	float RandomSpawnTime {MaxRandomSpawnTime};
	
	UPROPERTY(EditAnywhere)
	float DeadZoneY {500};

	UPROPERTY(EditAnywhere)
	float DeadZoneX {500};

	UPROPERTY(EditAnywhere)
	double SpawnAsteroidDeadZone {250};

public:
	AAsteroidsGameModeBase();
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SpawnAsteroid() const;
	void StartSpawn() const;

	void SetPlayerShipActor(AShipActor *Pawn) { this->PlayerShipActor = Pawn; };

	UFUNCTION(BlueprintCallable)
	AShipActor *GetPlayerShipActor() const { return this->PlayerShipActor; }
	UFUNCTION(BlueprintCallable)
	AAsteroidsPawn *GetPlayerPawn() const { return this->PlayerPawn; };

	float GetDeadZoneY() const { return this->DeadZoneY; }
	float GetDeadZoneX() const { return this->DeadZoneX; }
private:
	void SetPlayerPawn();
};
