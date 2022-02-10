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
	int Level = 0;

	FORCEINLINE void SetModuleInfo(UModuleInfoDataAsset* NewInfo) { Info = NewInfo; }
	FORCEINLINE void SetNeighbours(TArray<UModuleBase**> NewNeighbours) { Neighbours = NewNeighbours; }
	FORCEINLINE void SetTickLength(float NewTickLength) { TickLength = NewTickLength; }

public:
	UModuleInfoDataAsset* Info;
	TArray<UModuleBase**> Neighbours;

	UPROPERTY(EditAnywhere)
	int LevelModifier = 0;
	UPROPERTY(EditAnywhere)
	float ResourcesPerTick = 0.0f;
	UPROPERTY(EditAnywhere)
	float ResourcesModifier = 1.0f;
	UPROPERTY(EditAnywhere)
	float TickModifier = 1.0f;

	UFUNCTION(BlueprintCallable)
	TArray<UModuleBase*> GetModuleSlotNeighbours(int& length) const;

	float Tick(float DeltaTime);
	void Upgrade();
	float GetUpgradeCost() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpgrade();

	UFUNCTION(BlueprintCallable, Category="Module")
	FORCEINLINE int GetLevel() const { return Level + LevelModifier; }

	FORCEINLINE UTexture2D* GetCurrentTexture() const { return Info->Levels[Level].Texture; }

	UFUNCTION(BlueprintCallable, Category = "Module")
	FORCEINLINE int GetModifier1() const { return Info->Levels[Level].Modifier1; }

	UFUNCTION(BlueprintCallable, Category = "Module")
	FORCEINLINE int GetModifier2() const { return Info->Levels[Level].Modifier2; }

	UFUNCTION(BlueprintCallable, Category = "Module")
	FORCEINLINE FModuleLevelInfo GetLevelInfo() const { return Info->Levels[Level]; }

	UFUNCTION(BlueprintCallable, Category = "Module")
	void SetLevelModifier(int modifier);

	UFUNCTION(BlueprintCallable, Category = "Module")
	void SetResourcesModifier(float modifier);

	UFUNCTION(BlueprintCallable, Category = "Module")
	void SetTickModifier(float modifier);

	UFUNCTION(BlueprintCallable, Category = "Module")
	void RefreshNeighbours();

};
