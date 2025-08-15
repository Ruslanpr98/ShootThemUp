// Shoot Them Up Game. All RIghts Reserved.


#include "Player/STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer &ObjInit) : Super(ObjInit){
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    
}

void ASTUPlayerCharacter::BeginPlay() {
    Super::BeginPlay();

    check(CameraCollisionComponent);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);


    PlayerInputComponent->BindAxis("MoveXAxis", this, &ASTUPlayerCharacter::MoveXAxis);
    PlayerInputComponent->BindAxis("MoveYAxis", this, &ASTUPlayerCharacter::MoveYAxis);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUPlayerCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUPlayerCharacter::StopSprint);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Reload);
}


void ASTUPlayerCharacter::MoveXAxis(float Amount) {
    isMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveYAxis(float Amount) {
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUPlayerCharacter::StopSprint() {

    bPressedSprint = false;
    UCharacterMovementComponent *CharMovement = Cast<UCharacterMovementComponent>(GetCharacterMovement());

    if (!CharMovement) {
        return;
    }
    CharMovement->MaxWalkSpeed = 600.0f;
}

void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) {
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::CheckCameraOverlap() {
    const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);

    for (auto MeshChild : MeshChildren) {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeometry) {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

void ASTUPlayerCharacter::StartSprint() {
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


bool ASTUPlayerCharacter::isCharSprinting() const {
    return bPressedSprint && isMovingForward && (!GetVelocity().IsZero());
}

void ASTUPlayerCharacter::OnDeath() {
    Super::OnDeath();
    if (Controller) {
        Controller->ChangeState(NAME_Spectating);
    }
}