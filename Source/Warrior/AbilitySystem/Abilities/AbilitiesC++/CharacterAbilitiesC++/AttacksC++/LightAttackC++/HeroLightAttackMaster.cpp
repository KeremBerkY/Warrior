// Vince Petrelli All Rights Reserved


#include "HeroLightAttackMaster.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Warrior/WarriorFunctionLibrary.h"
#include "Warrior/AbilitySystem/Abilities/AbilitiesC++/WarriorAbilityTask_PlayMontageAndWaitForEvent.h"
#include "Warrior/Characters/WarriorHeroCharacter.h"

UHeroLightAttackMaster::UHeroLightAttackMaster()
{
	const auto AbilityTag = FGameplayTag::RequestGameplayTag(FName("Player.Ability.Attack.Light"));
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);

	CurrentLightAttackComboCount = 1;
	bIsComboTimerActive = false;

	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UHeroLightAttackMaster::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (CharacterRef)
	{
		ClearComboResetTimer();
		
		HandleComboAndSetMontage();
		StartAnimMontage();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UHeroLightAttackMaster::HandleComboAndSetMontage()
{
	if (AttackMontagesMap.Contains(CurrentLightAttackComboCount))
	{
		if (UAnimMontage* SelectedMontage = AttackMontagesMap[CurrentLightAttackComboCount])
		{
			AbilityMontage = SelectedMontage;
		}
	}

	if (CurrentLightAttackComboCount == AttackMontagesMap.Num())
	{
		ResetAttackComboCount();
	}
	else
	{
		if (CurrentLightAttackComboCount == AttackMontagesMap.Num() - 1)
		{
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(GetHeroCharacterFromWarriorGameplayAbility(), FGameplayTag::RequestGameplayTag(FName("Player.Status.JumpToFinisher")));
		}
		CurrentLightAttackComboCount++;
	}
}

void UHeroLightAttackMaster::ResetAttackComboCount()
{
	CurrentLightAttackComboCount = 1;

	UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(GetHeroCharacterFromWarriorGameplayAbility(), FGameplayTag::RequestGameplayTag(FName("Player.Status.JumpToFinisher")));
}

void UHeroLightAttackMaster::SetComboResetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		ComboCountResetTimerHandle,
		this,
		&UHeroLightAttackMaster::ResetAttackComboCount,
		0.3f,
		false
	);
	
}

void UHeroLightAttackMaster::ClearComboResetTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ComboCountResetTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ComboCountResetTimerHandle);
	}
}

void UHeroLightAttackMaster::OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnEventReceived(EventTag, Payload);

	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Player.Event.OnComplete")))
	{
		OnCompleted(EventTag, Payload);
	}
	
}

void UHeroLightAttackMaster::OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnCompleted(EventTag, Payload);
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHeroLightAttackMaster::OnCancelled(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnCancelled(EventTag, Payload);
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHeroLightAttackMaster::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	SetComboResetTimer();
}


