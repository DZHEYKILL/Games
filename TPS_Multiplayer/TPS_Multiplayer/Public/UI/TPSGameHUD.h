// Shoot Them Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"

#include "TPSGameHUD.generated.h"


UCLASS()
class TPS_MULTIPLAYER_API ATPSGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;

private:
	void DrawCrossHair();
};
