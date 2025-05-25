// Shoot Them Up Game. All RIghts Reserved.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    ProjectileMovementComponent->InitialSpeed = 2000.0f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");

}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(ProjectileMovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

	ProjectileMovementComponent->Velocity = ShotDirection * ProjectileMovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);

	SetLifeSpan(LifeSpan);
	
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) {
    if (!GetWorld())
        return;

    ProjectileMovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius,
                                        UDamageType::StaticClass(), {}, this, GetController(), DoFullDamage);

    
    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);

    WeaponFXComponent->PlayImpactFX(Hit);
    
    Destroy();
}

AController *ASTUProjectile::GetController() const {
    const auto Pawn = Cast<APawn>(GetOwner());

    return Pawn ? Pawn->GetController() : nullptr;
}

