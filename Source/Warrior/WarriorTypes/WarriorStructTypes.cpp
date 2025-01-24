// Vince Petrelli All Rights Reserved


#include "WarriorStructTypes.h"

#include "Warrior/AbilitySystem/Abilities/WarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;;
}
