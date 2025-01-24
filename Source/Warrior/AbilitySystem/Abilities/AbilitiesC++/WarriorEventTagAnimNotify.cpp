// Vince Petrelli All Rights Reserved


#include "WarriorEventTagAnimNotify.h"

#include "AbilitySystemBlueprintLibrary.h"


UWarriorEventTagAnimNotify::UWarriorEventTagAnimNotify()
{

#if WITH_EDITORONLY_DATA	
	bShouldFireInEditor = false;
#endif
	
}

void UWarriorEventTagAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (const auto Actor = MeshComp->GetOwner())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, EventTag, FGameplayEventData());
	}
}

FString UWarriorEventTagAnimNotify::GetNotifyName_Implementation() const
{
	return EventTag.GetTagName().ToString();
}
