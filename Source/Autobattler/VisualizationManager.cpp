// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualizationManager.h"

// Sets default values
AVisualizationManager::AVisualizationManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVisualizationManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVisualizationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVisualizationManager::InitialSpawn(TSubclassOf<AActor> UnitClass)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));

	FActorSpawnParameters Params;
	FVector SpawnLocation = FVector(0.f, 0.f, 0.f); 
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	// GetWorld()->SpawnActor(UnitClass, SpawnLocation, SpawnRotation, Params);
	UnitActor = GetWorld()->SpawnActor(UnitClass);
}

void AVisualizationManager::OnSimulationTick(int NewPosition)
{
}

