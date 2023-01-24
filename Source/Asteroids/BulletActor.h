// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class ASTEROIDS_API ABulletActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent *BulletMesh;
	
	UPROPERTY(EditAnywhere)
	float BulletSpeed;

	UPROPERTY(EditAnywhere)
	float DestroyTime {2};

	UPROPERTY(EditAnywhere)
	float HitScore {100};
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void AddScoreToPlayer() const;
public:
	void CheckHit(FHitResult* Hit);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
