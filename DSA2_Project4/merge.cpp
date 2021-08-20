#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

char a[1000];
char b[1000];
char c[2000];
int m[2001][2001] = {0};
int main() {

    string inputFile;
    string outputFile;
    // a,b,c originally read in from the given file
    string a1;
    string b1;
    string c1;

    cout << "Enter name of input file: ";
    cin >> inputFile;

    //open
    ifstream inputFileStream(inputFile); 

    // Check if given file exists
    while(!inputFileStream.is_open()){
        cout << "ERROR, INVALID FILE! Please enter an existing file:" << endl;
        cin >> inputFile;
        inputFileStream.open(inputFile);
    }

    cout << "Enter name of output file: ";
    cin >> outputFile;

    ofstream outputFileStream(outputFile);

    while(inputFileStream >> a1 >> b1 >> c1){

        // cout << a1.length() << endl;
        // cout << b1.length()  << endl;
        // cout << c1.length()  << endl;
        
        //initial each of the merge matrix
        m[0][0] = 1;

        if(a1.length() + b1.length() != c1.length()){
            // Easy case when the words do not add up to the same length
            //cout<< "*** NOT A MERGE ***" << endl;
            outputFileStream << "*** NOT A MERGE ***" << endl;

        } else {

            //put each character in a slot in a matrix
            strcpy(a, a1.c_str());
            strcpy(b, b1.c_str());
            strcpy(c, c1.c_str());
            // cout << a1 << " Second letter: " << a[1] << endl; 
            // cout << b1 << " Second letter: " << b[1] << endl; 
            // cout << c1 << " Second letter: " << c[1] << endl;
            
            // end position goal of the matrix, where it should be 1 if a merge
            int xgoal = a1.length();
            int ygoal = b1.length();
            int y = 0;
            int i = 0;
            
            //go through every letter of word c
            while( (i <= c1.length()) ) {
                int x = 0;
                while( x <= i ){
                    y = i - x;
                    // Only  look at where there is a 1 in the matrix
                    if( m[y][x] == 1 ) {
                        // case where c matches a
                        if( c[i] == a[x] ){
                            m[y][x+1] = 1;
                        } 
                        // need to make sure everything is reset to 0 that doesnt match

                        // else {
                        //     m[y][x+1] = 0;
                        // }

                        // case where c matches b
                        if( c[i] == b[y] ){
                            m[y+1][x] = 1;
                        } 

                        // else {
                        //     m[y+1][x] = 0;
                        // }
                        
                    }
                    
                    x++;

                }
                //always move through each letter of word c 
                i++;
            }
            i = c1.length();
            //check if the goal destination is 1 and work my way backwards to capitalize the proper letters
            //cout << "length of word: " << i << endl;
            if(m[ygoal][xgoal] == 1){
                //cout << c << " IS A MERGE!\n";
                i--;    
                while( (i >= 0) ){

                    if(m[ygoal-1][xgoal] == 1 && ygoal != 0){
                        ygoal--;

                    } else if(m[ygoal][xgoal-1] == 1 && xgoal != 0){
                        xgoal--;
                        c[i] = toupper(c[i]);
                    } 
                    i--;
                }

                outputFileStream << c << endl;

            } else {
                //cout << c << " IS NOT A MERGE :(\n";
                outputFileStream << "*** NOT A MERGE ***" << endl;
            }
            
            //remake everything to 0
            for (int i = 0; i < 2001; i++){
                for (int j = 0; j < 2001; j++){
                    m[i][j] = 0;
                }
            }
        }

    }

    //close
    inputFileStream.close();

    outputFileStream.close();

    return 0;
}