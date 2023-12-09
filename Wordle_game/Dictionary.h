#pragma once
#include<string>
#include<vector>
#include"Word.h"

using namespace std;

//Create a Dictionary class that holds the vector of Word objects;
//Input:
//Output:
//Written by:Aili Lu
//Creation date:02/05/2023
class Dictionary
{
private:
    vector<Word> words;

public:
    //Default constructor
    Dictionary() {}


    //Getter
    const vector<Word>& getWords()
    {
        return words;
    }

    //Setter
    void setWords(const vector<Word>& words)
    {
        this -> words = words;
    }

    //Task1
    void loadDictionary(const string fileName);

    //Task2
    void searchWord(const string& userInput);

    //Task3
    void findWords();

    //Task4
    bool wordExists(string userInput);
    void addWordToDictionary(string userInput);
    void writeDictionaryToFile();

};
