// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidActor.generated.h"

class USoundBase;
UCLASS()
class ASTEROIDS_API AAsteroidActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *AsteroidMesh;
	
	UPROPERTY(EditDefaultsOnly)
	int32 Divisions {3};

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAsteroidActor> AsteroidClass;

	UPROPERTY(EditDefaultsOnly)
	int32 HitDivisions {2};

	UPROPERTY(VisibleAnywhere)
	FVector MoveDirection;
	
	bool IsFirstTime {true};
	
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed {200};

	UPROPERTY(EditDefaultsOnly)
	USoundBase *DeadSoundCue;

public:	
	// Sets default values for this actor's properties
	AAsteroidActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Hit();
	void Spawn(FVector Scale, int32 NewDivisions);
};
