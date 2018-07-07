#pragma once
#include <string>
using int32 = int;
using FString = std::string;
struct BullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Wrong_length,
	Not_lowercase,
	Invalid_Status,
};

enum class EGuessStatus {
	Not_Isogram,
	Not_Lowercase,
	OK,
	Wrong_length,
	Invalid_Status
};

class FBullCowGame {
public:
	FBullCowGame();
	void Reset(); //TODO make more rich return value.
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	BullCowCount SubmitValidGuess(FString) ;
private:
	int32 MyCurrentTry = 1;
	int32 MyMaxTries = 5;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};