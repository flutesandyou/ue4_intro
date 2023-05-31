// Copyright Epic Games, Inc. All Rights Reserved.

#include "IntroGameMode.h"
#include "IntroCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIntroGameMode::AIntroGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Core/Characters/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
