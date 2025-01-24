// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Warrior/AbilitySystem/Abilities/AbilitiesC++/WarriorMontageEventAbility.h"
#include "HeroHeavyAttackMaster.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroHeavyAttackMaster : public UWarriorMontageEventAbility
{
	GENERATED_BODY()

protected:
	UHeroHeavyAttackMaster();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Montages")
	TMap<int32, UAnimMontage*> AttackMontagesMap;

private:
	void HandleComboAndSetMontage();
	void ResetAttackComboCount();
	void SetComboResetTimer();
	void ClearComboResetTimer();
	
	FTimerHandle ComboCountResetTimerHandle;

	int32 CurrentHeavyAttackComboCount;

	bool bIsComboTimerActive;

};
