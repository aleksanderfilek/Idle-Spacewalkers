// Idle game created for application purpouse by Aleksander Filek

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
	float ResourcesCount = 0.0f;
	float ResourcesSpeed = 0.0f;
	int Level = 0;
	FIntPoint gridSize;
	float DefaultGeneratedResources;

public:
	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	FORCEINLINE float GetResourcesCount() const { 
		return ResourcesCount; }

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	FORCEINLINE float GetResourcesSpeed() const { 
		return ResourcesSpeed; }

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	FORCEINLINE int GetLevel() const { 
		return Level; }

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool Upgrade();

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool IsUpgradeAvailable() const;

private:
	class UModuleBase*** modulesGrid;

public:
	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool CreateModule(int id, int row, int column);

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool UpgradeModule(int row, int column);

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	UTexture2D* GetModuleLevelTexture(int level, int row, int column) const;

	UFUNCTION(BlueprintCallable, Category = "IdlePawn")
	bool IsModuleSlotAvailable(int row, int column) const { 
		return (modulesGrid[row][column] == nullptr); }
};
