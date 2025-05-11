// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUHealthPickUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);

bool ASTUHealthPickUp::GivePickUpTo(APawn *PlayerPawn) {
    UE_LOG(LogHealthPickUp, Display, TEXT("Health was taken"))

    return true;
}
