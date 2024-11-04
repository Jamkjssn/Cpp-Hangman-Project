#include "word.h"
#include <random>

using namespace std;

Word::Word() : word(""), wordGuessed(false)
{
}

void Word::setWord(int length) {
	//WordBank was AI generated, no way i couldve come up with this list on my own
	vector<string> wordsLength3 = {"bat", "cat", "dog", "hat", "rat", "sun", "pen", "box", "jar", "fan", "fig", "owl"};
	vector<string> wordsLength4 = {"tree", "frog", "lion", "bear", "wolf", "fish", "star", "door", "lamp", "pear", "ball", "moss"};
	vector<string> wordsLength5 = {"grape", "flute", "chair", "stone", "piano", "apple", "knife", "peach", "clown", "bread", "grain", "sheep"};
	vector<string> wordsLength6 = {"castle", "forest", "planet", "rocket", "bridge", "shovel", "bucket", "button", "flower", "magnet", "puzzle", "sponge"};
	vector<string> wordsLength7 = {"battery", "concert", "diamond", "picture", "sandals", "justice", "courage", "whistle", "sunrise", "printer", "blanket", "captain"};
	vector<string> wordsLength8 = {"elephant", "notebook", "dolphins", "mountain", "umbrella", "medicine", "firewood", "scissors", "wildlife", "airplane", "daylight", "conquest"};
	
	mt19937 generator(random_device{}());
	int random_int = uniform_int_distribution<int>(1, 12)(generator);
	
	if (length == 3) {
		word = wordsLength3[random_int];
	}
	else if (length == 4) {
		word = wordsLength4[random_int];
	}
	else if (length == 5) {
		word = wordsLength5[random_int];
	}
	else if (length == 6) {
		word = wordsLength6[random_int];
	}
	else if (length == 7) {
		word = wordsLength7[random_int];
	}
	else if (length == 8) {
		word = wordsLength8[random_int];
	}

	// Set guessed letters to false
	spotsGuessed.resize(word.length(), false);
}

bool Word::guessLetter(char letter) {
	// Check if a guessed letter is in the word
	// initialize correct bool
	bool correct = false;
	// Iterate through each letter of the word checking if the letter matches any
	for (int i = 0; i < word.size(); ++i) {
		// If there's a match set its guessed state to true, and set correct to true so that the guess attempt isn't used
		if (tolower(word[i]) == tolower(letter)) {
			spotsGuessed[i] = true;
			correct = true;
		}
	}
	// Return whether they were correct or not
	return correct;
}

bool Word::guessWord(string &guess) {
	return guess == word;
}

bool Word::guessedCorrectly() {
	// Check if the word is complete, use after each guess to avoid saying they lose after getting the whole thing.

	if (wordGuessed) {							
		// Not sure why this might be applicable, but feels right to include.
		return true;
	}
	else {										
		
		// Check and see if all the spots in the word have been guessed yet
		for (bool position : spotsGuessed) {
			
			// If any of them havent been guessed yet, return false
			if (position == false) {			
				return false;							
			}
		}
		return true;
	}
}

string Word::displayWordHidden()
{
	// Start with an empty string to be added to
	string wordHidden = "";

	// Initialize index at 0
	int index = 0;

	// Iterate through guessed positions list
	for (bool position : spotsGuessed) {

		// For spots not guessed indicate a blank with a "_"
		if (position == false) {
			wordHidden += "_";
		}

		// For spots already guessed use the actual letter
		else {
			wordHidden += toupper(word[index]);
		}

		// Increment index and add spacers between characters
		index++;
		wordHidden += " ";
	}
	// Return final result
	return wordHidden;
}

string Word::getWord() {
	// Return the word
	return word;
}
