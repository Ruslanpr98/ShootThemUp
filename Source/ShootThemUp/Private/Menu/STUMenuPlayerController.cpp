// Shoot Them Up Game. All RIghts Reserved.


#include "Menu/STUMenuPlayerController.h"

void ASTUMenuPlayerController::BeginPlay() {
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}