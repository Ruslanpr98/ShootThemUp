// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()

public:
    ASTUPlayerCharacter(const FObjectInitializer& ObjInit);
    
    
    
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    //UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool isCharSprinting() const override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;


    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArmComponent;


    virtual void OnDeath() override;

private:
    bool bPressedSprint = false;
    bool isMovingForward = false;

    void MoveXAxis(float Amount);
    void MoveYAxis(float Amount);
    
    void StartSprint();
    void StopSprint();
};
