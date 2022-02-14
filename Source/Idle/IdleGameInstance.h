// Idle game created for application purpouse by Aleksander Filek

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

public:
	FORCEINLINE UUserWidget* GetMainWidget() const { 
		return MainWidget; }

	void CreateMainWidget();

	FORCEINLINE AIdlePawn* GetPawn() const { 
		return Pawn; }
	FORCEINLINE void SetPawn(AIdlePawn* NewPawn) { 
		Pawn = NewPawn; }

protected:
	UPROPERTY(EditAnywhere, Category="Idle Instance")
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Idle Instance")
	UGameDataAsset* GameAsset;

public:
	FORCEINLINE float GetStartResources() const { 
		return GameAsset->StartResources; }

	FORCEINLINE float GetThresholds(int currentLevel) const { 
		return GameAsset->Thresholds[currentLevel]; }

	FORCEINLINE float GetDefaultGeneratedResources() const { 
		return GameAsset->DefaultGeneratedResources; }

	FORCEINLINE float GetTickLength() const { 
		return GameAsset->TickLength; }

	UFUNCTION(BlueprintCallable, Category = "Idle Instance")
	FIntPoint GetGridSize() const;

	UFUNCTION(BlueprintCallable, Category = "Idle Instance")
	FORCEINLINE UModuleInfoDataAsset* GetModuleInfo(int id) const { 
		return GameAsset->Modules[id]; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetDefaultModuleTexture(int id) const { 
		return GameAsset->Modules[id]->Levels[0].Texture; }

	UFUNCTION(BlueprintCallable, Category = "Idle Instance")
		FORCEINLINE int GetModuleCount() const { 
		return GameAsset->Modules.Num(); }

protected:
	UPROPERTY(EditAnywhere, Category = "Idle Instance")
	UTexture2D* DefaultGridTexture;

public:
	UFUNCTION(BlueprintCallable, Category = "Idle Instance")
	FORCEINLINE UTexture2D* GetDefaultGridTexture() const { 
		return DefaultGridTexture; }

};
