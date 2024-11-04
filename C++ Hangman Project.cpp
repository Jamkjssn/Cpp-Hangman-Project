// C++ Hangman Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <list>
#include <chrono>
#include <thread>
#include "game.h"

using namespace std;

// Function Prototypes
int menuChoice(string options, int num_options);
void clearConsole();

int main()
{
    cout << "\t\tWelcome To The Hangman Game!\n";
    string startMenu = "(1) Start Game\n(2) Exit\n";
    int userChoice = menuChoice(startMenu, 2);
    if (userChoice != 2) {
        // Cool little start message that dissapears
        clearConsole();
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\n\n\t\tLet the games begin";
        this_thread::sleep_for(chrono::seconds(3));
        clearConsole();

        // Create instance of Game
        Game newGame;

        // Go through setup
        bool setup = false;
        while (!setup) {
            setup = newGame.gameSetup();        // Repeat setup until they make it through
        }        
        
        // Start the game
        newGame.gameStart();
    }
}

// I know it looks like this was a lot of work for nothing, i had a different design in mind that wouldve had most of the menus in this file.
// In order to make things run smoother things had to change that and I wont get rid of this since it does work, even if its more complicated than necessary. 
int menuChoice(string options, int numOptions) {
    // Basic layout of any menu that displays options and takes an input number choice. 
    // Parameters:
    //  Options: A single string showing each of the options with a number associated to each one starting at 0
    //  num_options: An integer indecating how many different options the user has to choose from in order to only accept valid choices. 
    int userChoice = -1;                                                            // Initialize choice variable
    while (true) {                                                                  // Loop until a valid choice is made
        cout << options;                                                            // Display their options
        cout << "\nUser Choice: ";
        cin >> userChoice;                                                          // Get their response
        if ((userChoice > 0) && (userChoice < numOptions + 1)) {                    // If their choice was valid return the chioce
            return userChoice;
        }
        else {  
            clearConsole();                                                         // Invalid answer chosen, send them back to beginning of choice
            cout << "Sorry, but that was not a valid option. Please try again.\n";
        }
    }
}

// Generic function I found online to clear the console
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}