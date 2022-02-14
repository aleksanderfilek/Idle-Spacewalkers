// Idle game created for application purpouse by Aleksander Filek


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
		}
	}

	ResourcesCount += NewResource;
	ResourcesSpeed = NewResource / DeltaTime;
}

// Called to bind functionality to input
void AIdlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool AIdlePawn::CreateModule(int id, int row, int column)
{
	UIdleGameInstance* gameInstance = UIdleFunctionLibrary::GetIdleGameInstance();
	UModuleBase*& moduleSlot = modulesGrid[row][column];

	UModuleInfoDataAsset* moduleInfo = gameInstance->GetModuleInfo(id);

	int Cost = moduleInfo->Levels[0].Cost;
	if (ResourcesCount < Cost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough resources!"));
		return false;
	}

	ResourcesCount -= Cost;

	moduleSlot = NewObject<UModuleBase>(gameInstance, moduleInfo->Class);
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
	moduleSlot->TickLength = gameInstance->GetTickLength();
	moduleSlot->Upgrade();

	return true;
}

bool AIdlePawn::Upgrade()
{ 
	UIdleGameInstance* gameInstance = UIdleFunctionLibrary::GetIdleGameInstance();

	int Threshold = gameInstance->GetThresholds(Level);
	if (ResourcesCount < Threshold) return false;

	ResourcesCount = gameInstance->GetStartResources();

	Level++; 

	for (int i = 0; i < gridSize.Y; i++)
	{
		for (int j = 0; j < gridSize.X; j++)
		{
			if (modulesGrid[i][j] == nullptr) continue;

			modulesGrid[i][j]->ConditionalBeginDestroy();
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

UTexture2D* AIdlePawn::GetModuleLevelTexture(int level, int row, int column) const
{
	UModuleBase* moduleSlot = modulesGrid[row][column];

	return moduleSlot->GetTexture(level);
}

bool AIdlePawn::IsUpgradeAvailable() const
{
	return (ResourcesCount >= UIdleFunctionLibrary::GetIdleGameInstance()->GetThresholds(Level));
}