// Shoot Them Up Game. All RIghts Reserved.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUMenuWidget::NativeOnInitialized() {
    Super:: NativeOnInitialized();

    if (StartGameButton) {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }
}

void USTUMenuWidget::OnStartGame() {
    const FName StartUpLevelName = "TestLevel";

    UGameplayStatics::OpenLevel(this, StartUpLevelName);
}