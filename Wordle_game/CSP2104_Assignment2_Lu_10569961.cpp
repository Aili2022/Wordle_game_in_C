// CSP2104_Assignment2_Lu_10569961.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "ExtendedDictionary.h"


using namespace std;

int main()
{
    string fileName;
    ExtendedDictionary myDictionary;
    ifstream file;

    cout << "********************************************************" << endl;
    cout << "          Welcome to the Word Dictionary Panel           " << endl;
    cout << "********************************************************" << endl;

    //The main menu;
    //Provide menu options until user tempts to exit the program;
    while (true)
    {
        int option;
        cout << "Please select from the following options:  " << endl;
        cout << "1) Load a dictionary." << endl;
        cout << "2) Enter a word to find a match dictionary." << endl;
        cout << "3) Find all words that contain more than three 'z' characters in them." << endl;
        cout << "4) Add a word to the dictionary." << endl;
        cout << "5) List all the words that are palindromes." << endl;
        cout << "6) Find rhyming words." << endl;
        cout << "7) Guess the fourth word." << endl;
        cout << "8) Cheat on Searchdle. " << endl;
        cout << "9) Exit the program." << endl;

        cin >> option;

        if (option == 1)
        {
            while (true)
            {
                cout << "Please enter a file name or enter 'd' as default file:  " << endl;
                cin >> fileName;


                //Convert the user input to lowercase with '.txt' append in the end;
                transform(fileName.begin(), fileName.end(), fileName.begin(),
                    [](unsigned char c) { return tolower(c); });

                //default file
                if (fileName == "d")
                {
                    fileName = "dictionary_2023S1";
                }

                fileName.append(".txt");

                file.open(fileName);

                if (file.is_open()) //if the file open successfully then break out of loop
                {
                    break;
                }
                else
                {
                    //file is not valid, close the stream and try again
                    file.close();
                    cout << "Invaild file! Please try again." << endl;
                }
            }

            myDictionary.loadDictionary(fileName);

        }


        else if (option == 2)
        {
            string userInput;
            cout << "Enter a word: " << endl;
            cin >> userInput;

            //Convert the user input to lowercase;
            transform(userInput.begin(), userInput.end(), userInput.begin(),
                [](unsigned char c) { return tolower(c); });

            myDictionary.searchWord(userInput);

        }

        else if (option == 3)
        {
            myDictionary.findWords();

        }

        else if (option == 4)
        {
            string userInput;
            cout << "Enter a word: " << endl;
            cin >> userInput;

            //Convert the user input to lowercase;
            transform(userInput.begin(), userInput.end(), userInput.begin(),
                [](unsigned char c) { return tolower(c); });

            myDictionary.addWordToDictionary(userInput);
            myDictionary.writeDictionaryToFile();

        }
          
        else if (option == 5)
        {
           myDictionary.listPalindromesWord();
        }



        else if (option == 6)
        {   
            while (true)
            {
                string userInput;
                cout << "Enter a word with more than 3 letters: " << endl;
                cin >> userInput;

                //to check if the user enter only alphabectial input
                bool isAlphabecical = true;

                for (char c : userInput) 
                {
                    if (!isalpha(c)) 
                    {
                        isAlphabecical = false;
                        break;
                    }
                }

                if (userInput.length() >= 3 && isAlphabecical)
                {
                    //Convert the user input to lowercase;
                    transform(userInput.begin(), userInput.end(), userInput.begin(),
                        [](unsigned char c) { return tolower(c); });

                    myDictionary.findRhymingWords(userInput);

                    break;
                }

                else
                {
                    cout << "Invalid input, please enter a word with more than 3 alphabetical letters." << endl;
                }
            }
        }

        else if (option == 7) 
        {
            myDictionary.guessWordGame();
        }

        else if (option == 8)
        {
            myDictionary.cheatAtSearchdle();
        }

        
        else if (option == 9)
        {
            cout << "Good bye!" << endl;
            break;
        }

        //Catch all other input other than the desired inputs
        //and uses continue to go back to the beginning of the loop and prompt the user again.
        else
        {

            cout << "Invaild input, Please enter an integer within the options." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;

        }
    }

    return 0;
}

