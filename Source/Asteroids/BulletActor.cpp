// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"

#include "AsteroidActor.h"
#include "AsteroidsGameModeBase.h"
#include "AsteroidsPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet mesh"));
	SetRootComponent(BulletMesh);
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	AddActorWorldOffset(GetActorForwardVector() * BulletSpeed * DeltaTime, true, &Hit);
	CheckHit(&Hit);
	
	DestroyTime -= DeltaTime;
	if(DestroyTime <= 0)
	{
		Destroy();
	}		
}

void ABulletActor::CheckHit(FHitResult* Hit)
{
	if(!Hit->GetActor()) return;
	UE_LOG(LogTemp, Warning, TEXT("Hit something!"));

	if(AAsteroidActor *Asteroid = Cast<AAsteroidActor>(Hit->GetActor()))
	{
		AddScoreToPlayer();
		Asteroid->Hit();
		Destroy();
	}
}

void ABulletActor::AddScoreToPlayer() const
{
	const AAsteroidsGameModeBase *GameMode = Cast<AAsteroidsGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(!GameMode) return;

	AAsteroidsPawn *PlayerPawn = GameMode->GetPlayerPawn();
	if(!PlayerPawn) return;
	
	PlayerPawn->AddScore(HitScore);
}