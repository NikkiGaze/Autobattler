// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AutobattlerGameModeBase.generated.h"

class UFSimulationManager;
class AVisualizationManager;
/**
 * 
 */
UCLASS()
class AUTOBATTLER_API AAutobattlerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> UnitTeam1Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> UnitTeam2Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector2D> Team1StartPositions;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector2D> Team2StartPositions;

private:
	UPROPERTY()
	AVisualizationManager *VisualizationManager;

	UPROPERTY()
	UFSimulationManager *SimulationManager;
};
