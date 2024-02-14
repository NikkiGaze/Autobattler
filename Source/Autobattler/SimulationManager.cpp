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
	for (FUnitDescriptor &Unit : Units)
	{
		Unit.Position.X += Unit.MovementSpeed;
		//calc new position
	}
	VisualizationManager->OnSimulationTick(TimeRate, Units);
}
