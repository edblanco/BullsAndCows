/*
*	@brief
*	Game logic.
*	The game is a simple guess word game
*/

#pragma once
#include <string>
#include <map>

#define TMap std::map

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame
{
public:
	FBullCowGame();
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	int32 GetMinLength() const;
	int32 GetMaxLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessVAlidity(FString) const; 
	bool setWordLength(int32);

	void Reset(); //make a more rich return value

	// counts bulls & cows, and increases try #, assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	void setIsGameWon(bool );
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	// Isograms for the game. Must be ordered
	TMap<int32, FString> Isograms{
		{3, FString("ado")},
		{4, FString("grow")},
		{5, FString("cargo")},
		{6, FString("planet")},
		{7, FString("girasol")},
		{8, FString("orgasmic")}
	};
};

