// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipActor.h"

#include "Kismet/GameplayStatics.h"
#include "BulletActor.h"
#include "HealthComponent.h"

// Sets default values
AShipActor::AShipActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship mesh"));
	SetRootComponent(ShipMesh);
}

// Called when the game starts or when spawned
void AShipActor::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterial = UMaterialInstanceDynamic::Create(MeshMaterial, this);
	ShipMesh->SetMaterial(0, DynamicMaterial);
	
	Color.G = 0.f;
	DynamicMaterial->SetVectorParameterValue("ColorWithAlpha", Color);
}

// Called every frame
void AShipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Force = GetActorForwardVector() * MaxMoveForce * Throttle;
	Force += GetAirResistance();
	
	FVector Accel = Force / Mass;
	Velocity += Accel * DeltaTime;
	
	MoveShip(DeltaTime);
	ImmuneTime -= DeltaTime;
	if(ImmuneTime <= 0 && Color.G != .5f)
	{
		Color.G = .5f;
		DynamicMaterial->SetVectorParameterValue("ColorWithAlpha", Color);
	}
}

void AShipActor::RotateShip(float Axis)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw += GetActorRotation().Yaw + (Axis * 90);
	const float Alpha = UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * RotationSpeed;
	const FRotator Rotation = FMath::Lerp(GetActorRotation(), DeltaRotation, Alpha);
	
	SetActorRotation(Rotation);
}

void AShipActor::AddThrottleShip(float Axis)
{
	Throttle = Axis;
}

void AShipActor::MoveShip(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;
	
	FHitResult Hit;
	AddActorWorldOffset(Translation, true, &Hit);

	if(Hit.IsValidBlockingHit())
	{
		Velocity = FVector::Zero();
	}
}

void AShipActor::Shoot() const
{
	ABulletActor *Bullet = GetWorld()->SpawnActor<ABulletActor>(BulletActorClass, GetActorLocation() + GetActorForwardVector() * BulletSpawnLocation, FRotator::ZeroRotator);
	if(!Bullet) return;
	Bullet->SetActorRotation(GetActorRotation());
}

void AShipActor::Hit()
{
	SetActorLocation(FVector::Zero());
	Velocity = FVector::Zero();
	ImmuneTime = MaxImmuneTime;
	
	Color.G = 0.f;
	DynamicMaterial->SetVectorParameterValue("ColorWithAlpha", Color);
}


int32 AShipActor::GetHealth() const
{
	const UHealthComponent *HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
	if(!HealthComponent) return 0;

	return HealthComponent->GetCurrentHealth();
}

FVector AShipActor::GetAirResistance() const
{
	return -Velocity.GetSafeNormal() * (Velocity.SizeSquared() * DragCoefficient);
}
