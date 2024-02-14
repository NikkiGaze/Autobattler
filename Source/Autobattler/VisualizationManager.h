// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnitDescriptor.h"
#include "GameFramework/Actor.h"
#include "VisualizationManager.generated.h"

UCLASS()
class AUTOBATTLER_API AVisualizationManager : public AActor
{
	GENERATED_BODY()

public:
	AVisualizationManager();

	virtual void Tick(float DeltaTime) override;

	void InitialSpawn(TSubclassOf<AActor> UnitTeam1Class,
		TSubclassOf<AActor> UnitTeam2Class,
		const TArray<FUnitDescriptor> &UnitDescriptors);

	void OnSimulationTick(float TimeRate, const TArray<FUnitDescriptor> NewUnitDescriptors);

protected:
	virtual void BeginPlay() override;

private:
	static FVector CalcCellPosition(const FVector2d &Coordinates);
	
	inline static int CellRadius = 200;
	
	UPROPERTY()
	TMap<FGuid, AActor *> UnitActorsMap;

	UPROPERTY()
	TMap<FGuid, FVector> UnitMovementVectorsMap;
};
