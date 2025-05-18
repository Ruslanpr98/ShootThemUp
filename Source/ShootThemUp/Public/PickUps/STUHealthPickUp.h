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


	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "50.0"))
    int32 HealthAmount = 50;


	private:

		
	virtual bool GivePickUpTo(APawn *PlayerPawn);
	
};
