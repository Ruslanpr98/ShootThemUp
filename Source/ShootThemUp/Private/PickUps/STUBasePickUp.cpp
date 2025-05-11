// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUBasePickUp.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp, All, All); 

// Sets default values
ASTUBasePickUp::ASTUBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);

}

void ASTUBasePickUp::BeginPlay()
{
	Super::BeginPlay();
    check(CollisionComponent);

}



void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASTUBasePickUp::GivePickUpTo(APawn *PlayerPawn) {
    return PlayerPawn != nullptr;
}


void ASTUBasePickUp::NotifyActorBeginOverlap(AActor *OtherActor) {
	
	Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickUpTo(Pawn)) {
        PickUpWasTaken();
    }

	
}

void ASTUBasePickUp::PickUpWasTaken() {
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    FTimerHandle RespawnTimerHandle;

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickUp::Respawn, RespawnTime);
}

void ASTUBasePickUp::Respawn() {
    
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

}
