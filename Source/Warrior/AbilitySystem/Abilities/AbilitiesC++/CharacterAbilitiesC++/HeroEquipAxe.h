// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Warrior/AbilitySystem/Abilities/AbilitiesC++/WarriorMontageEventAbility.h"
#include "Warrior/WarriorTypes/WarriorStructTypes.h"
#include "HeroEquipAxe.generated.h"

class AWarriorHeroCharacter;
class AWarriorHeroWeapon;
class UWarriorHeroLinkedAnimLayer;
/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroEquipAxe : public UWarriorMontageEventAbility
{
	GENERATED_BODY()

protected:
	UHeroEquipAxe();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Ability")
	void LinkAnimationLayerOnBlueprint(USkeletalMeshComponent* SkeletalMeshComponent, TSubclassOf<UWarriorHeroLinkedAnimLayer> AnimLayerClass);
	
	void HandleEquipWeapon(AWarriorHeroWeapon* InWeaponToEquip) const;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FWarriorHeroWeaponData CachedHeroWeaponData;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SocketNameToAttachTo;
	
};
