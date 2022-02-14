// Idle game created for application purpouse by Aleksander Filek

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

	float Tick(float DeltaTime);
	void Upgrade();
	float GetUpgradeCost() const;
	void RefreshNeighbours();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Module Base")
	float TickLength = 1.0f;
	UPROPERTY(BlueprintReadOnly, Category = "Module Base")
	int Level = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Base")
	int LevelModifier = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Base")
	float ResourcesPerTick = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Base")
	float ResourcesModifier = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Base")
	float TickModifier = 1.0f;

public:
	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE int GetLevel() const { 
		return (Level + LevelModifier >= Info->Levels.Num())? Info->Levels.Num(): (Level + LevelModifier); }

private:
	UModuleInfoDataAsset* Info;
	TArray<UModuleBase**> Neighbours;

	FORCEINLINE void SetModuleInfo(UModuleInfoDataAsset* NewInfo) { 
		Info = NewInfo; }

	FORCEINLINE void SetNeighbours(TArray<UModuleBase**> NewNeighbours) { 
		Neighbours = NewNeighbours; }

public:
	UFUNCTION(BlueprintCallable, Category = "Module Base")
		TArray<UModuleBase*> GetNeighbours(int& length) const;

	UTexture2D* GetTexture(int level) const;

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE float GetModifier1() const { 
		return Info->Levels[GetLevel()].Modifier1; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE float GetModifier2() const { 
		return Info->Levels[GetLevel()].Modifier2; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE FModuleLevelInfo GetLevelInfo() const { 
		return Info->Levels[GetLevel()]; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE FName GetName() const { 
		return Info->Name; }

	UFUNCTION(BlueprintCallable, Category = "Module Base")
	FORCEINLINE bool IsModuleWithName(FName name) const { 
		return (Info->Name.Compare(name) == 0); }

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpgrade();
};
