/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind*/

#pragma once
#include <string>

//to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Incalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{


public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	void GetWordLength(int32);
	int32 GetHiddenWordLength() const;
	FString MyHiddenWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset();
	
	FBullCowCount SubmitValidGuess(FString);
	

private:
	int32 MyCurrentTry; // in constructor
	int32 MyMaxTries;
	int32 TheWordLength;
	bool bGameIsWon;
	FString TheHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
