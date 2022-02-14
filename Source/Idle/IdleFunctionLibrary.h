// Idle game created for application purpouse by Aleksander Filek

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include"IdleGameInstance.h"

#include "IdleFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class IDLE_API UIdleFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Idle Library")
	static FORCEINLINE UIdleGameInstance* GetIdleGameInstance() {
		return UIdleGameInstance::Get();
	}
	
	UFUNCTION(BlueprintCallable, Category = "Idle Library")
	static FORCEINLINE AIdlePawn* GetIdlePawn() {
		return UIdleGameInstance::Get()->GetPawn();
	}

	UFUNCTION(BlueprintCallable, Category = "Idle Library")
	static FORCEINLINE UUserWidget* GetMainBP() {
		return UIdleGameInstance::Get()->GetMainWidget();
	}
};
