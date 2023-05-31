// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"

// Sets default values
AMyFirstActor::AMyFirstActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();
	SetRandomRotationSpeed();
}

void AMyFirstActor::SetRandomRotationSpeed()
{
	CurrentRotationSpeed = FMath::RandRange(MinimumRotationSpeed, MaximumRotationSpeed);
	GEngine->AddOnScreenDebugMessage(0, 5, TextColor, FString::Printf(TEXT("Initial rotation speed %f"), CurrentRotationSpeed));

}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotator = GetActorRotation();
	Rotator.Yaw += CurrentRotationSpeed * DeltaTime;
	SetActorRotation(Rotator);
}

