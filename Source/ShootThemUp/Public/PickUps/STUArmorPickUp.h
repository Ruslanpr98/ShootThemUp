// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STUBasePickUp.h"
#include "STUArmorPickUp.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUArmorPickUp : public ASTUBasePickUp
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    int32 ArmorAmount = 25;

    virtual bool GivePickUpTo(APawn* PlayerPawn) override;
};