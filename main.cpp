/*
*	This is the console executable, that makes use of the BullCow class.
*	This acts as the view in MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include "FBullCowGamePlay.h"

FBullCowGamePlay Game;

int main() {

	Game.PlayGame();

	return 0;
}