/*
*	@Brief Gameplay of the Bulls and cows game
*/
#pragma once
#include"FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;

class FBullCowGamePlay
{
public:
	FBullCowGamePlay();
	~FBullCowGamePlay();
	void PlayGame();

private:
	// instatiate a new game
	FBullCowGame BCGame; 
	
	// Class methods
	void Printintro();
	FText GetValidGuess() const;
	void PrintBullsAndCows(FBullCowCount BullCowCount) const;
	void TakeGuesses();
	bool AskToPlayAgain() const;
	void PrintGameSummary();
	void setWordLength();
};

