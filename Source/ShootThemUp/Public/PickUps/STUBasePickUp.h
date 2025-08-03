// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickUp.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASTUBasePickUp();

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "PickUp")
	USphereComponent* CollisionComponent;

    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
    // bool CouldBeTakenTest = true;


  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp")
  float RespawnTime = 5.0f;
	
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	
	virtual void Tick(float DeltaTime) override;

    bool CouldBeTaken() const;

private:

	float RotationYaw = 0.0f;

    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickUpTo(APawn *PlayerPawn);
    void PickUpWasTaken();
  void Respawn();
    void GenerateRotationYaw();

};
