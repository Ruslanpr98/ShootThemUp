// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArmComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    bool isCharSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

private:
	  bool bPressedSprint = false;
      bool isMovingForward = false;

	void MoveXAxis(float Amount);
    void MoveYAxis(float Amount);
    void StartSprint();
    void StopSprint();
};
