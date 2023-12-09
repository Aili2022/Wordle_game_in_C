#pragma once
#include"Dictionary.h"


using namespace std;

class ExtendedDictionary : public Dictionary
{
private:
	int highestScore =0;

public:

	//Default constructor
	ExtendedDictionary() {};

	//getter for highestScore
	int getHighestScore() { return highestScore; }

	//setter for highestScore
	int setHighestScore(int& highestScore)
	{  
		return this->highestScore = highestScore;

	}

	//Task5 Palindromes
	void listPalindromesWord();

	//Task6 Rhyming words
	void findRhymingWords(const string& userInput);

	//Task7 Guess the fourth word
	void guessWordGame();


	//Task8 Cheat at Searchdle
	void cheatAtSearchdle();
};