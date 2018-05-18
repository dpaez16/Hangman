#ifndef HANGMAN_H
#define HANGMAN_H

#include <vector>
#include <string>
using namespace std;

class Hangman {
	public:
		Hangman();
		void initHangman();
		void drawPerson();
		void drawChars();
		void guessLetter();
		void clearScreen();
		bool updateGame();
		
	private:
		vector<bool> blanks;
		vector<char> badGuesses;
		int tries;
		int correctGuesses;
		string word;
		string printWord;
};

#endif