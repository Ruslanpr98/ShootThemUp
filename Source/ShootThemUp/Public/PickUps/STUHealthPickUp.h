// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STUBasePickUp.h"
#include "STUHealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickUp : public ASTUBasePickUp {
	GENERATED_BODY()

	private:
	virtual bool GivePickUpTo(APawn *PlayerPawn);
	
};
