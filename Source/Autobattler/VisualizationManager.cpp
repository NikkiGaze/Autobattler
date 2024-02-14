// Fill out your copyright notice in the Description page of Project Settings.


#include "VisualizationManager.h"

#include "UnitActorBase.h"

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

void AVisualizationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const auto &UnitActorIter : UnitActorsMap)
	{
		// UE_LOG(LogTemp, Log, TEXT("%f"), UnitActorIter.Value->GetActorLocation().X);
		FVector CurrentMovementVector = UnitMovementVectorsMap.FindChecked(UnitActorIter.Key);
		UnitActorIter.Value->SetActorLocation(UnitActorIter.Value->GetActorLocation() + CurrentMovementVector * DeltaTime);
		// UE_LOG(LogTemp, Log, TEXT("%s"), *UnitActorIter.Value->GetName());
	}
	
	// UE_LOG(LogTemp, Log, TEXT("%f, %f"), DeltaTime, GetWorld()->GetDeltaSeconds());
}

void AVisualizationManager::InitialSpawn(TSubclassOf<AActor> UnitTeam1Class,
	TSubclassOf<AActor> UnitTeam2Class,
	const TArray<FUnitDescriptor> &UnitDescriptors)
{
	for (const auto &UnitDescriptor : UnitDescriptors)
	{
		const FVector *SpawnLocation = new FVector(CalcCellPosition(UnitDescriptor.Position));
		const TSubclassOf<AActor> UnitClass = (UnitDescriptor.Team == 1) ? UnitTeam1Class : UnitTeam2Class;
		AActor *UnitActor = GetWorld()->SpawnActor(UnitClass, SpawnLocation);
		UnitActorsMap.Emplace(UnitDescriptor.Id, UnitActor);
		UnitMovementVectorsMap.Emplace(UnitDescriptor.Id, FVector());

		UE_LOG(LogTemp, Log, TEXT("%f"), SpawnLocation->X);
	}
	
}

void AVisualizationManager::OnSimulationTick(float TimeRate, const TArray<FUnitDescriptor> NewUnitDescriptors)
{
	//Calc new position in world coordinates
	for (const FUnitDescriptor &UnitDescriptor : NewUnitDescriptors)
	{
		if (!UnitActorsMap.Contains(UnitDescriptor.Id))
		{
			continue;
		}
		
		AActor *UnitActor = UnitActorsMap.FindChecked(UnitDescriptor.Id);
		const FVector OldPositionVector = UnitActor->GetActorLocation();

		const FVector NextPositionVector = CalcCellPosition(UnitDescriptor.Position);
		UnitMovementVectorsMap.FindChecked(UnitDescriptor.Id) = (NextPositionVector - OldPositionVector) / TimeRate;

		if (!UnitDescriptor.IsAlive())
		{
			UnitActor->Destroy();
			UnitActorsMap.Remove(UnitDescriptor.Id);
			UnitMovementVectorsMap.Remove(UnitDescriptor.Id);
		}
	}
}

FVector AVisualizationManager::CalcCellPosition(const FVector2d &Coordinates)
{
	int X = Coordinates.X * CellRadius + Coordinates.Y * 0.5;
	int Y = (sqrt(3) / 2) * Coordinates.Y * CellRadius;
	return FVector(X, Y, 0);
}
