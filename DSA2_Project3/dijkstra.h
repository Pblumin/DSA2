#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include "hash.h"
#include "heap.h"
#include <fstream>
#include "limits.h"

using namespace std;

class graph{
public:

    class vertex;
    
    //int infinity = 1000001;

    struct edges{
        vertex* pos; //position of vertex (data)
        int weight; // weights
    };

    class vertex{
        public:
        //List adj;
        std::list<edges> adj;
        //bool known;
        bool known = false;
        //DistType dist;
        int dist = 2000000000;
        //2000000000
        //Vertex path;
        vertex* path = nullptr;
        string id;
        //
        //string pathv;
    };

    
    graph();

    int dijkstra(string &s);

    hashTable vertices = hashTable(10000); //contains table of Vs
    
    std::list<vertex*> data;

    int insert(string startv, string endv, int weight); //insert vertexs

    void output(ofstream &outputFile, string startv); //function to give output

};

#endif //_DIJKSTRA_H