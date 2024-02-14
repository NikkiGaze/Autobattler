// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitActorBase.h"


AUnitActorBase::AUnitActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitActorBase::StartAttack()
{
	Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()))
		->SetMaterial(0, AttackMaterial);

	GetWorldTimerManager().SetTimer(AttackAnimationTimerHandle, this, &AUnitActorBase::FinishAttack,
		0.3f);
	
}

void AUnitActorBase::FinishAttack() const
{
	Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()))
		->SetMaterial(0, DefaultMaterial);
}


