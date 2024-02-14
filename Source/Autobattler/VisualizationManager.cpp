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

	// UnitActor->SetActorLocation(UnitActor->GetActorLocation() + CurrentOffsetVector * DeltaTime);
	// UE_LOG(LogTemp, Log, TEXT("%f, %f"), DeltaTime, GetWorld()->GetDeltaSeconds());
}

void AVisualizationManager::InitialSpawn(TSubclassOf<AActor> UnitTeam1Class,
	TSubclassOf<AActor> UnitTeam2Class,
	const TArray<FUnitDescriptor> &UnitDescriptors)
{
	for (auto &UnitDescriptor : UnitDescriptors)
	{
		const FVector *SpawnLocation = new FVector(CalcCellPosition(UnitDescriptor.Position));
		if (UnitDescriptor.Team == 1)
		{
			UnitActor = GetWorld()->SpawnActor(UnitTeam1Class, SpawnLocation);
		}
		else if (UnitDescriptor.Team == 2)
		{
			UnitActor = GetWorld()->SpawnActor(UnitTeam2Class, SpawnLocation);
		}
	}
	// FActorSpawnParameters Params;
	// FVector SpawnLocation = FVector(0.f, 0.f, 0.f); 
	// 
	// GetWorld()->SpawnActor(UnitClass, SpawnLocation, SpawnRotation, Params);
	
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

FVector AVisualizationManager::CalcCellPosition(const FVector2d &Coordinates)
{
	static int CellRadius = 200;
	int X = Coordinates.X * CellRadius + Coordinates.Y * 0.5;
	int Y = (sqrt(3) / 2) * Coordinates.Y * CellRadius;
	return FVector(X, Y, 0);
}
