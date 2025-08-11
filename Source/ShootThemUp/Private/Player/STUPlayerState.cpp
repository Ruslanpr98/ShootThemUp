// Shoot Them Up Game. All RIghts Reserved.


#include "Player/STUPlayerState.h"


DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, Log, All);

void ASTUPlayerState::LogInfo() {
    UE_LOG(LogTemp, Display, TEXT("TeamID: %i, Kills: %i, Deaths:%i,"), TeamID, KillsCount, DeathsCount);
}
