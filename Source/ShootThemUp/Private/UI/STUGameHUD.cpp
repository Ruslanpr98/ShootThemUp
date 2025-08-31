// Shoot Them Up Game. All RIghts Reserved.

#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "STUGameModeBase.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, Log, All);

void ASTUGameHUD::DrawHUD() {

    Super::DrawHUD();

    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() {
    Super::BeginPlay();
    
    GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets) {
        const auto GameWidget = GameWidgetPair.Value;
        if(!GameWidget) continue;

        GameWidget->AddToViewport();

        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GetWorld()) {
        const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());

        if (GameMode) {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASTUGameHUD::DrawCrossHair() {

    int32 SizeX = Canvas->SizeX;
    int32 SizeY = Canvas->SizeY;
    
    const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float HalfLineThickness = 2.0f;
    const FLinearColor HalfLineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, HalfLineColor, HalfLineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, HalfLineColor, HalfLineThickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State) {

    if(CurrentWidget) {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GameWidgets.Contains(State)) {
        CurrentWidget = GameWidgets[State];
    }

    if(CurrentWidget) {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    
    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}

