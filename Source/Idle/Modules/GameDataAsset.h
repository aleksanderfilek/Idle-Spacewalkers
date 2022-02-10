// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include"ModuleInfoDataAsset.h"
#include "GameDataAsset.generated.h"

UCLASS(BlueprintType)
class IDLE_API UGameDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 GridWidth;

	UPROPERTY(EditAnywhere)
	int32 GridHeight;

	UPROPERTY(EditAnywhere)
	float StartResources;

	UPROPERTY(EditAnywhere)
	float DefaultGeneratedResources;

	UPROPERTY(EditAnywhere)
	float TickLength;

	UPROPERTY(EditAnywhere)
	TArray<float> Thresholds;

	UPROPERTY(EditAnywhere)
	TArray<UModuleInfoDataAsset*> Modules;
};
