// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUAmmoPickUp.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);




bool ASTUAmmoPickUp::GivePickUpTo(APawn *PlayerPawn) {

    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);

    if (!HealthComponent || HealthComponent->isDead()) {
        return false;
    }

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) {
        return false;
    }

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
