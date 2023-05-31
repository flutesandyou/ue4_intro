// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneratorPropsDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FGeneratorPropVariant
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;
};

enum class EGeneratorType;

UCLASS()
class INTRO_API UGeneratorPropsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EGeneratorType, FGeneratorPropVariant> PropsVariants;

};
