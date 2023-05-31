// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstActor.generated.h"

UENUM(BlueprintType)
enum class EMyNewEnum : uint8
{
	Value1 UMETA(DisplayName = "First value of the new enum"),
	Value2 UMETA(DisplayName = "Second value of the new enum")
};

USTRUCT(BlueprintType)
struct FMyNewStruct
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		int32 IntegerValue = 100;

	UPROPERTY(EditAnywhere)
		EMyNewEnum EnumValue = EMyNewEnum::Value1;
};

UCLASS()
class INTRO_API AMyFirstActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyFirstActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void SetRandomRotationSpeed();

	UPROPERTY(EditAnywhere)
		FMyNewStruct StructProperty;

	UPROPERTY(EditAnywhere)
		AActor* AnotherActor;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Misc properties", meta = (ClampMin = 0, UIMin = 0, ClampMax = 100, UIMax = 100))
		int MyFirstProperty = 100;

	UPROPERTY(EditAnywhere)
		float MinimumRotationSpeed = 30.0f;

	UPROPERTY(EditAnywhere)
		float MaximumRotationSpeed = 360.0f;

	UPROPERTY(EditAnywhere)
		FColor TextColor = FColor::Red;

	UPROPERTY(EditAnywhere)
		TArray<float> NewVector;

	UPROPERTY(EditAnywhere)
		TMap<int, float> NewMap;

	UPROPERTY(EditAnywhere)
		TSet<int> NewSet;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float CurrentRotationSpeed = 0.0f;

};
