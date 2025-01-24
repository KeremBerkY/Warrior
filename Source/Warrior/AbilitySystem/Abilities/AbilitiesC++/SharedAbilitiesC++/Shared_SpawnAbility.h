// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Warrior/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "Shared_SpawnAbility.generated.h"

class AWarriorWeaponBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UShared_SpawnAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWarriorWeaponBase> WeaponClassToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketNameToAttachTo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FGameplayTag WeaponTagToRegister;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	bool RegisterAsEquippedWeapon;
	
};
