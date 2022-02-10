// Fill out your copyright notice in the Description page of Project Settings.


#include "ModuleBase.h"

float UModuleBase::Tick(float DeltaTime)
{
	float ModifiedTick = TickLength * TickModifier;
	float NewResources = ResourcesPerTick * ResourcesModifier;
	NewResources /= ModifiedTick;
	NewResources *= DeltaTime;

	return NewResources;
}

void UModuleBase::Upgrade()
{
	Level++;

	OnUpgrade();
}

float UModuleBase::GetUpgradeCost() const
{ 
	if ((Level - 1) >= Info->Levels.Num()) return -1.0f;

	return Info->Levels[Level].Cost; 
}

TArray<UModuleBase*> UModuleBase::GetModuleSlotNeighbours(int& length) const
{
	TArray<UModuleBase*> result;
	for (int i = 0; i < Neighbours.Num(); i++)
	{
		result.Add(*Neighbours[i]);
	}

	length = result.Num();
	return result;
}

void UModuleBase::RefreshNeighbours()
{
	for (int i = 0; i < Neighbours.Num(); i++)
	{
		if (Neighbours[i] == nullptr) continue;

		(*Neighbours[i])->OnUpgrade();
	}
}

void UModuleBase::SetLevelModifier(int modifier)
{
	LevelModifier += modifier;
	RefreshNeighbours();
}

void UModuleBase::SetResourcesModifier(float modifier)
{
	ResourcesModifier *= modifier;
}

void UModuleBase::SetTickModifier(float modifier)
{
	TickModifier *= modifier;
}