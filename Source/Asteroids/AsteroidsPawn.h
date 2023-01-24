// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AsteroidsPawn.generated.h"

class ABulletActor;
class AShipActor;
class UCameraComponent;
UCLASS()
class ASTEROIDS_API AAsteroidsPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent *Camera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AShipActor> ShipActorClass;
	
	UPROPERTY(VisibleAnywhere)
	AShipActor *ShipActor;

	UPROPERTY(VisibleAnywhere)
	float Score{0};

public:
	// Sets default values for this pawn's properties
	AAsteroidsPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RotatePawn(float Axis);
	void MovePawn(float Axis);
	void Shoot();
	void AddScore(float Value);

	UFUNCTION(BlueprintCallable)
	int32 GetScore() const { return this->Score; }
	AShipActor *GetShipActor() const {return this->ShipActor;};
};
