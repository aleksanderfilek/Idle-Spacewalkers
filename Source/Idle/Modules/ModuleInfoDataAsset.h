// Idle game created for application purpouse by Aleksander Filek

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "ModuleInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FModuleLevelInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Level Info")
	float Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Level Info")
	float Modifier1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Level Info")
	float Modifier2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Level Info")
	UTexture2D* Texture;
};


UCLASS(BlueprintType)
class IDLE_API UModuleInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Info")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Info")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Info")
	TSubclassOf<class UModuleBase> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Module Info")
	TArray<FModuleLevelInfo> Levels;
};
