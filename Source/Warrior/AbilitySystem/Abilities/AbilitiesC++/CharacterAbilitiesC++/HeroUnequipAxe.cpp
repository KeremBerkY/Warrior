// Vince Petrelli All Rights Reserved


#include "HeroUnequipAxe.h"

#include "EnhancedInputSubsystems.h"
#include "Warrior/WarriorDebugHelper.h"
#include "Warrior/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Warrior/Characters/WarriorHeroCharacter.h"
#include "Warrior/Components/Combat/HeroCombatComponent.h"
#include "Warrior/Controllers/WarriorHeroController.h"
#include "Warrior/Items/Weapons/WarriorHeroWeapon.h"
#include "Warrior/Items/Weapons/WarriorWeaponBase.h"

UHeroUnequipAxe::UHeroUnequipAxe()
{
	const auto AbilityTag = FGameplayTag::RequestGameplayTag("Player.Ability.UnEquip.Axe");
	
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);
}

void UHeroUnequipAxe::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CharacterRef)
	{
		BlockAbilities(true);
		StartAnimMontage();	
		if (const auto HeroCharacter = Cast<AWarriorHeroCharacter>(CharacterRef))
		{
			HeroCharacter->GetHeroCombatComponent()->CurrentEquippedWeaponTag = FGameplayTag();
		}
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	}
}

void UHeroUnequipAxe::OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnEventReceived(EventTag, Payload);

	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Player.Event.UnEquip.Axe")))
	{
		if (const auto HeroCharacter = Cast<AWarriorHeroCharacter>(CharacterRef))
		{
			if (const auto WeaponActor = HeroCharacter->GetHeroCombatComponent()->GetCharacterCarriedWeaponByTag(FGameplayTag::RequestGameplayTag("Player.Weapon.Axe")))
			{
				const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
				WeaponActor->AttachToComponent(CharacterRef->GetMesh(), AttachRules, SocketNameToAttachTo);

				if (const auto HeroWeapon = Cast<AWarriorHeroWeapon>(WeaponActor))
				{
					const auto WeaponClass = HeroWeapon->HeroWeaponData.WeaponAnimLayerToLink;
					LinkAnimationLayerOnBlueprint(HeroCharacter->GetMesh(), WeaponClass);
					
					HandleEquipWeapon(HeroWeapon);

					auto AbilityToRemove = HeroWeapon->GetGrantedAbilitySpecHandles();
					GetWarriorAbilitySystemComponentFromActorInfo()->RemoveGrantHeroWeaponAbilities(AbilityToRemove);
				}
			}
		}
	}
}

void UHeroUnequipAxe::HandleEquipWeapon(const AWarriorHeroWeapon* InWeaponToUnEquip) const
{
	const auto HeroWeaponData = InWeaponToUnEquip->HeroWeaponData;

	if (const auto WarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController))
	{
		if (const auto EnhancedInputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(WarriorHeroController->GetLocalPlayer()))
		{
			EnhancedInputSubSystem->RemoveMappingContext(HeroWeaponData.WeaponInputMappingContext);
		}
	}
}

void UHeroUnequipAxe::OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnCompleted(EventTag, Payload);
}

void UHeroUnequipAxe::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

