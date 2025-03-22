// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USkeletalMeshComponent *WeaponMesh;
	// Called when the game starts or when spawned

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  FName MuzzleSocketName = "MuzzleSocket";

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float TraceMaxDistance = 1500.0f;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  float DamageValue = 10.0f;

	virtual void BeginPlay() override;

	void MakeShot();

	APlayerController *GetPlayerController() const;

	bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotaion) const;

	FVector GetMuzzleWorldLocation() const;

	bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

	void MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd);

	void MakeDamage(FHitResult& HitResult);

};
