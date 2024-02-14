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
	// Sets default values for this actor's properties
	AVisualizationManager();

	virtual void Tick(float DeltaTime) override;

	void InitialSpawn(TSubclassOf<AActor> UnitTeam1Class,
		TSubclassOf<AActor> UnitTeam2Class,
		const TArray<FUnitDescriptor> &UnitDescriptors);

	void OnSimulationTick(int NewPosition);
	
	UPROPERTY()
	AActor *UnitActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	int OldPosition;

	UPROPERTY()
	int NextPosition;
	
	UPROPERTY()
	FVector CurrentOffsetVector;

private:
	static FVector CalcCellPosition(const FVector2d &Coordinates);
};
