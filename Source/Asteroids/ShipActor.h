// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

class ABulletActor;
UCLASS()
class ASTEROIDS_API AShipActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *ShipMesh;

	UPROPERTY(EditAnywhere)
	float RotationSpeed {200};

	UPROPERTY(VisibleAnywhere)
	float Throttle;

	UPROPERTY(EditAnywhere)
	float MaxMoveForce {1000};

	UPROPERTY(EditAnywhere)
	float Mass {1000};

	UPROPERTY(EditAnywhere)
	float DragCoefficient{16};

	UPROPERTY(EditDefaultsOnly)
	float MaxImmuneTime {3};
	
	UPROPERTY(VisibleAnywhere)
	float ImmuneTime {MaxImmuneTime};
	
	UPROPERTY(VisibleAnywhere)
	FVector Velocity;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABulletActor> BulletActorClass;

	UPROPERTY(EditAnywhere, meta = (MakeEditWidget))
	float BulletSpawnLocation;

	UPROPERTY(EditAnywhere)
	UMaterialInterface *MeshMaterial;

	UMaterialInstanceDynamic *DynamicMaterial;
	
	UPROPERTY(EditAnywhere)
	FLinearColor Color;

public:	
	// Sets default values for this actor's properties
	AShipActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateShip(float Axis);

	void AddThrottleShip(float Axis);
	void MoveShip(float DeltaTime);
	void Shoot() const;
	void Hit();
	float GetImmuneTime() const { return this->ImmuneTime; }

	UFUNCTION()
	int32 GetHealth() const;
private:
	FVector GetAirResistance() const;	
};
