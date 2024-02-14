// // Created by N. Gezhes, ngezhes@temporal-games.com

#pragma once

#include "UnitDescriptor.generated.h"
USTRUCT()
struct FUnitDescriptor
{
	GENERATED_BODY()
	
	FGuid Id;
	int MaxHealth;
	int CurrentHealth;
	int AttackSpeed;
	int MovementSpeed;
	int Team;
	
	FVector2d Position;
	
	bool IsAlive() const
	{
		return CurrentHealth > 0;
	}
};
