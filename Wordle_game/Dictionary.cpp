#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

//Create a function that loads and parse a dictionary file into an instance of Word struct called Dictionary;
//Input: a file of dictionary words
//Output: vector of words of Word class that made from file;
//Written by:Aili Lu
//Creation date:18/03/2023
//Modified date: 02/05/2023
void Dictionary::loadDictionary(const string fileName)
{

    words.clear(); //this is to ensure that the old dictionary is cleared before loading in a new one.

    ifstream file(fileName);
    if (file.is_open())
    {
        cout << "The file " << fileName << " is loading..." << "\n" << endl;

        string line;
        string skipWord = "<word>";

        while (getline(file, line))
        {

            if (line.find(skipWord) == 0)
            {
                Word word;
                getline(file, line);
                word.setName(line);
                getline(file, line);
                word.setDefinition(line);
                getline(file, line);
                word.setType(line);
                words.push_back(word);
            }
        }

        file.close();

        cout << "The file " << fileName << " is loaded in successfully!" << "\n" << endl;
    }

    else
    {
        cout << "dictionary not loaded..." << "\n" << endl;
    }

}

//create a function that finds the matching word in the dictionary vetor and print its type and definition ;
//the function taking in two parameters, one is user input, the other is the dictionary to iterate through;
//Input: the user input and the dictionary 
//Output: the word that is matched with the user input
//Written by:Aili Lu
//Creation date:23/03/2023
//Modified date: 02/05/2023
void Dictionary::searchWord(const string& userInput) // the reference variables using const to make sure the data is read only.
{


    bool wordFound = false; // initialize the variable with an valid value;
    for (const Word& word : words)
    {

        if (word.getName() == userInput) // check if the input matches the name fields of the dictionary
        {
            wordFound = true;
            string newType; // a variable holds the new value of the type.

            //print name, converted type and definition of the word.
            cout << "\n" << word.getName() << endl;

            if (word.getType() == "n")
            {
                newType = "[noun]";
                cout << newType << endl;
            }
            if (word.getType() == "v")
            {
                newType = "[verb]";
                cout << newType << endl;
            }
            if (word.getType() == "adv")
            {
                newType = "[adverb]";
                cout << newType << endl;
            }
            if (word.getType() == "adj")
            {
                newType = "[adjective]";
                cout << newType << endl;
            }
            if (word.getType() == "prep")
            {
                newType = "[preposition]";
                cout << newType << endl;
            }
            if (word.getType() == "misc")
            {
                newType = "[miscellaneous]";
                cout << newType << endl;
            }
            if (word.getType() == "pn")
            {
                newType = "[proper noun]";
                cout << newType << endl;
            }
            if (word.getType() == "n_and_v")
            {
                newType = "[noun and verb]";
                cout << newType << endl;
            }

            cout << word.getDefinition() << "\n" << endl;

            break;
        }
    }

    if (!wordFound)
    {
        cout << "Word not found." << "\n" << endl;

    }

}


//create a function that find a word that contain more that three 'z' and print it to the console.
//Input: The copy of Dictionary 
//Output: the word that have three or more 'z'. 
//Written by:Aili Lu
//Creation date:23/03/2023
//Modified date: 02/05/2023
void Dictionary::findWords()
{
    //looping throught the whole dictionary, find names with more than three 'z' s.
    for (int i = 0; i < words.size(); i++)
    {
        int countZ = 0;
        //looping througt the each characters in the name.
        for (int j = 0; j < words[i].getName().length(); j++)
        {

            if (words[i].getName()[j] == 'z')
            {
                countZ++;
            }
        }

        if (countZ >= 3)
        {
            cout << "The word is: " << words[i].getName() << "\n" << endl;
        }
    }
}

//Task 4 
//Create three function that allow user to add a new word;
//First function check whether the word is existed in the dictionary which return a boolean value;
//Second function allow user to add this word into a new dictionary if the first function return false;
//Third function to write the new dictionary into file;
//input:Dictionary, user input;
//output: New file with extended Dictionary
//Written by:Aili Lu
//Creation date:28/03/2023
//Modified date: 02/05/2023
bool Dictionary::wordExists(string userInput)
{
    for (auto& word : words)
    {
        if (word.getName() == userInput)
        {
            return true;
        }
    }
    return false;
}


void Dictionary::addWordToDictionary(string userInput)
{

    string name, definition, type;
    name = userInput;
    getline(cin, userInput);
    cout << "Enter the definition of the word: " << endl;
    getline(cin, definition);

    //Validating the types input
    bool isValidType = false;
    while (!isValidType)
    {
        cout << "Choose the type of the word(n->Noun, v->Verb, adv->Adverb, adj->adjective, " << endl;
        cout << "prep->preposition, misc->miscellaneous, pn->proper noun, n_and_v->nounand verb):  " << endl;
        getline(cin, type);


        //turn the input in lowercase!!
        transform(type.begin(), type.end(), type.begin(),
            [](unsigned char c) { return tolower(c); });

        if (type == "n" ||
            type == "v" ||
            type == "adv" ||
            type == "adj" ||
            type == "prep" ||
            type == "misc" ||
            type == "pn" ||
            type == "n_and_v")
        {
            isValidType = true;
            break;
        }

        else
        {
            cout << "Invaild type input, please enter again!" << "\n" << endl;
            continue;
        }
    }

    if (wordExists(userInput))
    {
        cout << "Error: word exists, elevated privileges required to edit existing words." << "\n" << endl;
        return;
    }


    Word newWord;
    newWord.setName(name);
    newWord.setDefinition(definition);
    newWord.setType(type);
    words.push_back(newWord);

    cout << "The word added to dictionary successfully!" << "\n" << endl;

}

void Dictionary::writeDictionaryToFile()
{
    string fileName;
    cout << "Enter the name for the new dictionary file: " << endl;
    getline(cin, fileName);
    //Convert the user input to lowercase;
    transform(fileName.begin(), fileName.end(), fileName.begin(),
        [](unsigned char c) { return tolower(c); });

    //make the file a txt document;
    fileName.append(".txt");

    ofstream outFile(fileName);
    if (!outFile)
    {
        cout << "Error: Unable to create a new dictionary file." << "\n" << endl;
        return;
    }

    string frontWordTag = "<word>";
    string endWordTag = "</word>";

    for (auto& word : words)
    {
        outFile << frontWordTag << endl
            << word.getName() << endl
            << word.getDefinition() << endl
            << word.getType() << endl
            << endWordTag << endl;
    }

    outFile.close();
    cout << "The file " << fileName << " has created!" << "\n" << endl;
}

