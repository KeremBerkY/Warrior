// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Warrior/AbilitySystem/Abilities/AbilitiesC++/WarriorMontageEventAbility.h"
#include "Warrior/AnimInstances/Hero/WarriorHeroLinkedAnimLayer.h"
#include "Warrior/Characters/WarriorHeroCharacter.h"
#include "Warrior/WarriorTypes/WarriorStructTypes.h"
#include "HeroUnequipAxe.generated.h"

class AWarriorHeroWeapon;
/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroUnequipAxe : public UWarriorMontageEventAbility
{
	GENERATED_BODY()

protected:
	UHeroUnequipAxe();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
	void LinkAnimationLayerOnBlueprint(USkeletalMeshComponent* GetMesh, TSubclassOf<UWarriorHeroLinkedAnimLayer> Class);
	
	void HandleEquipWeapon(const AWarriorHeroWeapon* InWeaponToUnEquip) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketNameToAttachTo;
};
