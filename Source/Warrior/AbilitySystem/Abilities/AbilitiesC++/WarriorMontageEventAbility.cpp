// Vince Petrelli All Rights Reserved


#include "WarriorMontageEventAbility.h"

#include "WarriorAbilityTask_PlayMontageAndWaitForEvent.h"
#include "Warrior/Characters/WarriorHeroCharacter.h"

UWarriorMontageEventAbility::UWarriorMontageEventAbility()
{
}

void UWarriorMontageEventAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	CharacterRef = Cast<AWarriorHeroCharacter>(ActorInfo->AvatarActor);
}

void UWarriorMontageEventAbility::OnCancelled(FGameplayTag EventTag, FGameplayEventData Payload)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UWarriorMontageEventAbility::OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	//Warning no need endAbility; Every class needs endability itselfs.
}

void UWarriorMontageEventAbility::OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	//Warning no need endAbility; Every class needs endability itselfs.
}

void UWarriorMontageEventAbility::StartAnimMontage()
{
	/** PLay montage and wait for the montage event to spawn overlap check actor for a valid interaction */
	Task = UWarriorAbilityTask_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this,
		NAME_None,
		AbilityMontage,
		FGameplayTagContainer(),
		MontageRate,
		NAME_None,
		false,
		1);

	//Task->OnBlendOut.AddDynamic(this, &ThisClass::OnCompleted);
	Task->OnCompleted.AddDynamic(this, &ThisClass::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &ThisClass::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &ThisClass::OnCancelled);
	Task->EventReceived.AddDynamic(this, &ThisClass::OnEventReceived);
	
	Task->ReadyForActivation();	
}

void UWarriorMontageEventAbility::StopAnimMontage()
{
	if(IsValid(Task))
	{
		Task->EndTask();
		CharacterRef->GetMesh()->GetAnimInstance()->Montage_Stop(0.25, AbilityMontage);
		Task->OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
	}
}

void UWarriorMontageEventAbility::BlockAbilities(bool IsEnableBlockAbilities)
{
	FGameplayTagContainer Temp;
	CharacterRef->GetAbilitySystemComponent()->ApplyAbilityBlockAndCancelTags(
		Temp, this, IsEnableBlockAbilities, BlockTagList, false, Temp);
}
