// Shoot Them Up Game. All RIghts Reserved.


#include "Components/STUHealthComponent.h"

#include "HeadMountedDisplayTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "STUGameModeBase.h"
#include "Camera/CameraShakeBase.h"


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

	check(MaxHealth > 0);

	SetHealth(MaxHealth);
    //OnHealthChanged.Broadcast(Health, 0.0f);
	// ...
	
	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner) {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}



void USTUHealthComponent::OnTakeAnyDamage(
	AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser ) {
	
	if (Damage <= 0.0f || isDead() || !GetWorld()) {
        return;
	}
    SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (isDead()) {
	    Killed(InstigatedBy);
        OnDeath.Broadcast();
	} 
	else if (AutoHeal && GetWorld()) {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::RegenerateHealth,
                                               HealthUpdateTime, true, HealthDelay);
	}
    PlayCameraShake();
}

void USTUHealthComponent::RegenerateHealth() {
    SetHealth(Health + HealthRegenRate);

	if (isHeathFull() && GetWorld()) {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::SetHealth(float NewHealth) {

	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

	const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}


bool USTUHealthComponent::TryToAddHealth(int32 HealthAmount) {
    if (isDead() || isHeathFull()) {
        return false;
	}

	SetHealth(Health + HealthAmount);

	return true;
}

bool USTUHealthComponent::isHeathFull() const {
    return FMath::IsNearlyEqual(Health, MaxHealth);
}


void USTUHealthComponent::PlayCameraShake() {
    if (isDead()) {
        return;
	}

	const auto Player = Cast<APawn>(GetOwner());

	if (!Player) {
        return;
	}

	const auto Controller = Player->GetController<APlayerController>();

	if (!Controller || !Controller->PlayerCameraManager) {
        return;
	}

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void USTUHealthComponent::Killed(AController *Killer) {
    const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());

    const auto Victim = Player ? Player->Controller : nullptr;

    GameMode->Killed(Killer, Victim);
}