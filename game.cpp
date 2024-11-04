#include "game.h"
#include "word.h"
#include <iostream>
#include <random>

using namespace std;

Game::Game()
{
}

bool Game::gameSetup() {
	// Initialize variables to -1
	int difficultyChoice = -1;
	int numGuesses = -1;
	int wordLetters = -1;

	// Random number for word length stuff later
	mt19937 generator(random_device{}());
	int random_int = uniform_int_distribution<int>(0, 1)(generator);

	// First have the player choose a difficulty
	cout << "\t\tGame Setup\n\n";
	cout << "Difficulty levels:\n\t(1) Easy\n\t(2) Medium\n\t(3) Hard\n\t(4) Insane\n\t(5) Custom\n\n";
	cout << "Select your game difficulty:";
	cin >> difficultyChoice;

	// Error handling
	if (difficultyChoice < 1 || difficultyChoice > 6) {
		cout << "\n\nSorry but that is not a valid option, please restart the game creation process.\n\n";
		return false;
	}

	// Difficulty one
	else if (difficultyChoice == 1) {
		// Set number of letters in the word
		wordLetters = 8;
		// Set number of guesses
		numGuesses = 10;
	}

	// Difficulty two
	else if (difficultyChoice == 2) {
		// Set number of letters in the word
		wordLetters = random_int+6;	// This will randomly be either 6 or 7
		// Set number of guesses
		numGuesses = 8;
	}
	
	// Difficulty three
	else if (difficultyChoice == 3) {
		// Set number of letters in the word
		wordLetters = random_int+4; //This will randomly be either 4 or 5
		// Set number of guesses
		numGuesses = 6;
	}
	
	// Difficulty four
	else if (difficultyChoice == 4) {
		// Set number of letters in the word
		wordLetters = 3;
		// Set number of guesses
		numGuesses = 4;
	}

	// Extra handling for custom difficulty
	else if (difficultyChoice == 5) {
		cout << "\nHow many guesses woud you like to have(1-12): ";
		cin >> numGuesses;
		if (numGuesses < 1 || numGuesses > 12) {
			cout << "\n\nSorry but that is not a valid option, please restart the game creation process.\n\n";
			return false;
		}
		else {
			cout << "\nHow many letters would you like the word to have(3-8): ";
			cin >> wordLetters;
			if (wordLetters < 2 || wordLetters > 7) {
				cout << "\n\nSorry but that is not a valid option, please restart the game creation process.\n\n";
				return false;
			}
		}
	}
	// Once this is aquired use the word.cpp setWord method to set and get the word that will be used. 
	currentWord.setWord(wordLetters);
	totalGuesses = numGuesses;
	remainingGuesses = numGuesses;
	return true;
}

void Game::gameStart() {
	while (remainingGuesses > 0 && !currentWord.guessedCorrectly()) {
		playRound();
	}
	endGame(currentWord.guessedCorrectly());
}

void Game::playRound() {
	gameStatus();
	int choice = -1;
	cout << "(1) Guess a Letter\n(2) Guess the Word\n(3) Forfeit\n";
	cout << "Your move: ";
	cin >> choice;

	// Error handling added during debugging
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Sorry that wasn't a valid input, try again\n\n";
	}

	if (choice > 0 || choice < 4) {
		// Having recieved a valid input now let them guess
		
		// Guess a letter
		if (choice == 1) {
			char letter;
			cout << "Enter the letter you'd like to guess: ";
			cin >> letter;
			cout << "\n\n";

			// Dont let them guess a letter they've already guessed
			if (letterGuessed(letter)) {
				cout << "You've already guessed this letter, pick a different one: ";
				cin >> letter;
				cout << "\n\n";
			}

			// Check if the letter was in the word, if it wasnt then deduct a guess
			if (!letterGuessed(letter)) {
				guessedLetters.push_back(letter);
				if (!currentWord.guessLetter(letter)) {
					remainingGuesses--;
				}
			}
		}

		// Guess the word
		else if (choice == 2) {
			string wordGuess;
			cout << "What would you like to guess: ";
			cin >> wordGuess;
			if(!currentWord.guessWord(wordGuess)) {
				guessedWords.push_back(wordGuess);
				remainingGuesses--;
			}
		}

		//Forfeit
		else if (choice == 3) {
			int doubleCheck;
			//Confirm that they want to forfeit
			cout << "Enter (1) to confirm: ";
			cin >> doubleCheck;
			if (doubleCheck == 1) {
				// Drain guesses to end the game
				remainingGuesses = 0;
			}
		}
	}
	else {
		cout << "Sorry that wasn't a valid input, try again\n\n";

	}
}

void Game::endGame(bool won) {
	if (won) {
		cout << "Congratulations! You guessed the word!\n";
	}
	else {
		cout << "Defeat, Youll get it next time\nThe word was: " << currentWord.getWord() << "\n";
	}
}

void Game::gameStatus() {
	// Game Status to be displayed beginning each round
	// Have the number of guesses used represented by an "X" in the box, total boxes is total guesses
	cout << "Guesses Left:";
	for (int i = totalGuesses; i > 0; i--) {	
		if (i <= remainingGuesses) {
			cout << "[ ] ";
		}
		else {
			cout << "[X] ";
		}
	}
	// Display guessed letters
	cout << "\n\nGuessed Letters: ";
	for (char letter : guessedLetters) {
		cout << letter << " ";
	}
	if (size(guessedLetters) == 0) {
		cout << "None";
	}

	// Display word with correct guesses filled in
	cout << "\n\n Word: " << currentWord.displayWordHidden() << "\n\n";
}

bool Game::letterGuessed(char letter) {
	// Check the current list of guessed letters to see if the current guess is already on it
	for (char guessedLetter : guessedLetters) {
		if (guessedLetter == letter) {
			return true;
		}
	}
	return false;
}