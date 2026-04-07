// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyTestDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTTEST_API UMyTestDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Settings")
    int32 MaxPlayers = 4;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Settings")
    float RoundTime = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Settings")
    float PlayerWalkSpeed = 600.f;
};
