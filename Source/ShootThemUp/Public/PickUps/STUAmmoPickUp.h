// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STUBasePickUp.h"
#include "STUAmmoPickUp.generated.h"

class ASTUBaseWeapon;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()

	protected:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "10.0"))
      int32 ClipsAmount = 10;

	  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
      TSubclassOf<ASTUBaseWeapon> WeaponType;

	private:
    virtual bool GivePickUpTo(APawn *PlayerPawn);
};
