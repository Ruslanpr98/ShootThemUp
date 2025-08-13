// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32 &CountDownTime) const {
    const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());

    if(!RespawnComponent || !RespawnComponent->isRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCountdown();

    return true;
}