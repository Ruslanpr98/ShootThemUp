// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	float GetHealth() const {
        return Health;
    };

	UFUNCTION(BlueprintCallable)
    float isDead() const {
        return FMath::IsNearlyZero(Health);
    };

	FOnDeath OnDeath;

	FOnHealthChanged OnHealthChanged;

  protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "200.0"))
	float MaxHealth = 100.0f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealthUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealthDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealthRegenRate = 1.0f;


	// Called when the game starts
	virtual void BeginPlay() override;


	private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;

	UFUNCTION()
    void OnTakeAnyDamage(AActor *DamageActor, float Damage, const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);

	void RegenerateHealth();
    void SetHealth(float NewHealth);
		
};
