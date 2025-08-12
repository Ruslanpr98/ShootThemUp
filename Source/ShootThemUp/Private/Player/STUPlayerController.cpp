// Shoot Them Up Game. All RIghts Reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController() {
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}