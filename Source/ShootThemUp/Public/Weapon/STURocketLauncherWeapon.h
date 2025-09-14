// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURocketLauncherWeapon.generated.h"


class ASTUProjectile;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTURocketLauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
 public:

	void StartFire() override;

	//void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
  TSubclassOf<ASTUProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;


  virtual void MakeShot() override;

	
};
