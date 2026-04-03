// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAttributeSet.h"

UMyAttributeSet::UMyAttributeSet()
{
    Health.SetBaseValue(100.f);
    Health.SetCurrentValue(100.f);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        float NewHealth = FMath::Clamp(Health.GetCurrentValue(), 0.0f, 100.0f);
        Health.SetCurrentValue(NewHealth);
    }
}
float UMyAttributeSet::GetHealth() const
{
    return Health.GetCurrentValue();
}