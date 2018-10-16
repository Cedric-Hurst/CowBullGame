/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void AskWordLength();

FBullCowGame BCGame; // create instant of new game


int main()
{
	do
	{
		AskWordLength();
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());

	return 0;
}


//introduce the game
void PrintIntro()
{
	
	std::cout << std::endl << std::endl;
	std::cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << std::endl;
	std::cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << std::endl;
	std::cout << "*/*/ Welcome to Bulls and Cows, a fun word game. /*/*" << std::endl; //introduce the game
	std::cout << "*/*/                                             /*/*" << std::endl;
	std::cout << "*/*/ Guess the " << BCGame.GetHiddenWordLength() << " letter isogram.                 /*/*" << std::endl; // challenge the player
	std::cout << "*/*/                                             /*/*" << std::endl;
	std::cout << "*/*/ You have a total of " << BCGame.GetMaxTries() << " tries.               /*/*" << std::endl;
	std::cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << std::endl;
	std::cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*" << std::endl;
	std::cout << std::endl;

	return;
}
void AskWordLength()
{
	std::cout << "How long would you like your isogram word to be (3 to 7 letters)?" << std::endl;
	int32 WordLength = 3;
	std::cin >> WordLength;
	std::cin.ignore();
	if (WordLength >= 3 && WordLength <= 7)
	{
		BCGame.GetWordLength(WordLength);
	}
	else
	{
		std::cout << "You didn't enter a proper number so the isogram was set to 3" << std::endl;
		WordLength = 3;
		BCGame.GetWordLength(WordLength);
	}

}
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guess while game is not won and still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		std::cout << std::endl;
		FText Guess = GetValidGuess(); 

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

	
		std::cout << "Bulls = " << BullCowCount.Bulls << " | ";
		std::cout << "Cows = "<< BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
}

// loop until getting valid guess from player
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Incalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". ";
		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);
		

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter word in all lowercase." << std::endl << std::endl;
			break;
		default:
			break;
		}
		
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
	
}

bool AskToPlayAgain()
{
	std::cout << std::endl;
	std::cout << "Would you like to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	std::cout << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	std::cout << std:: endl;
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL Done - YOU WIN!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!" << std::endl;
	}
}
