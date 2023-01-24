// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidActor.h"

#include "HealthComponent.h"
#include "ShipActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAsteroidActor::AAsteroidActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Asteroid mesh"));
	SetRootComponent(AsteroidMesh);
}

// Called when the game starts or when spawned
void AAsteroidActor::BeginPlay()
{
	Super::BeginPlay();
	
	MoveDirection = FVector{FMath::FRandRange<float>(-1, 1), FMath::FRandRange<float>(-1, 1), 0};
}

void AAsteroidActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(!OtherActor) return;
	if(const AShipActor *PlayerShip = Cast<AShipActor>(OtherActor))
	{
		if(UHealthComponent *Health = Cast<UHealthComponent>(PlayerShip->GetComponentByClass(UHealthComponent::StaticClass())))
		{
			Health->HitActor();
		}
	}
}

// Called every frame
void AAsteroidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(MoveDirection * MoveSpeed * DeltaTime);
}

void AAsteroidActor::Hit()
{
	if(Divisions > 0)
	{
		Divisions--;
		//Spawn another 2 asteroids with scale / 2 and -1 divisions
		for(int32 i = 0; i < HitDivisions; i++)
		{
			if(AAsteroidActor *Asteroid = GetWorld()->SpawnActor<AAsteroidActor>(AsteroidClass, GetActorLocation(), FRotator::ZeroRotator))
			{
				Asteroid->Spawn(GetActorScale(), Divisions);
			}
		}
	}
	
	UGameplayStatics::PlaySoundAtLocation(this, DeadSoundCue, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

void AAsteroidActor::Spawn(FVector Scale, int32 NewDivisions)
{
	Divisions = NewDivisions;
	SetActorScale3D(FVector{Scale / 2});
	UE_LOG(LogTemp, Warning, TEXT("Spawned %s with %i number of divisions"), *GetActorNameOrLabel(), Divisions);
}

