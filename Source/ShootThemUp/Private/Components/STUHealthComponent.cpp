// Shoot Them Up Game. All RIghts Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);
	// ...
	
	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner) {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}



void USTUHealthComponent::OnTakeAnyDamage(
	AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser ) {
	
	if (Damage <= 0.0f || isDead()) {
        return;
	}
	Health = FMath::Clamp(Health - Damage,0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
	if (isDead()) {
        OnDeath.Broadcast();
	}
}