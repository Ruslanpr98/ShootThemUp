#pragma once

#include "STUCoreTypes.generated.h"

// Health Types

DECLARE_MULTICAST_DELEGATE(FOnDeath);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

// Armor Types

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnArmorChanged, float, float);

USTRUCT(BlueprintType)
struct FArmorData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
    int32 ArmorAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor", meta = (EditCondition = "!Infinite"))
    int32 ArmorPacks;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armor")
    bool Infinite;
};

// Weapon Types

class ASTUBaseWeapon;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASTUBaseWeapon*);


USTRUCT(BlueprintType)
struct FWeaponData {

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage *ReloadAnimMontage;
};


USTRUCT(BlueprintType)
struct FAmmoData {

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponUIData {

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D *CrossHairIcon;

};


//VFX

class UNiagaraSystem;
class USoundCue;


USTRUCT(BlueprintType)
struct FDecalData {

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInterface* Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f;
};

USTRUCT(BlueprintType)
struct FImpactData {

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* Sound;
};


USTRUCT(BlueprintType)
struct FGameData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "8"))
    int32 PlayersNum = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
    int32 RoundsNum = 4;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "5", ClampMax = "180"))
    int32 RoundTime = 10; // timer in seconds

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor DefaultTeamColor = FLinearColor::Red;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TArray<FLinearColor> TeamColors;


    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "5", ClampMax = "15"))
    int32 RespawnTime = 5; // timer in seconds
};

UENUM(BlueprintType)
enum class ESTUMatchState : uint8 {
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESTUMatchState);

USTRUCT(BlueprintType)
struct FLevelData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FName LevelDisplayName = NAME_None;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    UTexture2D* LevelThumb;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSelectedSignature, const FLevelData&);