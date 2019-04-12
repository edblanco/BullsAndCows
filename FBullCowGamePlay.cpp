#pragma once
#include "FBullCowGamePlay.h"
#include<iostream>
#include<string>

FBullCowGamePlay::FBullCowGamePlay() {
}


FBullCowGamePlay::~FBullCowGamePlay() {
}

void FBullCowGamePlay::PlayGame() {
	do {
		Printintro();
		TakeGuesses();
		PrintGameSummary();
	} while (AskToPlayAgain());
	return;
}

void FBullCowGamePlay::Printintro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	setWordLength();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;

	return;
}

FText FBullCowGamePlay::GetValidGuess() const {
	FText Guess = "";

	while (true) {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: \n";
		std::getline(std::cin, Guess);

		switch (BCGame.CheckGuessVAlidity(Guess)) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all lowercase letters\n";
			break;
		case EGuessStatus::OK:
			return Guess;
		default:
			return NULL;
		}
		std::cout << std::endl;
	}
}

void FBullCowGamePlay::PrintBullsAndCows(FBullCowCount BullCowCount) const {
	std::cout << "Bulls = " << BullCowCount.Bulls;
	std::cout << ". Cows = " << BullCowCount.Cows;
	std::cout << std::endl;
}

void FBullCowGamePlay::TakeGuesses() {
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses 
	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries)) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		PrintBullsAndCows(BullCowCount);
		std::cout << std::endl;
	}
	return;
}

bool FBullCowGamePlay::AskToPlayAgain() const {
	std::cout << "Do you want to play again? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);

	return (toupper(Response[0]) == 'Y');
}

void FBullCowGamePlay::PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations! You beat the game.\n";
	}
	else {
		std::cout << "Bad Lucky buddy, you lost XD \n";
	}
	BCGame.Reset();
	return;
}

void FBullCowGamePlay::setWordLength() {
	FString WordLength = "";
	std::cout << "Please select the word Length between " << BCGame.GetMinLength() <<  " and " << BCGame.GetMaxLength();
	std::cout << std::endl;
	std::getline(std::cin, WordLength);
	while (!BCGame.setWordLength(std::atoi(WordLength.c_str()))) {
		std::cout << "Wrong length. Must be beetween " << BCGame.GetMinLength() <<  " and " << BCGame.GetMaxLength();
		std::cout << std::endl;
		std::getline(std::cin, WordLength);
	}
}
