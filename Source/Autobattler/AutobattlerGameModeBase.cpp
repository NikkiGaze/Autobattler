// Copyright Epic Games, Inc. All Rights Reserved.

#include "VisualizationManager.h"
#include "AutobattlerGameModeBase.h"

void AAutobattlerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	VisualizationManager = Cast<AVisualizationManager>(GetWorld()->SpawnActor(AVisualizationManager::StaticClass()));
	VisualizationManager->InitialSpawn(UnitClass);

	GetWorldTimerManager().SetTimer(SimulationTimerHandle, []
		{}, 5.f, true);
}
