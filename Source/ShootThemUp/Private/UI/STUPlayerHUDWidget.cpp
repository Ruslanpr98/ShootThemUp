// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto HealthComponent = GetHealthComponent();

    if (!HealthComponent) {
        return false;
    }

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const {
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) {
        return false;
    }

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData &AmmoData) const {
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) {
        return false;
    }

    return WeaponComponent->GetAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
    const auto HealthComponent = GetHealthComponent();

    return HealthComponent && !HealthComponent->isDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {

    const auto Controller = GetOwningPlayer();

    return Controller && Controller->GetStateName() == NAME_Spectating;
}

USTUWeaponComponent *USTUPlayerHUDWidget::GetWeaponComponent() const {
    const auto Player = GetOwningPlayerPawn();

    if (!Player) {
        return nullptr;
    }

    const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());

    const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);

    return WeaponComponent;
}

USTUHealthComponent *USTUPlayerHUDWidget::GetHealthComponent() const {
    const auto Player = GetOwningPlayerPawn();

    if (!Player) {
        return nullptr;
    }

    const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());

    const auto HealthComponent = Cast<USTUHealthComponent>(Component);


    return HealthComponent;
}




