// Vince Petrelli All Rights Reserved


#include "Shared_SpawnAbility.h"

#include "Warrior/Components/Combat/PawnCombatComponent.h"
#include "Warrior/Items/Weapons/WarriorWeaponBase.h"

void UShared_SpawnAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
}

void UShared_SpawnAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (WeaponClassToSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetAvatarActorFromActorInfo();
		SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());

		if (AWarriorWeaponBase* SpawnedActor = GetWorld()->SpawnActor<AWarriorWeaponBase>(WeaponClassToSpawn ,SpawnParams))
		{
			if (ActorInfo && ActorInfo->AvatarActor.IsValid())
			{
				USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
				if (const APawn* Pawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
				{
					SkeletalMeshComponent = Pawn->FindComponentByClass<USkeletalMeshComponent>();
				}

				const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
				
				SpawnedActor->AttachToComponent(SkeletalMeshComponent, AttachRules, SocketNameToAttachTo);
				
				if (WeaponTagToRegister.IsValid())
				{
					GetPawnCombatComponentFromActorInfo()->RegisterSpawnedWeapon(WeaponTagToRegister, SpawnedActor, RegisterAsEquippedWeapon);
				}
			}
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UShared_SpawnAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
