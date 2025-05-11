// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUAmmoPickUp.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);

bool ASTUAmmoPickUp::GivePickUpTo(APawn *PlayerPawn) {
    UE_LOG(LogAmmoPickUp, Display, TEXT("Ammo was taken"))
    return true;
}
