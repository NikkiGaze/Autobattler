#include "SimulationManager.h"

#include "VisualizationManager.h"

void UFSimulationManager::StartSimulation(AVisualizationManager *InVisualizationManager, const FSimulationParams &SimulationParams)
{
	VisualizationManager = InVisualizationManager;
	TimeRate = SimulationParams.TimeRate;

	SetupUnits(SimulationParams.Team1StartPositions, SimulationParams.Team2StartPositions);

	VisualizationManager->InitialSpawn(SimulationParams.UnitTeam1Class, SimulationParams.UnitTeam2Class, Units);
	VisualizationManager->GetWorld()->GetTimerManager().SetTimer
		(SimulationTimerHandle, this, &UFSimulationManager::UpdateSimulation, TimeRate, true);
}

void UFSimulationManager::UpdateSimulation()
{
	// for (FUnitDescriptor &Unit : Units)
	// {
	// 	Unit.Position.X += Unit.MovementSpeed;
	// 	//calc new position
	// }
	if (FVector2D::DistSquared(Units[0].Position, Units[1].Position) >= 64)
	{
		Units[0].Position += CalcMovementVector(Units[0], Units[1]);
		Units[1].Position += CalcMovementVector(Units[1], Units[0]);
	}
	else
	{
		//fight
	}
	VisualizationManager->OnSimulationTick(TimeRate, Units);
}

void UFSimulationManager::SetupUnits(const TArray<FVector2D> &Team1StartPositions, const TArray<FVector2D> &Team2StartPositions)
{
	int Unit1PositionIndex = RandomStream.RandRange(0, Team1StartPositions.Num() - 1);
	int Unit2PositionIndex = RandomStream.RandRange(0, Team2StartPositions.Num() - 1);
	
	FUnitDescriptor FirstUnit, SecondUnit;
	FillUnitValues(FirstUnit);
	FillUnitValues(SecondUnit);
	
	FirstUnit.Position = Team1StartPositions[Unit1PositionIndex];
	FirstUnit.Team = 1;
	
	SecondUnit.Team = 2;
	SecondUnit.Position = Team2StartPositions[Unit2PositionIndex];	

	Units.Add(FirstUnit);
	Units.Add(SecondUnit);
}

void UFSimulationManager::FillUnitValues(FUnitDescriptor &Unit) const
{
	Unit.Id = FGuid::NewGuid();
	Unit.MovementSpeed = 5;
	Unit.AttackSpeed = 3;
	Unit.MaxHealth = RandomStream.RandRange(2, 5);
	Unit.CurrentHealth = Unit.MaxHealth;
};

FVector2D UFSimulationManager::CalcMovementVector(const FUnitDescriptor &Unit, const FUnitDescriptor &TargetUnit)
{
	FVector2D OffsetVector;
	const int DistX = TargetUnit.Position.X - Unit.Position.X;
	const int DistY = TargetUnit.Position.Y - Unit.Position.Y;

	//(DistX / DistY) / (1 + DistX / DistY)  = offset1x
	//I know I can use smth like Lerp but I like math ^))

	OffsetVector.X =  Unit.MovementSpeed * (FGenericPlatformMath::Abs((float)DistX / DistY) / (1 + FGenericPlatformMath::Abs((float)DistX / DistY))) * FGenericPlatformMath::Sign(DistX);
	OffsetVector.Y = (Unit.MovementSpeed - FGenericPlatformMath::Abs(OffsetVector.X)) * FGenericPlatformMath::Sign(DistY);
	// UE_LOG(LogTemp, Log, TEXT("%d, %d"), OffsetX, OffsetY);

	return OffsetVector;
}
