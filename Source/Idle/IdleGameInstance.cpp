// Fill out your copyright notice in the Description page of Project Settings.


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

UUserWidget* UIdleGameInstance::CreateMainWidget()
{
	MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
	MainWidget->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
	
	return MainWidget;
}

FIntPoint UIdleGameInstance::GetGridSize() const
{ 
	return FIntPoint(GameAsset->GridWidth, GameAsset->GridHeight);
}