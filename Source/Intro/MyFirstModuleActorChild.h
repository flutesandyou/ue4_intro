// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/MyFirstModuleActor.h"
#include "MyFirstModuleActorChild.generated.h"

/**
 * 
 */
UCLASS()
class INTRO_API AMyFirstModuleActorChild : public AMyFirstModuleActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
