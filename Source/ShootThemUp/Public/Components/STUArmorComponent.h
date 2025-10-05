// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUArmorComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArmorChanged, float, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUArmorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USTUArmorComponent();

    // Armor getters
    float GetArmor() const { return Armor; }
    float GetMaxArmor() const { return MaxArmor; }
    float GetArmorPercent() const { return MaxArmor > 0.0f ? Armor / MaxArmor : 0.0f; }
    
    UFUNCTION(BlueprintCallable, Category = "Armor")
    bool IsArmorEmpty() const { return FMath::IsNearlyZero(Armor); }
    
    UFUNCTION(BlueprintCallable, Category = "Armor")
    bool IsArmorFull() const { return FMath::IsNearlyEqual(Armor, MaxArmor); }

    // Armor management
    bool TryToAddArmor(int32 ArmorAmount);
    float ProcessDamage(float IncomingDamage);
    
    // Events
    FOnArmorChanged OnArmorChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (ClampMin = "0.0", ClampMax = "200.0"))
    float MaxArmor = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
    float ArmorAbsorption = 0.5f; // How much damage armor absorbs (0.5 = 50%)

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
    bool AutoRegen = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (EditCondition = "AutoRegen"))
    float ArmorRegenRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (EditCondition = "AutoRegen"))
    float ArmorRegenDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (EditCondition = "AutoRegen"))
    float ArmorRegenInterval = 1.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Armor = 0.0f;
    FTimerHandle ArmorRegenTimerHandle;

    void SetArmor(float NewArmor);
    void RegenerateArmor();
};