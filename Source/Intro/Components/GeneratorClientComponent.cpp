// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneratorClientComponent.h"
#include "GeneratorActor.h"

void UGeneratorClientComponent::OnGeneratorSwitched(bool bIsOn)
{

	FString OnOffString = bIsOn ? TEXT("ON") : TEXT("OFF");
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("UGeneratorClientComponent::OnGeneratorSwitched for %s generator is %s"), *GetOwner()->GetName(), *OnOffString));
	if (OnGeneratorClientSwitched.IsBound())
	{
		OnGeneratorClientSwitched.Broadcast(bIsOn);
	}
}

// Called when the game starts
void UGeneratorClientComponent::BeginPlay()
{
	Super::BeginPlay();

	//TODO subscribe on generator events

	if (IsValid(Generator))
	{
		Generator->OnGeneratorSwitched.AddUObject(this, &UGeneratorClientComponent::OnGeneratorSwitched);
	}
}
