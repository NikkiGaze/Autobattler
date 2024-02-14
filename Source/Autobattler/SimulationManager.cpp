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
	for (FUnitDescriptor &Unit : Units)
	{
		//calc new position

		if (FVector2D::DistSquared(Unit.Position, Units[Unit.TargetIndex].Position) >= 64)
		{
			Unit.Position += CalcMovementVector(Unit, Units[Unit.TargetIndex]);
			// Units[1].Position += CalcMovementVector(Units[1], Units[0]);
		}
		else
		{
			//fight
		}
	}
	VisualizationManager->OnSimulationTick(TimeRate, Units);
}

void UFSimulationManager::SetupUnits(const TArray<FVector2D> &Team1StartPositions, const TArray<FVector2D> &Team2StartPositions)
{
	int UnitCount = 4;
	Units.SetNum(UnitCount);

	TArray<FVector2D> UnitPositionIndexes;
	UnitPositionIndexes.SetNum(UnitCount);


	for (int i = 0; i < Units.Num(); i++)
	{
		FillUnitValues(Units[i]);

		Units[i].Team = i < 2 ? 1 : 2;
		Units[i].TargetIndex = i < 2 ? i + 2 : i - 2;

		//Dont look here please ^)
		Units[i].TargetIndex = i < 2 ? i + 2 : i - 2;
		int PositionIndex;
		if (i % 2 == 0)
		{
			PositionIndex = RandomStream.RandRange(0, (Team1StartPositions.Num() - 1) / 2);
		}
		else
		{
			PositionIndex = RandomStream.RandRange((Team1StartPositions.Num() - 1) / 2 + 1, (Team1StartPositions.Num() - 1));
		}
		
		Units[i].Position = i < 2 ? Team1StartPositions[PositionIndex] : Team2StartPositions[PositionIndex];
	}
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

	float Coeff = (DistY == 0) ? 1 : FGenericPlatformMath::Abs(static_cast<float>(DistX) / DistY);

	OffsetVector.X =  Unit.MovementSpeed * (Coeff / (1 + Coeff)) * FGenericPlatformMath::Sign(DistX);
	OffsetVector.Y = (Unit.MovementSpeed - FGenericPlatformMath::Abs(OffsetVector.X)) * FGenericPlatformMath::Sign(DistY);
	UE_LOG(LogTemp, Log, TEXT("%d, %d, %f, %f"), DistX, DistY, OffsetVector.X, OffsetVector.Y);

	return OffsetVector;
}
