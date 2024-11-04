#pragma once

#include <string>
#include <vector>

using namespace std;

class Word
{
private:
	string word;					// The word itself
	vector<bool> spotsGuessed;		// Which spaces have already been guessed
	bool wordGuessed;				// Has the entire word been guessed yet

public:
	Word();

	void setWord(int length);				// Set the word according to specified length

	bool guessLetter(char letter);			// Guess a specific letter

	bool guessWord(string& guess);			// Guess an entire word

	bool guessedCorrectly();				// Has the word been guessed yet

	string displayWordHidden();				// Display the word without showing things that havent been guessed

	string getWord();						// Returns the actual full word

};

