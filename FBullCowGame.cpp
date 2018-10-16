#pragma once
#include "FBullCowGame.h"
#include <map>

//to make syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const{ return TheWordLength; }
void FBullCowGame::GetWordLength(int32 WordLength) { TheWordLength = WordLength; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

FString FBullCowGame::MyHiddenWord() const
{
	//must be an isogram
	TMap<int32, FString> WordLengthToWord{ { 3,"mad" },{ 4,"coin" },{ 5,"spicy" },{ 6,"planet" },{ 7,"urgency" } };
	return WordLengthToWord[TheWordLength];
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[TheWordLength];
}

void FBullCowGame::Reset()
{

	TheHiddenWord = MyHiddenWord();

	MyCurrentTry = 1;
	
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length; 
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else 
	{
		return EGuessStatus::OK; 
	}
		
}

// receives a VALID guess, increments turn, and returns above ^^
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 WordLength = TheHiddenWord.length(); // assuming same length as guess

	//loop through all leters in the Hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == TheHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
						BullCowCount.Bulls++;
				}
				else
				{
						BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat 0 and 1 letter strings as isograms
	if (Guess.length() <= 1) { return true; }

	// setup the map
	TMap <char, bool> LetterSeen;

	// loop through each character of word
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);

		// if there is double character
		if (LetterSeen[Letter]) { return false; }

		else { LetterSeen[Letter] = true; } // add letter to map
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{

	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
