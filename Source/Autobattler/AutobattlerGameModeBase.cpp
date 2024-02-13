// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutobattlerGameModeBase.h"

#include "VisualizationManager.h"


void AAutobattlerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	VisualizationManager = Cast<AVisualizationManager>(GetWorld()->SpawnActor(AVisualizationManager::StaticClass()));
	VisualizationManager->InitialSpawn(UnitTeam1Class, UnitTeam2Class, TArray<FUnitDescriptor>());

	GetWorldTimerManager().SetTimer(SimulationTimerHandle, [this]
		{Tick++, VisualizationManager->OnSimulationTick(Tick);},
		5.f, true);
}
