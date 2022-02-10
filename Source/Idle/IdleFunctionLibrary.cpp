// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleFunctionLibrary.h"

UIdleGameInstance* UIdleFunctionLibrary::GetIdleGameInstance()
{
	return UIdleGameInstance::Get();
}