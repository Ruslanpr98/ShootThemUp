// Shoot Them Up Game. All RIghts Reserved.


#include "STUGameInstance.h"
#include "Sound/STUSoundFuncLib.h"

void USTUGameInstance::ToggleVolume() {
    USTUSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}