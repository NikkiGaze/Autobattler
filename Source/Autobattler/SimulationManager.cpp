#include "SimulationManager.h"

#include "VisualizationManager.h"

void UFSimulationManager::StartSimulation(AVisualizationManager *InVisualizationManager, const FSimulationParams &SimulationParams)
{
	VisualizationManager = InVisualizationManager;
	TimeRate = SimulationParams.TimeRate;

	FUnitDescriptor FirstUnit;
	FirstUnit.Id = FGuid::NewGuid();
	FirstUnit.Position = SimulationParams.Team1StartPositions[0];
	FirstUnit.Team = 1;
	FirstUnit.MovementSpeed = 5;
	
	FUnitDescriptor SecondUnit;
	SecondUnit.Id = FGuid::NewGuid();
	SecondUnit.Team = 2;
	SecondUnit.Position = SimulationParams.Team2StartPositions[0];	
	SecondUnit.MovementSpeed = 5;
	
	Units.Add(FirstUnit);
	Units.Add(SecondUnit);
	
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
		int DistX = Units[1].Position.X - Units[0].Position.X;		
		int DistY = Units[1].Position.Y - Units[0].Position.Y;

		//(DistX / DistY) / (1 + DistX / DistY)  = offset1x
		
		
		int OffsetX =  Units[0].MovementSpeed * (FGenericPlatformMath::Abs((float)DistX / DistY) / (1 + FGenericPlatformMath::Abs((float)DistX / DistY))) * FGenericPlatformMath::Sign(DistX);
		int OffsetY = (Units[0].MovementSpeed - FGenericPlatformMath::Abs(OffsetX)) * FGenericPlatformMath::Sign(DistY);
		UE_LOG(LogTemp, Log, TEXT("%d, %d"), OffsetX, OffsetY);
		
		Units[0].Position.X = Units[0].Position.X + OffsetX;
		Units[0].Position.Y = Units[0].Position.Y + OffsetY;

		////
		
		DistX = Units[0].Position.X - Units[1].Position.X;		
		DistY = Units[0].Position.Y - Units[1].Position.Y;

		OffsetX =  Units[1].MovementSpeed * (FGenericPlatformMath::Abs((float)DistX / DistY) / (1 + FGenericPlatformMath::Abs((float)DistX / DistY))) * FGenericPlatformMath::Sign(DistX);
		OffsetY = (Units[1].MovementSpeed - FGenericPlatformMath::Abs(OffsetX)) * FGenericPlatformMath::Sign(DistY);
		UE_LOG(LogTemp, Log, TEXT("%d, %d"), OffsetX, OffsetY);
		
		Units[1].Position.X = Units[1].Position.X + OffsetX;
		Units[1].Position.Y = Units[1].Position.Y + OffsetY;
	}
	else
	{
		//fight
	}
	VisualizationManager->OnSimulationTick(TimeRate, Units);
}
