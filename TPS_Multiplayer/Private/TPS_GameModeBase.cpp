// Shoot Them Up Game


#include "TPS_GameModeBase.h"
#include "TPS_Charachter.h"
#include "TPSPlayerController.h"

ATPS_GameModeBase::ATPS_GameModeBase() {

	DefaultPawnClass = ATPS_Charachter::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();

}