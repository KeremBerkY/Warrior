// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "WarriorEventTagAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorEventTagAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

	UWarriorEventTagAnimNotify();
public:

	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
