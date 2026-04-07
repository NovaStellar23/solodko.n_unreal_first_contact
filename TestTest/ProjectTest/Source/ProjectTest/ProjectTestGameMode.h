// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyTestDataAsset.h"
#include "ProjectTestGameMode.generated.h"


UCLASS(minimalapi)
class AProjectTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectTestGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UMyTestDataAsset* GameModeConfig;

	UPROPERTY(EditAnywhere, Category = "Config")
	TArray<UMyTestDataAsset*> AvailableConfigs;

	UFUNCTION(BlueprintCallable)
	void SwitchConfig(int32 Index);
};



