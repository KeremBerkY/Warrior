// Vince Petrelli All Rights Reserved


#include "WarriorHeroLinkedAnimLayer.h"

#include "WarriorHeroAnimInstance.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	// GetOwningComponent kontrolü
	USkeletalMeshComponent* OwningComponent = GetOwningComponent();
	if (!OwningComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetOwningComponent() is nullptr in GetHeroAnimInstance"));
		return nullptr;
	}

	// GetAnimInstance kontrolü
	UAnimInstance* AnimInstance = OwningComponent->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetAnimInstance() is nullptr in GetHeroAnimInstance"));
		return nullptr;
	}

	// UWarriorHeroAnimInstance türüne cast etme
	UWarriorHeroAnimInstance* HeroAnimInstance = Cast<UWarriorHeroAnimInstance>(AnimInstance);
	if (!HeroAnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UWarriorHeroAnimInstance in GetHeroAnimInstance"));
	}

	return HeroAnimInstance;
}
