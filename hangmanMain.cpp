#include "hangman.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
using namespace std;

void startGame() {
	srand(time(NULL));
	bool playing = true;
	Hangman myGame;
	while(playing) {
		myGame.clearScreen();
		myGame.guessLetter();
		playing = myGame.updateGame();
	}
}

int main() {
	startGame();
	return 0;
}