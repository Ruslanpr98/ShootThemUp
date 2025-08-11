// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

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

    bool IsAmmoEmpty() const;

	FOnClipEmptySignature OnClipEmpty;

	FWeaponUIData GetUIData() const {
        return UIData;
	}

	FAmmoData GetAmmoData() const {
        return CurrentAmmo;
    }

	bool TryToAddAmmo(int32 ClipsAmount);

    bool IsAmmoFull() const;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	void DecreaseAmmo();

	

	bool IsClipEmpty() const;

	void LogAmmo();

	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);

	UNiagaraComponent* SpawnMuzzleEffect();

	private:

		FTimerHandle ShotTimerHandle;

		FAmmoData CurrentAmmo;
};
