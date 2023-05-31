// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "GeneratorActor.generated.h"

//DECLARE_DELEGATE_OneParam(FOnGeneratorSwitchedSignature, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGeneratorSwitchedSignature, bool);

UENUM(BlueprintType)
enum class EGeneratorType : uint8
{
	Basic = 0,
	Advanced,
	Ultra
};

USTRUCT(BlueprintType)
struct FGeneratorSettingsRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CooldownTime = 5.0f;

};


UCLASS()
class INTRO_API AGeneratorActor : public AActor
{
	GENERATED_BODY()

public:
	FOnGeneratorSwitchedSignature OnGeneratorSwitched;

protected:
	UFUNCTION(BlueprintCallable)
	void SwitchGenerator();

	UFUNCTION(BlueprintCallable)
	float GetCooldownFromRate(float InRotationRate) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator settings")
	EGeneratorType GeneratorType = EGeneratorType::Basic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator settings")
	class UGeneratorPropsDataAsset* PropSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator settings")
	UCurveFloat* CooldownCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generator state")
	bool bIsOn = true;

};
