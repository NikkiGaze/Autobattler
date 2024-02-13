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

	UnitActor->SetActorLocation(UnitActor->GetActorLocation() + CurrentOffsetVector * DeltaTime);
	// UE_LOG(LogTemp, Log, TEXT("%f, %f"), DeltaTime, GetWorld()->GetDeltaSeconds());
}

void AVisualizationManager::InitialSpawn(TSubclassOf<AActor> UnitClass)
{
	// FActorSpawnParameters Params;
	// FVector SpawnLocation = FVector(0.f, 0.f, 0.f); 
	// FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
	// GetWorld()->SpawnActor(UnitClass, SpawnLocation, SpawnRotation, Params);
	UnitActor = GetWorld()->SpawnActor(UnitClass);
}

void AVisualizationManager::OnSimulationTick(int NewPosition)
{
	//Calc new position in world coordinates
	const int CellSize = 50;

	OldPosition = NextPosition;
	NextPosition = NewPosition;

	if (const int CellDiff = NewPosition != OldPosition;
		CellDiff != 0)
	{
		const FVector OldPositionVector = FVector(CellSize * OldPosition, 0, 0);
		const FVector NewPositionVector = FVector(CellSize * NextPosition, 0, 0);
		CurrentOffsetVector = (NewPositionVector - OldPositionVector) / 5.f;
	}
}

