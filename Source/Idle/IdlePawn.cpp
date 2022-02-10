// Fill out your copyright notice in the Description page of Project Settings.


#include "IdlePawn.h"
#include"IdleFunctionLibrary.h"
#include"Modules/ModuleBase.h"


// Sets default values
AIdlePawn::AIdlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIdlePawn::BeginPlay()
{
	Super::BeginPlay();

	UIdleGameInstance* gameInstance = UIdleFunctionLibrary::GetIdleGameInstance();
	gameInstance->SetPawn(this);
	gameInstance->CreateMainWidget();
	gridSize = gameInstance->GetGridSize();
	modulesGrid = new UModuleBase **[gridSize.Y];
	ResourcesCount = gameInstance->GetStartResources();
	DefaultGeneratedResources = gameInstance->GetDefaultGeneratedResources();

	for (int i = 0; i < gridSize.Y; i++)
	{
		modulesGrid[i] = new UModuleBase * [gridSize.X]{ nullptr };
	}
}

void AIdlePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (int i = 0; i < gridSize.Y; i++)
	{
		delete[] modulesGrid[i];
	}
	delete[] modulesGrid;
}

// Called every frame
void AIdlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float NewResource = DefaultGeneratedResources * DeltaTime;
	for (int i = 0; i < gridSize.Y; i++)
	{
		for (int j = 0; j < gridSize.X; j++)
		{
			if(modulesGrid[i][j] == nullptr) continue;

			NewResource += modulesGrid[i][j]->Tick(DeltaTime);
			UE_LOG(LogTemp, Warning, TEXT("%d"), NewResource);
		}
	}

	ResourcesCount += NewResource;
	ResourcesSpeed = NewResource / DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("res %f"), NewResource);
	UE_LOG(LogTemp, Warning, TEXT("speed %f, detla time %f"), ResourcesSpeed, DeltaTime);

}

// Called to bind functionality to input
void AIdlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AIdlePawn::SetModuleSlot(int id, int row, int column)
{
	UModuleBase*& moduleSlot = modulesGrid[row][column];

	UModuleInfoDataAsset* moduleInfo = UIdleFunctionLibrary::GetIdleGameInstance()->GetModuleInfo(id);

	int Cost = moduleInfo->Levels[0].Cost;
	if (ResourcesCount < Cost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough resources!"));
		return false;
	}

	ResourcesCount -= Cost;

	moduleSlot = NewObject<UModuleBase>(moduleInfo->Class);
	if (moduleSlot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create module!"));
		return false;
	}

	moduleSlot->SetModuleInfo(moduleInfo);
	TArray<UModuleBase**> Neighbours;
	if(row - 1 >= 0) Neighbours.Add(&modulesGrid[row-1][column]);
	if (row + 1 < gridSize.Y) Neighbours.Add(&modulesGrid[row + 1][column]);
	if (column - 1 >= 0) Neighbours.Add(&modulesGrid[row][column - 1]);
	if (column + 1 < gridSize.X) Neighbours.Add(&modulesGrid[row][column + 1]);

	moduleSlot->SetNeighbours(Neighbours);
	moduleSlot->SetTickLength(UIdleFunctionLibrary::GetIdleGameInstance()->GetTickLength());
	
	return true;
}

bool AIdlePawn::IncrementUpgradeLevel()
{ 
	int Threshold = UIdleFunctionLibrary::GetIdleGameInstance()->GetThresholds(UpgradeLevel);
	if (ResourcesCount < Threshold) return false;
	ResourcesCount -= Threshold;

	UpgradeLevel++; 

	for (int i = 0; i < gridSize.Y; i++)
	{
		for (int j = 0; j < gridSize.X; j++)
		{
			if (modulesGrid[i][j] == nullptr) continue;

			modulesGrid[i][j]->RemoveFromRoot();
			modulesGrid[i][j] = nullptr;
		}
	}

	return true;
}

bool AIdlePawn::UpgradeModule(int row, int column)
{
	UModuleBase* moduleSlot = modulesGrid[row][column];

	int Cost = moduleSlot->GetUpgradeCost();

	if (Cost < 0.0f || ResourcesCount < Cost) return false;

	ResourcesCount -= Cost;

	moduleSlot->Upgrade();

	return true;
}

UTexture2D* AIdlePawn::GetModuleLevelTexture(int row, int column) const
{
	UModuleBase* moduleSlot = modulesGrid[row][column];

	return moduleSlot->GetCurrentTexture();
}

bool AIdlePawn::IsLevelUpgradeAvailable() const
{
	return (ResourcesCount >= UIdleFunctionLibrary::GetIdleGameInstance()->GetThresholds(UpgradeLevel));
}