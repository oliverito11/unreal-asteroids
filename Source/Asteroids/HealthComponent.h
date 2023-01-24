// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealthHits {3};

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth {MaxHealthHits};

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void HitActor();
	virtual void Dead();

	UFUNCTION(BlueprintCallable)
	int GetCurrentHealth() const { return this->CurrentHealth; }
};
