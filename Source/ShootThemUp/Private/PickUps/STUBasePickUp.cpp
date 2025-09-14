// Shoot Them Up Game. All RIghts Reserved.


#include "PickUps/STUBasePickUp.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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

    GenerateRotationYaw();
}



void ASTUBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

bool ASTUBasePickUp::CouldBeTaken() const {
    
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
    //return CouldBeTakenTest;
}

bool ASTUBasePickUp::GivePickUpTo(APawn *PlayerPawn) {
    return PlayerPawn != nullptr;
}


void ASTUBasePickUp::NotifyActorBeginOverlap(AActor *OtherActor) {
	
	Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (!Pawn) {
        return;
    }
    if (GivePickUpTo(Pawn)) {
        PickUpWasTaken();
    }

	
}

void ASTUBasePickUp::PickUpWasTaken() {
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickUp::Respawn, RespawnTime);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpTakenSound, GetActorLocation());
}

void ASTUBasePickUp::Respawn() {
    
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    GenerateRotationYaw();

}

void ASTUBasePickUp::GenerateRotationYaw() {
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
