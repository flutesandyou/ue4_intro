// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IntroGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class INTRO_API UIntroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	const FColor& GetPlayerColor();

private:
	FColor PlayerColor = FColor::Black;
};
