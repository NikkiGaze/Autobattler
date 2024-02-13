// // Created by N. Gezhes, ngezhes@temporal-games.com

#pragma once

struct FUnitDescriptor
{
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
