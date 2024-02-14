// Copyright Epic Games, Inc. All Rights Reserved.

#include "AutobattlerGameModeBase.h"

#include "VisualizationManager.h"


void AAutobattlerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FUnitDescriptor FirstUnit;
	FirstUnit.Position = FVector2d(0, 0);
	FirstUnit.Team = 1;
	
	FUnitDescriptor SecondUnit;
	SecondUnit.Team = 2;
	SecondUnit.Position = FVector2d(5, 5);
	TArray<FUnitDescriptor> Units;
	Units.Add(FirstUnit);
	Units.Add(SecondUnit);
	
	VisualizationManager = Cast<AVisualizationManager>(GetWorld()->SpawnActor(AVisualizationManager::StaticClass()));
	VisualizationManager->InitialSpawn(UnitTeam1Class, UnitTeam2Class, Units);

	
	GetWorldTimerManager().SetTimer(SimulationTimerHandle, [this]
		{Tick++, VisualizationManager->OnSimulationTick(Tick);},
		5.f, true);
}
