// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WarriorAbilitySystemComponent.h"
#include "WarriorAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UWarriorAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)
	
	UPROPERTY(BlueprintReadOnly, Category = "Defense")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefensePower)
};