#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "ExtendedDictionary.h"
#include <cstdlib>
#include <memory>
#include <sstream>


using namespace std;

//Task 5
//Create a function that lists all words in the dictionary that are palindromes. e.g .”civic”
//Input: 'words' vector that is inherited from its parent class 'Dictionary'via getter method;
//Output: all words that are palindrome are printed to the console;
//Written by:Aili Lu
//Creation date:03/05/2023
void ExtendedDictionary::listPalindromesWord()
{
    cout << "The word that's palindrome is: " << endl;

    for (const auto& word : getWords()) 
    {
        // a flag to check if the word is a palindrome
        bool isPalindrome = true;

        //initialise i to scan from the begining of the word and j from the end of the word
        int i = 0, j = word.getName().size() - 1;


        while (i < j)
        {
            //if the first letter = last letter, second letter = second last letter, continously.
            if (word.getName()[i] != word.getName()[j])
            {
                isPalindrome = false;
                break;
            }

            i++;
            j--;

        }

       // print the palindrome word
        if (isPalindrome)
        {
            cout <<word.getName() << endl;
        }  
    }
}

//Task 6
//Create a function that prompt the user to enter a word and print all words from the
//dictionary that ends in the same sequence of three letters as the entered word.
//Input:user input
//Output: all words that in the same sequence of three letters that matchs the user input are printed to the console;
//Written by:Aili Lu
//Creation date:05/05/2023
void ExtendedDictionary::findRhymingWords(const string& userInput)
{
    
    string wordSequence = userInput.substr(userInput.length()-3);//substring it from the third last index with the length of 3.

    // A flage to check if the word is a rhyme.
    bool foundRhyme = false;

    //get the last 3 letter of each word's name, if it equals to the wordSequnce, then it is rhymed.
    for (const Word& word : getWords())
    {
        if (word.getName().length() >= 3 && word.getName().substr(word.getName().length() - 3) == wordSequence)
        {
            cout << "The rhyming word is: " << word.getName() <<"\n" <<endl;
            foundRhyme = true;
        }
    }

    if (!foundRhyme)
    {
        cout << "No word is rhymed with " << userInput << "\n" << endl;
    }
}

//Task 7
//Create a function that let the user guess the fourth word of a random word's defintion and preserved the score. 
//Input: user input & the Word vector
//Output:The player's higest score
//Written by:Aili Lu
//Creation date:05/05/2023
void ExtendedDictionary::guessWordGame()
{
    // Initialize the current score
    int currentScore = 0;
    bool quitGame = false;
    

    cout << "********************************************************" << endl;
    cout << "       Welcome to the guess the fourth word game        " << endl;
    cout << "********************************************************" << endl;

    cout << "Highest Score: " << getHighestScore() << "\n\n";

    while (!quitGame)
    {
        // Generate a random word in the vector
        vector<string> definitionWords;
        srand(time(nullptr)); //seed, make sure that each time a new word in generated.
        Word randWord; //random word that generates from the word vector


        //generate a new word until the length of the 4th word in definition is more than 4.
        do
        {
            definitionWords.clear();//clear the buffer
            int randIndex = rand() % getWords().size();
            randWord = getWords()[randIndex];
            string definition = getWords()[randIndex].getDefinition();
            
            //split the definition into words and store it in a vector
            istringstream iss(definition);
            string word;
            while (iss >> word)
            {
                //convert the definition word to lowercase
                transform(word.begin(), word.end(), word.begin(),
                    [](unsigned char c) { return tolower(c); });

                definitionWords.push_back(word);
            }

        } while (definitionWords.size() < 4);

        //A copy of the definition vector to store the definition that has changed to underscore
        vector<string>definitionWordsCopy = definitionWords;
        
        //the missing word, run a for loop to check if there is special character in it, if so remove it for later comparison
        string missingWord = definitionWords[3];

        string specialChar = ";-,.!?";

        for (char c : specialChar) 
        {
            missingWord.erase(remove(missingWord.begin(), missingWord.end(), c), missingWord.end());
        }

        // Replace the copy of new missing word(no speacial char)with underscores
        string& word = missingWord;
        string result;
         for (char c : word) 
         {
             result += '_';
             result += ' ';//this is for user to count how many letters are missing easier with white space between each underscore.
         }
         definitionWordsCopy[3] = result;
      
        // Print the word and the definition with the fourth word replaced by underscores
        cout << "The word is : " << randWord.getName() << endl;
        cout << "The definition of the word is: " << "\n" << endl;
        for (const string& w : definitionWordsCopy)
        {
            cout << w << " ";
        }
        
        cout << "\n" << endl;


        // Get the user's guess
        string userGuess;
        cout << "Enter your guess for the missing word in the definition:" << endl;
        cin >> userGuess;
        

        // Check if the guess is correct
        if (userGuess == missingWord)
        {
            cout << "Congratulations, you guessed correctly! You've earned 10 marks!" << "\n"<< endl;
            currentScore += 10;

            //Compare to the highest score
            if (currentScore > getHighestScore())
            {
                setHighestScore(currentScore);

                cout << "WOW! you beat the highest score, the new high score: " << getHighestScore() << "\n"<< endl;
            }

            quitGame = false; // start new iteration   
        }

        else
        {
            cout << "Sorry, the correct word is: " << missingWord << endl;
            cout << "Your score is: " << currentScore << endl;
            cout << "See you next time!" <<"\n"<< endl;

            quitGame = true;

        }

    }

}


//Task 8
//Create a function to help the user to cheat at Searchdle, in another word, find the mystery word in our dictionary
//Input:user input and a copy of word vector
//Output:The user's higest score
//Written by:Aili Lu
//Creation date:09/05/2023
void ExtendedDictionary::cheatAtSearchdle()
{
    //Initiate a copy of Word vector, to use the function to find the mystery that exits in the dictionary
    //update the eligble words in the vector(aka remove the non-correct words), print the only eligble word

    vector<Word> copyWords;
    copyWords = getWords();//copy the words from the word vector

    //write a header and instruction
    cout << "********************************************************" << endl;
    cout << "       Welcome to the searchdle cheat program        " << endl;
    cout << "********************************************************" << "\n"<< endl;
    cout << "The game starts with opening the website provided below, press 'Get New Word'.\n" << endl;
    cout << "The website would display a metrix which the row indicates the length of the word.\n" << endl;
    cout << "Follow the steps below to find the mystery word!\n" << endl;
    cout << "The website: https://wtfseo.com/searchdle/" << "\n\n" << endl;


    //"a" function that prompt the user to enter the length of the word.
    //Remove the words that does not match the length
    int wordLength;
    while (true)
    {
        cout << "Enter the length of the word(less than 50): " << endl;
        cin >> wordLength;

        if (!cin.fail() && wordLength > 0 && wordLength < 50) { break; }//valid input

        else
        { 

            cout << "Invalid input. Please an integer to indicate the length of the word. " << endl; 
            //clear if there any remaining value in the input buffer
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }


    }
    //remove the word that is not the specified length
    copyWords.erase(remove_if(copyWords.begin(), copyWords.end(), [wordLength](const Word& word) 
    {
        return word.getName().length() != wordLength; 

    }), copyWords.end());

    //display the eligible words
    cout << "The word that matchs the length is: "<< copyWords.size() << " words.\n" << endl;

    //if there is no matching words in the dictionary
    if (copyWords.size() == 0) 
    {
        cout << "There is no matching words, please go back to the previous menu.\n" << endl;
    }

    string greyLetters;
    string yellowLetters;

    while (true)
    { 
        int option;
        cout << "*This is an ongoing step, go back to the website, choose random letters into the matrix, input them into the program.\n" << endl;
        cout << "*After entering all the letter set of the row, continue trying inputing new letter in the next row of the matrix.\n" << endl;
        cout << "*You can select 4) to display the potiential words to enter into the matrix.\n" << endl;
        cout << "Please select from the following options:  " << endl;
        cout << "1) Input grey letters." << endl;
        cout << "2) Input yellow letters." << endl;
        cout << "3) Input green letters." << endl;
        cout << "4) Display potential words." << endl;
        cout << "5) Return to main menu." << endl;

       
        cin >> option;

        //"b" function that prompt the user to enter a 'set' of grey letters, iterate throught the specified string and the word string.
        // if anywords that contains that set of letters, remove it from the vector
        if (option == 1)
        {
            //to make sure the user input is valid.
             while(true)
             {
                cout << "Enter all the grey letter below(whitespaces excluded): " << endl;
                cin>>greyLetters;

                if (!greyLetters.empty() && !(greyLetters.find_first_not_of(' ') == string::npos)) { break; }
               
                else
                { 
                    cout << "Invalid input. Please enter a(some) letter(s): " << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
             }
            //Convert the letter into lowercase;
            transform(greyLetters.begin(), greyLetters.end(), greyLetters.begin(),
                [](unsigned char c) { return tolower(c); });

            //if any words in the vector contain any letters this set of letters, remove it from the copyWord vector
            copyWords.erase(
                remove_if(
                    copyWords.begin(), copyWords.end(), [greyLetters](const Word& word)
                    {
                        const string& wordName = word.getName();
                        return any_of(greyLetters.begin(), greyLetters.end(), [&wordName](char c)
                            {
                                return wordName.find(c) != string::npos;
                            });

                    }), copyWords.end());

            //display the number of eligible words
            cout << "The number of matching words are: " << copyWords.size() <<" words.\n" << endl;

           //if there is no matching words in the dictionary
            if (copyWords.size() == 0)
            {
               cout << "There is no matching words, please go back to the previous menu.\n" << endl;
            }

            continue;
        }

       
        else if (option == 2)
        {
            //to make sure the user input is valid.
            while (true)
            {
                cout << "Enter all the yellow letter below(whitespaces excluded): " << endl;
                cin>>yellowLetters;

                if (!yellowLetters.empty() && !(yellowLetters.find_first_not_of(' ') == string::npos)) { break; }
                else 
                {
                    cout << "Invalid input. Please enter a(some) letter(s): " << endl; 
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            //Convert the letter into lowercase;
            transform(yellowLetters.begin(), yellowLetters.end(), yellowLetters.begin(),
                [](unsigned char c) { return tolower(c); });

            //remove the word that has the specified letters
            copyWords.erase(
                remove_if(
                    copyWords.begin(), copyWords.end(), [yellowLetters](const Word& word)
                    {
                        const string& wordName = word.getName();
                        return none_of(yellowLetters.begin(), yellowLetters.end(), [&wordName](char c)
                            {
                                return wordName.find(c) != string::npos;
                            });

                    }), copyWords.end());

            //display the number of eligible words
            cout << "The number of matching words are: " << copyWords.size() << " words.\n" << endl;
            
            //if there is no matching words in the dictionary
            if (copyWords.size() == 0)
            {
            cout << "There is no matching words, please go back to the previous menu.\n" << endl;
            }

            continue;
        }


        else if (option == 3)
        {
            int inputCount;
        
            while(true)
            {
                cout << "How many green letters have shown: " << endl;
                if (cin >> inputCount) { break; }//valid input

                else 
                {
                    cout << "Invalid input, please enter only integer: \n" << endl;
                    // clear any remaining value in the input buffer
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            for (int i = 0; i < inputCount; i++)
            {
                string letter;
                //to make sure the user input is valid.
                while (true)
                {
                    cout << "Enter the green letter below(one by one): " << endl;
                    cin >> letter;

                    if (letter.size() == 1 && !letter.empty() && !(letter.find_first_not_of(' ') == string::npos)) { break; } // valid input

                    else
                    { 
                        cout << "Invalid input. Please enter one letter: " << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                //Convert the letter into lowercase;
                transform(letter.begin(), letter.end(), letter.begin(), [](char& c) {
                    return tolower(c);
                    });

                string position;
                int wordPosition = 0;

                while (true) 
                {
                    cout << "Enter an integer that indicates the letter position: " << endl;
                    cin >> position;

                    if (isdigit(position[0]) && position.size() == 1 && !position.empty() && !(position.find_first_not_of(' ') == string::npos))
                    { 
                        // valid input, convert it to an int
                        wordPosition = stoi(position);
                        cout <<"The first "<< wordPosition << endl;

                        break; 
                    }

                    else 
                    { 
                        cout << "Invalid input. Please enter one integer: " << endl; 
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    }
                
                }

                cout << "The second  " << wordPosition << endl;

                // check if certain letter in certain position in a word, if not then remove it
                copyWords.erase(remove_if(copyWords.begin(), copyWords.end(), [&](const Word& word)
                    {
                        const string& wordName = word.getName();
                        
                        return wordName.substr(wordPosition-1, 1) != letter;
                    }), 
                    
                    copyWords.end());

                //This is just for testing purpose whether the vector has been modified correctly
                cout << "The number of matching words are: " << copyWords.size() << " words.\n" << endl;
                continue;
            }
              //if there is no matching words in the dictionary
              if (copyWords.size() == 0)
              {
                cout << "There is no matching words, please go back to the previous menu.\n" << endl;
               }
        }


        else if (option == 4)
        {
            for (auto word : copyWords)
            {
            cout << "The potential word is: " << word.getName() << "" << "\n" << endl;
            }
            
        }

        else if(option == 5) 
        {
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

}