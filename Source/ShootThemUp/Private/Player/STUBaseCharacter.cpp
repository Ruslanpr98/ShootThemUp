// Shoot Them Up Game. All RIghts Reserved.


#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


    PlayerInputComponent->BindAxis("MoveXAxis", this, &ASTUBaseCharacter::MoveXAxis);
    PlayerInputComponent->BindAxis("MoveYAxis", this, &ASTUBaseCharacter::MoveYAxis);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::StopSprint);
}

void ASTUBaseCharacter::MoveXAxis(float Amount) {
    isMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveYAxis(float Amount) {
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::StopSprint() {

    bPressedSprint = false;
    UCharacterMovementComponent *CharMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

    if (!CharMovement) {
        return;
    }
    CharMovement->MaxWalkSpeed = 600.0f;
}

void ASTUBaseCharacter::StartSprint() {
    if (!isMovingForward) {
        return;
    }
    bPressedSprint = true;
    UCharacterMovementComponent *CharMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

    if (!CharMovement) {
        return;
    } 
    CharMovement->MaxWalkSpeed = 1000.0f;
}


bool ASTUBaseCharacter::isCharSprinting() const {
    return bPressedSprint && isMovingForward && (!GetVelocity().IsZero());
}

float ASTUBaseCharacter::GetMovementDirection() const {
    if (GetVelocity().IsZero()) {
        return 0.0f;
    }
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}
