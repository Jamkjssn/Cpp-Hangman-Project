#pragma once

#include <string>
#include <vector>
#include "word.h"

using namespace std;

class Game
{
private:
	int remainingGuesses;
	int totalGuesses;
	int gameDifficulty;
	vector<char> guessedLetters;
	vector<string> guessedWords;
	Word currentWord;

public:
	Game();

	bool gameSetup();					// Setup the game

	void gameStart();					// Begin Game loop

	void playRound();					// Give options and run each round

	void endGame(bool victory);			// End of Game, Display loss or victory

	void gameStatus();					// Show current status of game(Guesses, letters guessed, amount of word discovered)

	bool letterGuessed(char letter);	// Check if a letter has already been guessed
};

