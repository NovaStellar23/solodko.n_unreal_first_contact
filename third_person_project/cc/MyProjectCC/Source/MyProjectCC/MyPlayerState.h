// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "MyPlayerState.generated.h"

class UAbilitySystemComponent;
class UVitalAttributeSet;
class UDamageAttributeSet;

UCLASS()
class MYPROJECTCC_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AMyPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	//UPROPERTY()
	//UVitalAttributeSet* VitalAttributes;
	//UPROPERTY()
	//UDamageAttributeSet* DamageAttributes;
	
};
