// Shoot Them Up Game. All RIghts Reserved.


#include "UI/STUBaseWidget.h"
#include "SOund/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void USTUBaseWidget::Show() {
    PlayAnimation(ShowAnimation);

    UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}