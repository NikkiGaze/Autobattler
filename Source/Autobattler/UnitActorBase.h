// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitActorBase.generated.h"

UCLASS()
class AUTOBATTLER_API AUnitActorBase : public AActor
{
	GENERATED_BODY()

public:
	AUnitActorBase();

	void StartAttack() const;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent *StaticMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *DefaultMaterial;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface *AttackMaterial;
};
