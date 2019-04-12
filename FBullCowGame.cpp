#pragma once
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() {
	Reset();
}

FBullCowGame::~FBullCowGame() {
}

void FBullCowGame::Reset() {
	constexpr int32 FIRST_TRY = 1;
	constexpr bool IS_GAME_WON = false;
	const FString HIDDEN_WORD = "planet"; // This MUST be an Isogram

	MyCurrentTry = FIRST_TRY;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = IS_GAME_WON;
	return;
}

// receives a VALID guess, increments turn, and returns Bulls and Cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	size_t WordLength = MyHiddenWord.length();
	// setup a return variable
	FBullCowCount BullCowCount;

	++MyCurrentTry;
	// loop throug all letters in the HiddenWord
	for (size_t HWChar = 0; HWChar < WordLength; ++HWChar){
		// Compare letters against the guess
		for (size_t GChar = 0; GChar < Guess.length(); ++GChar){
			if (MyHiddenWord[HWChar] == Guess[GChar]){
				if (HWChar == GChar){ // they are in the same place
					++BullCowCount.Bulls;
				}else{ // They are in different place
					++BullCowCount.Cows;
				}
			}
		}
	}
	setIsGameWon(WordLength == BullCowCount.Bulls);
	return BullCowCount;
}

int32 FBullCowGame::GetMaxTries() const {
	static TMap<int32, int32> WordLengthtoMaxTries{ {3,4}, {4,6}, {5,9}, {6,13}, {7,20}, {8,30}, {9,45}, {10,67} };
	return WordLengthtoMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

int32 FBullCowGame::GetMinLength() const {
	return Isograms.begin()->first;
}

int32 FBullCowGame::GetMaxLength() const {
	auto iter = Isograms.end();
	--iter;
	return iter->first;
}

bool FBullCowGame::IsGameWon() const {
	return bGameIsWon;
}

void FBullCowGame::setIsGameWon(bool IsWon) {
	bGameIsWon = IsWon;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}
	// setup out map
	TMap<char, bool> LetterSeen;
	// loop through all the letter of the word 
	for (auto Letter : Word){
		Letter = tolower(Letter);
		if (LetterSeen[Letter]){
			return false;
		}else {
			LetterSeen[Letter] = true;
		}
	} 
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() <= 1) {
		return true;
	}

	for (auto Letter : Word) {
		if (isupper(Letter)) {
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessVAlidity(FString Guess) const {
	
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_LowerCase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::setWordLength(int32 WordLenght) {
	if ((WordLenght >= GetMinLength()) && (WordLenght <= GetMaxLength())) {
		MyHiddenWord = Isograms[WordLenght];
		return true;
	}
	return false;
}
