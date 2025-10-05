// Shoot Them Up Game. All Rights Reserved.

#include "PickUps/STUArmorPickUp.h"
#include "Components/STUArmorComponent.h"

bool ASTUArmorPickUp::GivePickUpTo(APawn* PlayerPawn)
{
    const auto ArmorComponent = PlayerPawn->FindComponentByClass<USTUArmorComponent>();
    if (!ArmorComponent) return false;

    return ArmorComponent->TryToAddArmor(ArmorAmount);
}