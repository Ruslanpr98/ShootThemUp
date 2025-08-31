// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUUtils.h"

void USTUGameOverWidget::NativeOnInitialized() {

    Super::NativeOnInitialized();

    if(GetWorld()) {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode) {
            GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton) {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
    
}


void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State) {

    if (State == ESTUMatchState::GameOver) {
        UpdatePlayerStat();
    }
    
}

void USTUGameOverWidget::UpdatePlayerStat() {
    if (!GetWorld() || !PlayerStatBox) {
        return;
    }

    PlayerStatBox->ClearChildren();

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It) {
        const auto Controller = It->Get();
        if (!Controller) {
            continue;
        }

        const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);

        if (!PlayerState) {
            continue;
        }

        const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);

        if (!PlayerStatRowWidget) {
            continue;
        }

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsCount()));
        PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsCount()));
        PlayerStatRowWidget->SetTeam(STUUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}

void USTUGameOverWidget::OnResetLevel() {

    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}