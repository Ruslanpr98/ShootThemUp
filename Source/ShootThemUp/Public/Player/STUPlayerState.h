// Shoot Them Up Game. All RIghts Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

	public:
    void SetTeamID(int32 ID) {TeamID = ID;}
    int32 GetTeamID() const {return TeamID;}

    void SetTeamColor(const FLinearColor& color) {TeamColor = color;}
    FLinearColor GetTeamColor() const {return TeamColor;}
	
	private:
    int32 TeamID;
      FLinearColor TeamColor;
};
