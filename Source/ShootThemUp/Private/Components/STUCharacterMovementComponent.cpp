// Shoot Them Up Game. All RIghts Reserved.


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const {
    const auto MaxSpeed = Super::GetMaxSpeed();

    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return Player && Player->isCharSprinting() ? MaxSpeed * RunModifier : MaxSpeed;
}
