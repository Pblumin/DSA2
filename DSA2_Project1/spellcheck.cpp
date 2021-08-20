//still to do/ask theo:
    //rehash function-very confused
    //findPos-basically done but not sure about one thing
    //remove-are u actually supposed to delete something in here?
    //what am I supposed to use getpointer and set pointer for
    //double check insert function; not sure if its right
    //double check read and load functions
    //help running and using cygwin

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include "hash.h"
using namespace std;

//NEED TO WRITE SOMETHING THAT CATCHES LONG WORDS AND THAT ISNT IN THE DICTIONARY
//IF WORD IS GREATER THAN 20 CHARACTERERS SKIP AND OUTPUT MESSAGE
//IF WORD IS NOT IN DICTIONARY OUTPUT ERROR
//WHAT IS NEEDED FOR EACH OF THESE
//NEED TO PARSE WORD BY WORD IN DICTIONARY AND COUNT CHARACTERS OF EACH WORD
//ONCE ERROR IS DETECTED NEED LINE AS WELL
//NEED TO SOMEHOW ACCOUNT FOR SPACES?????
//IDK HOW TO FIGURE OUT WHAT PARAMETERS TO USE

void errorCheck(string word, int line, bool longWord, hashTable* dictionary, ofstream &outputFile){
    longWord = false;
    if (word.size() > 20){
        longWord = true;
        outputFile << "Long word at line " << line <<", starts: " << word << endl;
    } else if (!dictionary -> contains(word) && word != " "){
        outputFile << "Unknown word at line " << line << ": " << word << endl;
    }
}

void load(ifstream &inputFile, hashTable* dictionary, int size){
    string line;
    while (getline(inputFile, line)){
        dictionary -> insert(line, nullptr);
    }
}

//FUNCTION THAT READS THE DOCUMENT TO SPELL CHECK
//NO CLUE AS THEO PLZ HELP :SOB::SOB::SOB::SOB::SOB::SOB::SOB::SOB:
void read(ifstream &inputFile, ofstream &outputFile, hashTable* dictionary){
    string word;
    int linelength;
    string line;
    int size = 0;
    bool longWord = false;
    while (getline(inputFile, line)) {
        ++size;
        for (int i = 0; i < line.length(); i++){
            //figure out how to go one word at a time
            char character = line.at(i);
            if (character == ' '){
                break;
            } else {
                word += character;
            }
            errorCheck(word, linelength, longWord, dictionary, outputFile);
        }
    }
}

int main() {
    string dictionary;
    string inputFile, outputFile;
    
    cout << "Enter name of the dictionary file: ";
    cin >> dictionary;

    clock_t t0, t1;
    //Start timer
    t0 = clock();

    //get file
    ifstream inputFileStream(dictionary);

    int size = 0;
    string line;

    while (getline(inputFileStream, line)){
        ++size;
    }

    cout << "Number of lines in text file: " << size << endl;
    
	hashTable* dictionary1 = new hashTable(size);

    //Need to put words from dictioary file into hashtable
    load(inputFileStream, dictionary1, size);

    inputFileStream.close();

    //stop clock
    t1=clock(); 
    cout << "Total time (in seconds) to load dictionary: " << t1 - t0 << endl;

    cout << "Enter name of input file:  /n";
    cin >> inputFile;

    cout << "Enter name of input file:  /n";
    cin  >> outputFile;

    //Start timer 2
    t0 = clock();

    ifstream inputFileStream2(inputFile);
    ofstream outputFileStream(outputFile);

    //WRITE SOMETHING HERE THAT PROFORMS THE READING OPERATION
    read(inputFileStream2, outputFileStream, dictionary1);

    inputFileStream.close();
    outputFileStream.close();

    //end timer 2
    t1 = clock();

    cout << "Total time (in seconds) to check document: " << t1 - t0 << endl;

    return 0;
}