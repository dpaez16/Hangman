#include "hangman.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <sstream>

using std::printf;
using namespace std;

bool charIsALetter(char c) {
	return ((65 <= (int)c) && ((int)c <= 90)) || (97 <= (int)c) && ((int)c <= 122);
}

int charInStringLocation(char c, string str) {
	for (int i = 0; i < str.length(); i++) {
		if (c == str[i])
			return i;
	}
	return -1;
}

bool charInArray(char c, vector<char> vec) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == c)
			return true;
	}
	return false;
}

void Hangman::initHangman() {
	
	vector<string> wordList;
	
	std::ifstream infile("words.txt");
	std::string line;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		wordList.push_back(line);
	}
	
	word = wordList[rand() % wordList.size()];
	printWord = word;
	
	for (int i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
		printWord[i] = toupper(printWord[i]);
	}
	
	tries = 6;
	correctGuesses = 0;
	blanks.clear();
	badGuesses.clear();
	for (int i = 0; i < word.length(); i++)
		blanks.push_back(true);
}

Hangman::Hangman() {
	initHangman();
}

void Hangman::drawPerson() {
	if (tries == 6) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else if (tries == 5) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else if (tries == 4) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |   |         \n");
		printf("   |   |         \n");
		printf("   |   |         \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else if (tries == 3) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |   |         \n");
		printf("   |  _|         \n");
		printf("   |   |         \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else if (tries == 2) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |   |         \n");
		printf("   |  _|_        \n");
		printf("   |   |         \n");
		printf("   |             \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else if (tries == 1) {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |   |         \n");
		printf("   |  _|_        \n");
		printf("   |   |         \n");
		printf("   | _|          \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	} else {
		printf("   ____          \n");
		printf("   |   |         \n");
		printf("   |   O         \n");
		printf("   |   |         \n");
		printf("   |  _|_        \n");
		printf("   |   |         \n");
		printf("   | _| |_       \n");
		printf("   |             \n");
		printf("___|__________   \n");
		cout << endl;
	}
	cout << endl;
}

void Hangman::drawChars() {
	for (int i = 0; i < blanks.size(); i++) {
		if (blanks[i])
			cout << "_ ";
		else
			cout << printWord[i] << " ";
	}
	
	cout << endl;
	cout << endl;
	
	cout << "Incorrect Guesses: ";
	for (int i = 0; i < badGuesses.size(); i++) {
		if (i == badGuesses.size() - 1)
			cout << badGuesses[i];
		else
			cout << badGuesses[i] << ", ";
	}
	
	cout << endl;
	cout << endl;
}

bool Hangman::updateGame() {
	if (tries == 0 || correctGuesses == word.length()) {
		bool properInput = false;
		string input;
		while (!properInput) {
			clearScreen();
			drawPerson();
			drawChars();
			if (tries == 0)
				cout << "You lose! The word was " << printWord << ". Play again? [Y, N]: ";
			else
				cout << "You win! Play again? [Y, N]: ";
			cin >> input;
			if (input.length() != 1)
				continue; //not 1 character
			else if (input[0] != 'Y' && input[0] != 'N' && input[0] != 'y' && input[0] != 'n')
				continue; // not Y, N/y, n format
			else
				properInput = true;
		}
		initHangman();
		clearScreen();
		return (input[0] == 'Y' || input[0] == 'y');  
	} else 
		return true;
}

void Hangman::guessLetter() {
	
	bool guessProper = false;
	string input;
	while(!guessProper) {
		clearScreen();
		drawPerson();
		drawChars();
		cout << "Guess a letter: ";
		getline(cin, input);
		
		if (input.length() != 1)
			continue; //not proper size (1 char) or not an actual letter
		else {
			char c = toupper(input[0]);
			int index = charInStringLocation(c, printWord);
			if (!charIsALetter(c))
				continue;	//not even a letter
			else if (charInArray(c, badGuesses))
				continue;	//duplication within badGuesses
			else {
				if (charInStringLocation(c, printWord) != -1) {
					if (word[charInStringLocation(c, printWord)] == '$')
						continue; //duplication within correct letters
					else
						guessProper = true;
				} else
					guessProper = true;
			}
		}
	}
	
	char x = toupper(input[0]);
	
	bool guessCorrect = false;
	for (int i = 0; i < word.length(); i++) {
		if(x == word[i]) {
			guessCorrect = true;
			blanks[i] = false;
			word[i] = '$';
			correctGuesses++;
		}
	}
	
	if (!guessCorrect) {
		tries--;
		badGuesses.push_back(x);
	}

}

void Hangman::clearScreen() {
   for (int i = 0; i < 75; i++)
      cout << endl;
}
