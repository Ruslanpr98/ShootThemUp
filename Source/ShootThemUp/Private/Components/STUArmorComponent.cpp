// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUArmorComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogArmorComponent, All, All)

USTUArmorComponent::USTUArmorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUArmorComponent::BeginPlay()
{
    Super::BeginPlay();
    
    check(MaxArmor > 0);
    SetArmor(MaxArmor);
}

void USTUArmorComponent::SetArmor(float NewArmor)
{
    const auto NextArmor = FMath::Clamp(NewArmor, 0.0f, MaxArmor);
    const auto ArmorDelta = NextArmor - Armor;
    
    Armor = NextArmor;
    OnArmorChanged.Broadcast(Armor, ArmorDelta);
    
    UE_LOG(LogArmorComponent, Display, TEXT("Armor changed: %f (Delta: %f)"), Armor, ArmorDelta);
}

float USTUArmorComponent::ProcessDamage(float IncomingDamage)
{
    if (IncomingDamage <= 0.0f || IsArmorEmpty())
    {
        return IncomingDamage; // No armor to absorb damage
    }
    
    const float AbsorbedDamage = FMath::Min(IncomingDamage * ArmorAbsorption, Armor);
    const float RemainingDamage = IncomingDamage - AbsorbedDamage;
    
    SetArmor(Armor - AbsorbedDamage);
    
    UE_LOG(LogArmorComponent, Display, TEXT("Armor absorbed %f damage, remaining damage: %f"), AbsorbedDamage, RemainingDamage);
    
    // Start regeneration if enabled and armor is not full
    if (AutoRegen && !IsArmorFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(ArmorRegenTimerHandle, this, &USTUArmorComponent::RegenerateArmor,
                                               ArmorRegenInterval, true, ArmorRegenDelay);
    }
    
    return RemainingDamage;
}

bool USTUArmorComponent::TryToAddArmor(int32 ArmorAmount)
{
    if (IsArmorFull() || ArmorAmount <= 0)
    {
        return false;
    }
    
    SetArmor(Armor + ArmorAmount);
    return true;
}

void USTUArmorComponent::RegenerateArmor()
{
    if (IsArmorFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(ArmorRegenTimerHandle);
        return;
    }
    
    SetArmor(Armor + ArmorRegenRate);
}