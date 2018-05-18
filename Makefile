all: main clear
.PHONY: all main clear

main: hangman.h hangman.cpp hangmanMain.cpp
	g++ -o hangman hangman.h hangman.cpp hangmanMain.cpp

clear:
	clear
	clear

clean:
	rm -f *.exe *.o
	clear
	clear
