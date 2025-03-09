// Shoot Them Up Game. All RIghts Reserved.

#include "Engine/Canvas.h"
#include "UI/STUGameHUD.h"

void ASTUGameHUD::DrawHUD() {

    Super::DrawHUD();

    DrawCrossHair();
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

