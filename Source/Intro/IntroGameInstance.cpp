// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroGameInstance.h"

const FColor& UIntroGameInstance::GetPlayerColor()
{
    // TODO: insert return statement here
    while (PlayerColor == FColor::Black)
    {
        PlayerColor = FColor::MakeRandomColor();
    }
    return PlayerColor;
}
