// Shoot Them Up Game. All RIghts Reserved.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, Log, All);

void USTUMenuWidget::NativeOnInitialized() {
    Super:: NativeOnInitialized();

    if (StartGameButton) {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }
}

void USTUMenuWidget::OnStartGame() {


    if (!GetWorld()) {
        return;
    }

    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

    if (!STUGameInstance) {
        return;
    }

    if (STUGameInstance->GetStartupLevelName().IsNone()) {
        UE_LOG(LogSTUMenuWidget, Error, TEXT("Level Name is None"))
        return;
    }

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}