#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "hash.h"
#include "heap.h"
#include "dijkstra.h"
#include "limits.h"
using namespace std;

int main (){

    string inputFile;
    string startVertex;
    string outputFile;
    graph g;

    clock_t t1; //start time
    clock_t t2; //end time

    cout << "Enter name of graph file: ";
    cin >> inputFile;

    string line;
    string startv;
    string endv;
    int weight;
    
    //open inputFile
    ifstream inputFileStream(inputFile); 

    list<string> vertices;

    //load the graph in
    while(getline(inputFileStream , line)){
        stringstream var(line);
        var >> startv >> endv >> weight;
        //cout << startv << " " << endv << " " << weight << endl;
        g.insert(startv, endv, weight);
        vertices.push_back(startv);
    }
    //close input file
    inputFileStream.close();

    bool found = false;
    while(found == false){
        cout << "Enter a valid vertex id for the staring vertex: ";
        cin >> startVertex;
        found = (std::find(vertices.begin(), vertices.end(), startVertex) != vertices.end());  
    }

    t1 = clock(); //start

    //do dijkstra
    g.dijkstra(startVertex);

    t2 = clock(); //end

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << ((double) (t2 - t1)) / CLOCKS_PER_SEC << endl;

    cout << "Enter name of output file: ";
    cin >> outputFile;

    //create outputfile
    ofstream outputFileStream(outputFile);

    //output function prints out results to file
    g.output(outputFileStream, startVertex);

    //close output file
    outputFileStream.close();

    return 0;
}