// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTURespawnComponent();

    void Respawn(int32 RespawnTime);
    int32 GetRespawnCountdown() const {return RespawnCountdown;}

    bool isRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;

    int32 RespawnCountdown = 0;

    void RespawnTimerUpdate();
};
