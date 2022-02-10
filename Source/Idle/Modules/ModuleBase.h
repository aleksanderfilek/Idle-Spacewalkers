// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include"GameDataAsset.h"
#include "ModuleBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class IDLE_API UModuleBase : public UObject
{
	GENERATED_BODY()

	friend class AIdlePawn;
private:
	float TickLength = 1.0f;
	int Level = -1;

	UModuleInfoDataAsset* Info;
	TArray<UModuleBase**> Neighbours;

	int LevelModifier = 0;
	float ResourcesPerTick = 10.0f;
	float ResourcesModifier = 1.0f;
	float TickModifier = 1.0f;

	FORCEINLINE void SetModuleInfo(UModuleInfoDataAsset* NewInfo) { Info = NewInfo; }
	FORCEINLINE void SetNeighbours(TArray<UModuleBase**> NewNeighbours) { Neighbours = NewNeighbours; }
	FORCEINLINE void SetTickLength(float NewTickLength) { TickLength = NewTickLength; }

public:

	UFUNCTION(BlueprintCallable)
	TArray<UModuleBase*> GetModuleSlotNeighbours(int& length) const;

	float Tick(float DeltaTime);
	void Upgrade();
	float GetUpgradeCost() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpgrade();

	UFUNCTION(BlueprintCallable, Category="Module")
	FORCEINLINE int GetLevel() const { return Level + LevelModifier; }

	FORCEINLINE UTexture2D* GetTexture(int level) const { return Info->Levels[level].Texture; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE float GetModifier1() const { return Info->Levels[Level].Modifier1; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE float GetModifier2() const { return Info->Levels[Level].Modifier2; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE FModuleLevelInfo GetLevelInfo() const { return Info->Levels[Level]; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	void SetLevelModifier(int modifier);
	UFUNCTION(BlueprintCallable, Category = "Module Base")
	void SetResourcesPerTick(float resources);
	UFUNCTION(BlueprintCallable, Category = "Module Base")
	void SetResourcesModifier(float modifier);

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	void SetTickModifier(float modifier);

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	void RefreshNeighbours();

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE bool IsModuleWithName(FName name) const { return (Info->Name.Compare(name) == 0); }
};
