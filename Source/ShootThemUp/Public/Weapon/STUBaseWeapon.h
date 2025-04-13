// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();

	virtual void StopFire();

	void ChangeClip();

	bool CanReload() const;

	FOnClipEmptySignature OnClipEmpty;

	FWeaponUIData GetUIData() const {
        return UIData;
	}

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent *WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{
		DefaultAmmo.Bullets = 15,
		DefaultAmmo.Clips = 10,
		DefaultAmmo.Infinite = false
	};


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

	APlayerController *GetPlayerController() const;

	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotaion) const;

	FVector GetMuzzleWorldLocation() const;

	void DecreaseAmmo();

	bool IsAmmoEmpty() const;

	bool IsClipEmpty() const;

	void LogAmmo();

	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);

	private:

		FTimerHandle ShotTimerHandle;

		FAmmoData CurrentAmmo;
};
