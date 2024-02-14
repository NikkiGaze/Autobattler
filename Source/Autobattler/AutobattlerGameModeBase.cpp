// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutobattlerGameModeBase.h"

#include "SimulationManager.h"
#include "VisualizationManager.h"


void AAutobattlerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	VisualizationManager = Cast<AVisualizationManager>(GetWorld()->SpawnActor(AVisualizationManager::StaticClass()));

	SimulationManager = NewObject<UFSimulationManager>();
	FSimulationParams Params;
	Params.TimeRate = 5.f;
	Params.Team1StartPositions = Team1StartPositions;
	Params.Team2StartPositions = Team2StartPositions;
	Params.UnitTeam1Class = UnitTeam1Class;
	Params.UnitTeam2Class = UnitTeam2Class;
	
	
	SimulationManager->StartSimulation(VisualizationManager, Params);
}
