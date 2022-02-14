// Idle game created for application purpouse by Aleksander Filek

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
	RefreshNeighbours();
}

float UModuleBase::GetUpgradeCost() const
{ 
	if (Level >= (Info->Levels.Num() - 1)) return -1.0f;

	return Info->Levels[Level].Cost; 
}

TArray<UModuleBase*> UModuleBase::GetNeighbours(int& length) const
{
	TArray<UModuleBase*> result;
	for (int i = 0; i < Neighbours.Num(); i++)
	{
		if (*(Neighbours[i]) == nullptr) continue;

		result.Add(*Neighbours[i]);
	}

	length = result.Num();
	return result;
}

void UModuleBase::RefreshNeighbours()
{
	for (int i = 0; i < Neighbours.Num(); i++)
	{
		if (*(Neighbours[i]) == nullptr) continue;

		(*(Neighbours[i]))->OnUpgrade();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(*(Neighbours[i]))->GetName().ToString());
	}
}

UTexture2D* UModuleBase::GetTexture(int level) const
{ 
	if (level >= Info->Levels.Num())
		return nullptr;
	return  Info->Levels[(level < 0) ? Level : level].Texture; 
}
