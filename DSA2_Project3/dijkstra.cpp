#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "hash.h"
#include "heap.h"
#include "dijkstra.h"
#include "limits.h"
using namespace std;


graph::graph(){
    
}

int graph::insert(string startv, string endv, int weight){
    //cout<<startv<<" "<< endv <<endl;

    bool known1;
    bool known2;

    vertex* vp1 = static_cast<vertex* > (vertices.getPointer(startv , &known1));
    vertex* vp2 = static_cast<vertex* > (vertices.getPointer(endv , &known2));

    //if it does not contain startv or endv
    //insert into the list of vertices and hashtable
    if(known1 == false){
        vp1 = new vertex;
        //cout<< "start:" <<startv<<endl;
        vp1->id = startv;
        vp1->dist = 2000000000;
        data.push_back(vp1);
        //cout<<temp<<endl;
        vertices.insert(startv, vp1);
        //vp1 = data.back();
        //need to get vp to match address that starv was interested in hashtable

    }

    // && (startv.compare(endv) != 0)
    if(known2 == false){
        //cout<< "end: " <<endv<<endl;
        vp2 = new vertex;
        //cout<<startv<<endl;
        vp2->id = endv;
        vp2->dist = 2000000000;
        if ((startv.compare(endv) != 0)){
            data.push_back(vp2);
            //cout<<temp<<endl;
            vertices.insert(endv, vp2);
        }
        //vp2 = data.back();
        //need to get vp to match address that endv was interested in hashtable

    }

    //now give the edge the correct wieght
    edges e;

    e.weight = weight;
    e.pos = vp2; 
    
    vp1->adj.push_back(e);

    //cout<<"h1\n";
    // for(auto i: data){
    //     cout << i->id << endl;
    // }

    //cout << "length: " << data.size() << endl;

    return 0;
}

int graph::dijkstra(string &s){

    heap distances = heap(10000); //contains table of distances for Vs
    for(auto v : data){
        //cout<<"hi\n";
        v->dist = 2000000000;
        v->known = false;
        distances.insert(v->id, v->dist, v);
    }
  
    bool known;
    distances.setKey(s , 0);
    vertex* vp = static_cast<vertex* > (vertices.getPointer(s , &known));
    // ds ← 0
    if(known == false){
        return 1;
    }
    vp->dist = 0;
    //vp->path = vp;
    // ps ← NULL
    //vp->path is already set to NULL
    //insert into heap
    // distances.setKey(s, 0);
    // while there are still unknown vertices
    int pkey;
    vertex* ppData;
    while( !( distances.deleteMin(nullptr, nullptr, &ppData) ) ) {
        //cout<<"hi\n";
        // v ← the unknown vertex with the smallest d-value
        //knownv ← TRUE
        ppData->known = true;
        // for each edge from v to vertex w
        //cout << "1: " <<(ppData->adj.front().pos->id) << endl;
        for(auto i : ppData->adj){
            if( (i.pos->known) == false){
                int newDistance = ppData->dist + i.weight;
                if( (newDistance <= i.pos->dist) ){
                    // dw ← dv + cv,w
                    i.pos->dist = newDistance;
                    // pw ← v
                    i.pos->path = ppData; 
                    distances.setKey(i.pos->id, newDistance);
                }
            }
        }
    }
    return 0;
}


void graph::output(ofstream &outputFile, string startv){
    //example:
    // v1: NO PATH
    // v2: NO PATH
    // v4: NO PATH
    // v5: 0 [v5]
    // v3: NO PATH
    // v6: 7 [v5, v7, v6]
    // v7: 6 [v5, v7]
    
    //go through everything in the list of vertices
    bool b;
    string s;
    list<string> usedV;
    for(auto i : data){
        // bool used = false;
        // used = (std::find(usedV.begin(), usedV.end(), i->id) != usedV.end());
        // //cout << i->id << " " << used << endl;
        // if(used == false) {
            usedV.push_back(i->id);
            //cout<<"hi2\n";
            if(i->dist == 2000000000){
                outputFile << i->id << ": NO PATH\n";
                continue;
            } 
            //cout<<"hi1\n";
            outputFile << i->id << ": ";
            //cout<<i.path<<endl;
            if(i->path == 0){
                outputFile<< "0" <<" [" << startv;

            } else {

                outputFile<< i->dist <<" [";
                vertex* temp = i;
                s.clear();
                s += temp->id;
                while( (temp->path != nullptr) ){

                    temp = temp->path;
                    s = temp->id + ", " + s;
                }
                outputFile << s;
                //outputFile << i->path->id << ", ";
                
            }
            outputFile << "]\n";
        }
}