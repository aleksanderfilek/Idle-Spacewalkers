// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"Blueprint/UserWidget.h"
#include"Modules/GameDataAsset.h"
#include"IdlePawn.h"
#include "IdleGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class IDLE_API UIdleGameInstance : public UGameInstance
{
	GENERATED_BODY()

	static UIdleGameInstance* Instance;

public:
	UIdleGameInstance(const FObjectInitializer& ObjectInitializer);

	inline static UIdleGameInstance* Get() { return UIdleGameInstance::Instance; }

	virtual void Init() override;

private:
	UUserWidget* MainWidget;

	AIdlePawn* Pawn;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere)
	UGameDataAsset* GameAsset;

	UPROPERTY(EditAnywhere)
	UTexture2D* DefaultGridTexture;

public:
	FORCEINLINE UUserWidget* GetMainWidget() const { return MainWidget; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AIdlePawn* GetPawn() const { return Pawn; }

	UUserWidget* CreateMainWidget();
	FORCEINLINE void SetPawn(AIdlePawn* NewPawn) { Pawn = NewPawn; }

	UFUNCTION(BlueprintCallable)
	FIntPoint GetGridSize() const;
	FORCEINLINE float GetStartResources() const { return GameAsset->StartResources; }
	FORCEINLINE float GetThresholds(int currentLevel) const { return GameAsset->Thresholds[currentLevel]; }
	FORCEINLINE float GetDefaultGeneratedResources() const { return GameAsset->DefaultGeneratedResources; }
	FORCEINLINE float GetTickLength() const { return GameAsset->TickLength; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UModuleInfoDataAsset* GetModuleInfo(int id) const { return GameAsset->Modules[id]; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetModuleNumber() const { return GameAsset->Modules.Num(); }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetDefaultGridTexture() const { return DefaultGridTexture; }

};
