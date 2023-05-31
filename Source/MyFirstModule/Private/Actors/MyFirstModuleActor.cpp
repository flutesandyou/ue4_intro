// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyFirstModuleActor.h"

// Called when the game starts or when spawned
void AMyFirstModuleActor::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("Hello from MyFirstModule"));
}

