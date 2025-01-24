// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Warrior/AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorMontageEventAbility.generated.h"

class UWarriorAbilityTask_PlayMontageAndWaitForEvent;
class AWarriorBaseCharacter;

/**
 * TODO: Daha Sonra DataAssetten MontageAbilityleri alacaksın UPROPERTY() boş kalacak ve Değişkene DataAssetten montage atacaksın!
 */
UCLASS()
class WARRIOR_API UWarriorMontageEventAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

protected:
	UWarriorMontageEventAbility();

	UPROPERTY()
	float MontageRate = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Warrior Ability|Montage")
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Warrior Ability")
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditAnywhere, Category="Warrior Ability")
	TSubclassOf<UGameplayEffect> BlockDamageEffect;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION()
	virtual void OnCancelled(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION()
	virtual void StartAnimMontage();
	
	UFUNCTION()
	virtual void StopAnimMontage();

	UFUNCTION()
	virtual void BlockAbilities(bool IsEnableBlockAbilities);

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer BlockTagList;

	UPROPERTY(BlueprintReadOnly)
	AWarriorBaseCharacter* CharacterRef;

	UPROPERTY()
	UWarriorAbilityTask_PlayMontageAndWaitForEvent* Task;
};
