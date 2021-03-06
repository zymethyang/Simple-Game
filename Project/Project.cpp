// Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"
using FText = std::string;
using int32 = int;
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame;

void PrintIntro() {
	//introduce game
	constexpr int NUMBER_OF_TURNS = 6;
	std::cout << "Wellcome to Bulls and Cows game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

std::string GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		//get a guess from a player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";

		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

int main()
{
	bool bWantsToPlay = false;
	do {
		PrintIntro();
		PlayGame();
		bWantsToPlay = AskToPlayAgain();
	} while (bWantsToPlay);


	system("pause");
	return 0;
}

void PlayGame()
{
	BCGame.Reset();	
	int32 MaxTries = BCGame.GetMaxTries();
	
	while(!BCGame.IsGameWon()&&BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = "";
		Guess = GetValidGuess();
		
		BullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//repeat the guess back to them
		std::cout << "Bulls = " << BullCowCount.Bulls << "\n";
		std::cout << "Cows = " << BullCowCount.Cows << "\n";
		std::cout << Guess;
		std::cout << std::endl;
	}

	PrintGameSummary();

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << "Is it right? ";
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE YOU WITH \n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}