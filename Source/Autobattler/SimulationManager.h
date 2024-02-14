// // Created by N. Gezhes, ngezhes@temporal-games.com

#pragma once
#include "UnitDescriptor.h"
#include "SimulationManager.generated.h"

class AVisualizationManager;

USTRUCT()
struct FSimulationParams
{
	GENERATED_BODY()
	
	UPROPERTY()
	float TimeRate;
	
	UPROPERTY()
	TArray<FVector2D> Team1StartPositions;
	
	UPROPERTY()
	TArray<FVector2D> Team2StartPositions;

	UPROPERTY()
	TSubclassOf<AActor> UnitTeam1Class;

	UPROPERTY()
	TSubclassOf<AActor> UnitTeam2Class;
};

UCLASS()
class UFSimulationManager : public UObject
{	
	GENERATED_BODY()
	
public:
	void StartSimulation(AVisualizationManager *InVisualizationManager, const FSimulationParams &SimulationParams);

private:
	void UpdateSimulation();

	void SetupUnits(const TArray<FVector2D> &Team1StartPositions, const TArray<FVector2D> &Team2StartPositions);

	void FillUnitValues(FUnitDescriptor &Unit) const; 
	static FVector2D CalcMovementVector(const FUnitDescriptor &Unit, const FUnitDescriptor &TargetUnit);

	UPROPERTY()
	AVisualizationManager *VisualizationManager;
	
	UPROPERTY()
	FTimerHandle SimulationTimerHandle;

	UPROPERTY()
	TArray<FUnitDescriptor> Units;

	UPROPERTY()
	float TimeRate;

	FRandomStream RandomStream = FRandomStream(567);
};
