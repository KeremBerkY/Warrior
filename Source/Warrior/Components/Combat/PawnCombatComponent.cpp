// Vince Petrelli All Rights Reserved


#include "PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Warrior/WarriorDebugHelper.h"
#include "Warrior/Items/Weapons/WarriorWeaponBase.h"


UPawnCombatComponent::UPawnCombatComponent()
{ 
	PrimaryComponentTick.bCanEverTick = true;
}

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterEquippedWeapon)
{
	Debug::Print(InWeaponTagToRegister.ToString());
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString())
	check(InWeaponToRegister);
	
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		check(WeaponToToggle);
		
		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Enabled"), FColor::Green);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Debug::Print(WeaponToToggle->GetName() + TEXT("Collision Disabled"), FColor::Red);
		}

	}
}

