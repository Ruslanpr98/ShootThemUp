// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, Log, All);

void USTUGoToMenuWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (GoToMenuButton) {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
}

void USTUGoToMenuWidget::OnGoToMenu() {
    if (!GetWorld()) return;

    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

    if (!STUGameInstance) {
        return;
    }

    if (STUGameInstance->GetMenuLevelName().IsNone()) {
        UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("MenuLevel Name is None"))
        return;
    }

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetMenuLevelName());
}