// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "WGJ96GameMode.h"
#include "WGJ96PlayerController.h"
#include "WGJ96Pawn.h"

AWGJ96GameMode::AWGJ96GameMode()
{
	// no pawn by default
	DefaultPawnClass = AWGJ96Pawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AWGJ96PlayerController::StaticClass();
}
