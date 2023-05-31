// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorActor.h"


void AGeneratorActor::SwitchGenerator()
{
	bIsOn = !bIsOn;

	if (OnGeneratorSwitched.IsBound())
	{
		OnGeneratorSwitched.Broadcast(bIsOn);
	}

}

float AGeneratorActor::GetCooldownFromRate(float InRotationRate) const
{
	float Result = 0.0f;
	if (IsValid(CooldownCurve))
	{
		Result = CooldownCurve->GetFloatValue(InRotationRate);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("AGeneratorActor::GetCooldownFromRate. Rate: %f, Cooldown: %f"), InRotationRate, Result));
	}
	return Result;
}
