// Vince Petrelli All Rights Reserved


#include "WarriorHeroWeapon.h"


AWarriorHeroWeapon::AWarriorHeroWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWarriorHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

