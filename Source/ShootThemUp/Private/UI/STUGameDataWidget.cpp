// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUGameDataWidget.h"

#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRoundsNum() const {
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetCurrentRoundsNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const {
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const {
    const auto GameMode = GetSTUGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const {
    return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const {
    return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}