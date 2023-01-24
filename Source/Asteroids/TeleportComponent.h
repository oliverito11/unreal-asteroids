// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsteroidsGameModeBase.h"
#include "Components/ActorComponent.h"
#include "TeleportComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDS_API UTeleportComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	AActor *Owner;

	UPROPERTY(VisibleAnywhere)
	AAsteroidsGameModeBase* GameMode;

public:	
	// Sets default values for this component's properties
	UTeleportComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void CheckIfOutsideBounds();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
