// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitActorBase.h"


// Sets default values
AUnitActorBase::AUnitActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	AddInstanceComponent(StaticMeshComponent);
}

void AUnitActorBase::StartAttack() const
{
	StaticMeshComponent->SetMaterial(0, AttackMaterial);
}


