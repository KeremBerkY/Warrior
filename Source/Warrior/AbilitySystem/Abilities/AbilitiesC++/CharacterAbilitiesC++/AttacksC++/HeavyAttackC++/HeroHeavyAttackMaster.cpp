// Vince Petrelli All Rights Reserved


#include "HeroHeavyAttackMaster.h"

#include "Warrior/WarriorFunctionLibrary.h"

UHeroHeavyAttackMaster::UHeroHeavyAttackMaster()
{
	const auto AbilityTag = FGameplayTag::RequestGameplayTag(FName("Player.Ability.Attack.Heavy"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	CurrentHeavyAttackComboCount = 1;
	bIsComboTimerActive = false;

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UHeroHeavyAttackMaster::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CharacterRef)
	{
		ClearComboResetTimer();
		
		if (UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromWarriorGameplayAbility(), FGameplayTag::RequestGameplayTag(FName("Player.Status.JumpToFinisher"))))
		{
			CurrentHeavyAttackComboCount = AttackMontagesMap.Num();
		}

		HandleComboAndSetMontage();
		StartAnimMontage();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}


void UHeroHeavyAttackMaster::HandleComboAndSetMontage()
{
	
	if (AttackMontagesMap.Contains(CurrentHeavyAttackComboCount))
	{
		if (UAnimMontage* SelectedMontage = AttackMontagesMap[CurrentHeavyAttackComboCount])
		{
			AbilityMontage = SelectedMontage;
		}
	}
	
	
	if (CurrentHeavyAttackComboCount == AttackMontagesMap.Num())
	{
		ResetAttackComboCount();
	}
	else
	{
		if (CurrentHeavyAttackComboCount == AttackMontagesMap.Num() - 1)
		{
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(GetHeroCharacterFromWarriorGameplayAbility(), FGameplayTag::RequestGameplayTag(FName("Player.Status.JumpToFinisher")));
		}
		CurrentHeavyAttackComboCount++;
	}
}

void UHeroHeavyAttackMaster::ResetAttackComboCount()
{
	CurrentHeavyAttackComboCount = 1;
	UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(GetHeroCharacterFromWarriorGameplayAbility(), FGameplayTag::RequestGameplayTag(FName("Player.Status.JumpToFinisher")));
}

void UHeroHeavyAttackMaster::SetComboResetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
	ComboCountResetTimerHandle,
	this,
	&UHeroHeavyAttackMaster::ResetAttackComboCount,
	0.3f,
	false
	);

}

void UHeroHeavyAttackMaster::ClearComboResetTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ComboCountResetTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboCountResetTimerHandle);
	}
}


void UHeroHeavyAttackMaster::OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnEventReceived(EventTag, Payload);

	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Player.Event.OnComplete")))
	{
		OnCompleted(EventTag, Payload);
	}
}

void UHeroHeavyAttackMaster::OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnCompleted(EventTag, Payload);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHeroHeavyAttackMaster::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	SetComboResetTimer();
}
