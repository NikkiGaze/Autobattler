// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AutobattlerGameModeBase.generated.h"

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> UnitTeam1Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> UnitTeam2Class;

private:
	UPROPERTY()
	AVisualizationManager *VisualizationManager;

	UPROPERTY()
	FTimerHandle SimulationTimerHandle;

	int Tick = 0;
};
