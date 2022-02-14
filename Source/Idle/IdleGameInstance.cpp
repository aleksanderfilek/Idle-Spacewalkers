// Idle game created for application purpouse by Aleksander Filek


#include "IdleGameInstance.h"

UIdleGameInstance* UIdleGameInstance::Instance = nullptr;

UIdleGameInstance::UIdleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UIdleGameInstance::Instance = this;
}

void UIdleGameInstance::Init()
{
	if (!IsValid(MainWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Main Widget is NONE"));
		return;
	}

	if (!IsValid(GameAsset))
	{
		UE_LOG(LogTemp, Error, TEXT("Game asset is NONE"));
		return;
	}
}

void UIdleGameInstance::CreateMainWidget()
{
	MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
	MainWidget->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

FIntPoint UIdleGameInstance::GetGridSize() const
{ 
	return FIntPoint(GameAsset->GridWidth, GameAsset->GridHeight);
}