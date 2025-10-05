// Shoot Them Up Game. All RIghts Reserved.


#include "Player/STUBaseCharacter.h"

#include "STUPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUArmorComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SOund/SoundCue.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUWeaponComponent.h"
#include "GameFramework/Controller.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjInit) 
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)) {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    ArmorComponent = CreateDefaultSubobject<USTUArmorComponent>("ArmorComponent");

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
   
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(HealthComponent); //Special Macros for checking if Component is valid (Works only in Dev Mode. Ignored in Shipment)
    check(ArmorComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASTUBaseCharacter::isCharSprinting() const {
    return false;
}

float ASTUBaseCharacter::GetMovementDirection() const {
    if (GetVelocity().IsZero()) {
        return 0.0f;
    }
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor &Color) {
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst) return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}


void ASTUBaseCharacter::OnDeath() {
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is Dead"), *GetName());

    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASTUBaseCharacter::OnHealthChanged(float Health, float HealthDelta) {
    
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult &Hit) {
    const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
    UE_LOG(LogBaseCharacter, Display, TEXT("On Landed %f"), FallVelocityZ);

    if (FallVelocityZ < LandedDamageVelocity.X) {
        return;
    }

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(LogBaseCharacter, Display, TEXT("FinalDamage %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent(), nullptr, nullptr);
}