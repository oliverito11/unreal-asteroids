// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidsPawn.h"

#include "AsteroidsGameModeBase.h"
#include "ShipActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AAsteroidsPawn::AAsteroidsPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main camera"));
	SetRootComponent(Camera);

}

// Called when the game starts or when spawned
void AAsteroidsPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Camera->SetWorldRotation(FRotator{-90, 0, 0});
	ShipActor = GetWorld()->SpawnActor<AShipActor>(ShipActorClass, FVector::Zero(), FRotator::ZeroRotator);

	AAsteroidsGameModeBase *GameMode = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(!GameMode) return;
	GameMode->SetPlayerShipActor(ShipActor);
	GameMode->StartSpawn();
}

// Called every frame
void AAsteroidsPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAsteroidsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Rotate", this, &AAsteroidsPawn::RotatePawn);
	PlayerInputComponent->BindAxis("MoveForward", this, &AAsteroidsPawn::MovePawn);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AAsteroidsPawn::Shoot);
}

void AAsteroidsPawn::RotatePawn(float Axis)
{
	if(!ShipActor) return;

	ShipActor->RotateShip(Axis);
}

void AAsteroidsPawn::MovePawn(float Axis)
{
	if(!ShipActor) return;

	ShipActor->AddThrottleShip(Axis);
}

void AAsteroidsPawn::Shoot()
{
	if(!ShipActor) return;

	ShipActor->Shoot();
}

void AAsteroidsPawn::AddScore(float Value)
{
	Score += Value;
	UE_LOG(LogTemp, Warning, TEXT("Added %f to player score. Current score: %f"), Value, Score);
}
