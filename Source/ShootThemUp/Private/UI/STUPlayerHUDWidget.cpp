// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUTils.h"

bool USTUPlayerHUDWidget::Initialize() {


    if(GetOwningPlayer()) {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    return Super::Initialize();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta) {
    if (HealthDelta < 0.0f) {
        OnTakeDamage();
    }

}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn) {
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);

    if (HealthComponent) {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
}


float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    if (!HealthComponent) {
        return 0.0f;
    }

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData &UIData) const {
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) {
        return false;
    }

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData &AmmoData) const {
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) {
        return false;
    }

    return WeaponComponent->GetAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());

    return HealthComponent && !HealthComponent->isDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {

    const auto Controller = GetOwningPlayer();

    return Controller && Controller->GetStateName() == NAME_Spectating;
}



