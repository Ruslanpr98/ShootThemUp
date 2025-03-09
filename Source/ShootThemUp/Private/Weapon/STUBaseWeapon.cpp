// Shoot Them Up Game. All RIghts Reserved.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBaseWeapon::Fire() {
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}


