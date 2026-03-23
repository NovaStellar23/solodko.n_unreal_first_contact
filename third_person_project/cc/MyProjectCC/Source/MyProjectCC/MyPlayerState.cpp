// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "AbilitySystemComponent.h"
//#include "VitalAttributeSet.h"
//#include "DamageAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	//VitalAttributes = CreateDefaultSubobject<UVitalAttributeSet>("VitalAttributes");
	//DamageAttributes = CreateDefaultSubobject<UDamageAttributeSet>("DamageAttributes");
}
UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

