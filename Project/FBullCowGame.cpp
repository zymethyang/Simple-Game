#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

int FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;
	MyCurrentTry = MAX_TRIES;
	const FString HIDDEN_WORD = "donkey";
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = 8;
	bGameIsWon = false;
	return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (false) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length()!= GetHiddenWordLength()) {
		return EGuessStatus::Wrong_length;
	}
	else {
		return EGuessStatus::OK;
	}
}


BullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	BullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChart = 0; MHWChart < WordLength; MHWChart++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[MHWChart] == MyHiddenWord[MHWChart]) {
				if (MHWChart == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() < 1) {
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

