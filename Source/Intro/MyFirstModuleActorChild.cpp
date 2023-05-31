// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstModuleActorChild.h"

void AMyFirstModuleActorChild::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Hello from MyFirstModule Child"));
}
