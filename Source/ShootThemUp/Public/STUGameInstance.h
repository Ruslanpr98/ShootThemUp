// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

class USoundClass;


UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    FLevelData GetStartupLevel() const {
        return StartUpLevel;
    }
    
    void SetStartupLevel(const FLevelData& Data) {
        StartUpLevel = Data;
    }

    TArray<FLevelData> GetLevelsData() const {
        return LevelsData;
    };

    
    
    FName GetMenuLevelName() const {
        return MenuLevelName;
    }

    void ToggleVolume();

    
protected:


    UPROPERTY(EditDefaultsOnly, Category = "Game", meta=(ToolTip = "LevelNames Must Be Unique!"))
    TArray<FLevelData> LevelsData;


    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;


    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

private:
    FLevelData StartUpLevel;
    
};
