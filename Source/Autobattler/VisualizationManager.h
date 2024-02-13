﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void InitialSpawn(TSubclassOf<AActor> UnitClass);

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
};