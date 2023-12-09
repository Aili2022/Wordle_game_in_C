#pragma once
#include<iostream>
#include<string>

using namespace std;

//Convert a the Word struct into Word class that include getter and setter and constructor;
//Input:
//Output:
//Written by:Aili Lu
//Creation date:02/05/2023
class Word
{
private:
    string name;
    string definition;
    string type;

public:
    //Default constructor
    Word() {}

    //Constructor
    Word(string& name, string& definition, string& type)
    {
        this->name = name; // Assign the value of name to the name member variable of the object. 
        this->definition = definition; // Assign the value of definition to the definition member variable of the object. 
        this->type = type; // Assign the value of type to the type member variable of the object.
    }

    //Getter, use const keyword here as it is in the dictionary method
    string getName() const { return name; }
    string getDefinition() const { return definition; }
    string getType()const { return type; }

    //Setter
    void setName(string& name)
    {
        this->name = name;
    }

    void setDefinition(string& definition)
    {
        this->definition = definition;
    }

    void setType(string& type)
    {
        this->type = type;
    }

    //print function
    void printDefinition() {
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Definition: " << definition << endl;
    }

};
