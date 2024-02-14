// // Created by N. Gezhes, ngezhes@temporal-games.com

#pragma once

#include "UnitDescriptor.generated.h"
USTRUCT()
struct FUnitDescriptor
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid Id;
	
	UPROPERTY()
	int MaxHealth;
	
	UPROPERTY()
	int CurrentHealth;
	
	UPROPERTY()
	int AttackSpeed;
	
	UPROPERTY()
	int MovementSpeed;
	
	UPROPERTY()
	int Team;

	UPROPERTY()
	int TargetIndex;

	UPROPERTY()
	FGuid AttackTargetId;

	UPROPERTY()
	int AttackStartTickNum;
	
	UPROPERTY()
	FVector2D Position;
	
	bool IsAlive() const
	{
		return CurrentHealth > 0;
	}
};
