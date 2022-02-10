// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IdlePawn.generated.h"

UCLASS()
class IDLE_API AIdlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIdlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UModuleBase*** modulesGrid;
	FIntPoint gridSize;
	float DefaultGeneratedResources;

public:
	UPROPERTY(BlueprintReadOnly)
	float ResourcesCount = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float ResourcesSpeed = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	int UpgradeLevel = 0;

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool SetModuleSlot(int id, int row, int column);

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool IncrementUpgradeLevel();

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool IsLevelUpgradeAvailable() const;

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool UpgradeModule(int row, int column);

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	UTexture2D* GetModuleLevelTexture(int level, int row, int column) const;

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	void AddResources(int count) { ResourcesCount += count; }

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool IsModuleSlotAvailable(int row, int column) const { return (modulesGrid[row][column] == nullptr); }


};
