// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class UProgressBar;


UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData &UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetAmmoData(FAmmoData &AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsCount() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(int32 BulletsNum) const;

  private:
    void OnHealthChanged(float Health, float HealthDelta);

    void OnNewPawn(APawn* NewPawn);

    void UpdateHealthBar();

protected:

    UPROPERTY(meta=(BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor SafeColor = FLinearColor::Green;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor DangerColor = FLinearColor::Red;

    
    virtual void NativeOnInitialized() override;
    
};