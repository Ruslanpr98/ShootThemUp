// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUHealthPickUp.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);

bool ASTUHealthPickUp::GivePickUpTo(APawn *PlayerPawn) {
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);

    if (!HealthComponent || HealthComponent->isDead()) {
        return false;
    }


    return HealthComponent->TryToAddHealth(HealthAmount);
}
