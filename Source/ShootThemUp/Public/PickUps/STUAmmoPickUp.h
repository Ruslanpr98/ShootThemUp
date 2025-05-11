// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STUBasePickUp.h"
#include "STUAmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickUp : public ASTUBasePickUp
{
	GENERATED_BODY()
	

	private:
    virtual bool GivePickUpTo(APawn *PlayerPawn);
};
