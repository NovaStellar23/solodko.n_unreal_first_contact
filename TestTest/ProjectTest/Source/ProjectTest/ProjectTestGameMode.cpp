// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectTestGameMode.h"
#include "ProjectTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyTestDataAsset.h"

AProjectTestGameMode::AProjectTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void AProjectTestGameMode::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("GAME MODE STARTED"));

    if (GameModeConfig)
    {
        UE_LOG(LogTemp, Warning, TEXT("MaxPlayers: %d"), GameModeConfig->MaxPlayers);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameModeConfig is NULL"));
    }
}
void AProjectTestGameMode::SwitchConfig(int32 Index)
{
    if (!AvailableConfigs.IsValidIndex(Index)) return;

    GameModeConfig = AvailableConfigs[Index];

    UE_LOG(LogTemp, Warning, TEXT("Switched Config -> MaxPlayers: %d"), GameModeConfig->MaxPlayers);
}