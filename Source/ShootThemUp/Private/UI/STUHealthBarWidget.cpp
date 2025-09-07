// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHeathPercent(float Percent) {

    if(!HealthProgressBar) return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
    ? ESlateVisibility::Hidden
    : ESlateVisibility::Visible;

    HealthProgressBar->SetVisibility(HealthBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? SafeColor : DangerColor;

    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}