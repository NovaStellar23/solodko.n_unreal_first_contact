// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectCCGameMode.h"
#include "MyProjectCCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectCCGameMode::AMyProjectCCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
