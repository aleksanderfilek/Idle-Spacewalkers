// Fill out your copyright notice in the Description page of Project Settings.

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
	static UIdleGameInstance* GetIdleGameInstance();
	
};
