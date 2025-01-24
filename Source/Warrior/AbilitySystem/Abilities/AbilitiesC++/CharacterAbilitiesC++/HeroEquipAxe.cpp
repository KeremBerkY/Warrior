// Vince Petrelli All Rights Reserved


#include "HeroEquipAxe.h"

#include "EnhancedInputSubsystems.h"
#include "Warrior/WarriorDebugHelper.h"
#include "Warrior/AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Warrior/AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Warrior/Characters/WarriorBaseCharacter.h"
#include "Warrior/Characters/WarriorHeroCharacter.h"
#include "Warrior/Components/Combat/HeroCombatComponent.h"
#include "Warrior/Controllers/WarriorHeroController.h"
#include "Warrior/Items/Weapons/WarriorHeroWeapon.h"
#include "Warrior/Items/Weapons/WarriorWeaponBase.h"
#include "Warrior/WarriorTypes/WarriorStructTypes.h"

UHeroEquipAxe::UHeroEquipAxe()
{
	const auto AbilityTag = FGameplayTag::RequestGameplayTag("Player.Ability.Equip.Axe");
	
	AbilityTags.AddTag(AbilityTag);
	ActivationOwnedTags.AddTag(AbilityTag);
}

void UHeroEquipAxe::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (CharacterRef)
	{
		BlockAbilities(true);
		StartAnimMontage();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);

	}
}

void UHeroEquipAxe::OnEventReceived(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnEventReceived(EventTag, Payload);

	if (EventTag == FGameplayTag::RequestGameplayTag(FName("Player.Event.Equip.Axe")))
	{
		if (const auto HeroCharacter = Cast<AWarriorHeroCharacter>(CharacterRef))
		{
			if (const auto WeaponActor = HeroCharacter->GetHeroCombatComponent()->GetCharacterCarriedWeaponByTag(FGameplayTag::RequestGameplayTag("Player.Weapon.Axe")))
			{
				const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, true);
				WeaponActor->AttachToComponent(CharacterRef->GetMesh(), AttachRules, SocketNameToAttachTo);

				// HeroCharacter->GetHeroCombatComponent()->CurrentEquippedWeaponTag = FGameplayTag::RequestGameplayTag("Player.Weapon.Axe");

				if (const auto HeroWeapon = Cast<AWarriorHeroWeapon>(WeaponActor))
				{
					const auto WeaponClass = HeroWeapon->HeroWeaponData.WeaponAnimLayerToLink;
					LinkAnimationLayerOnBlueprint(HeroCharacter->GetMesh(), WeaponClass);

					HandleEquipWeapon(HeroWeapon);
					
					HeroCharacter->GetHeroCombatComponent()->CurrentEquippedWeaponTag = FGameplayTag::RequestGameplayTag(FName("Player.Weapon.Axe"));
				}

			}
		}
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UHeroEquipAxe::HandleEquipWeapon(AWarriorHeroWeapon* InWeaponToEquip) const
{
	const auto HeroWeaponData = InWeaponToEquip->HeroWeaponData;
	
	if (const auto WarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController))
	{
		if (const auto EnhancedInputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(WarriorHeroController->GetLocalPlayer()))
		{
			EnhancedInputSubSystem->AddMappingContext(HeroWeaponData.WeaponInputMappingContext, 1);
		}
	}

	TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;

	GetWarriorAbilitySystemComponentFromActorInfo()->GrantHeroWeaponAbilities(HeroWeaponData.DefaultWeaponAbilities, GetAbilityLevel(), GrantedAbilityHandles);

	InWeaponToEquip->AssignGrantedAbilitySpecHandles(GrantedAbilityHandles);
}


void UHeroEquipAxe::OnCompleted(FGameplayTag EventTag, FGameplayEventData Payload)
{
	Super::OnCompleted(EventTag, Payload);
}

void UHeroEquipAxe::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	BlockAbilities(false);
}

