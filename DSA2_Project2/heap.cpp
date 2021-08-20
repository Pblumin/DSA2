#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "heap.h"
#include <fstream>
using namespace std;



heap::heap(int size):mapping(size*2) {

    capacity = size;
    data.resize(size + 1);
    filled = 0;

}

bool heap::isEmpty( ) {    
    // Heap is empty if only 
    return filled == 0;
}


int heap::insert(const std::string &id, int key, void *pv){
  //
  // insert - Inserts a new node into the binary heap
  //
  // Inserts a node with the specified id string, key,
  // and optionally a pointer.  They key is used to
  // determine the final position of the new node.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is already filled to capacity
  //   2 if a node with the given id already exists (but the heap
  //     is not filled to capacity)
    //cout << "hello";

    if (capacity == filled){
        return 1;
    }

    if (mapping.contains(id)){
        return 2;
    }

    filled++;
    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    mapping.insert(id, &data[filled]); //insert into hashtable

    percolateUp(filled);
    //bool b;

    //cout<< "pointer: " << mapping.getPointer(id, &b)<< endl;

    //cout << "pos: " << getPos(static_cast<node *> (mapping.getPointer(id, &b))) <<endl;

    //getHeap();
    return 0;

}

int heap::setKey(const std::string &id, int key){
  //
  // setKey - set the key of the specified node to the specified value
  //
  // I have decided that the class should provide this member function
  // instead of two separate increaseKey and decreaseKey functions.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist

    //cout<<"hello";
    bool b;
    //cout<<"hello";
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    //cout<<"hello";
    if(b == false){
        return 1;
    }

    //cout<<"hello";

    int position = getPos(pn);

    //cout<< position;
    //cout<< " ";
    //cout<< data.size();
    //cout<< std::endl;

    data[0] = data[position]; //start
    data[position].key = key;

    if(data[0].key > key){
        percolateUp(position);
    }

    if(data[0].key < key){
        percolateDown(position);
    }

    return 0;
}

int heap::deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData){
  //
  // deleteMin - return the data associated with the smallest key
  //             and delete that node from the binary heap
  //
  // If pId is supplied (i.e., it is not nullptr), write to that address
  // the id of the node being deleted. If pKey is supplied, write to
  // that address the key of the node being deleted. If ppData is
  // supplied, write to that address the associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if the heap is empty
  //

    if ( filled == 0 ){
        return 1;
    }

    int start = 1;
    data[0] = data[start];


    if (pId != nullptr){
        *pId = data[0].id;
    }

    if (pKey != nullptr){
        *pKey = data[0].key;
    }

    if(ppData != nullptr){
        *(static_cast<void **> (ppData)) = data[0].pData;
    }  


    data[start] = data[filled--];

    mapping.remove(data[0].id);
    percolateDown(start);

    return 0;

}

int heap::remove(const std::string &id, int *pKey = nullptr, void *ppData){
      //
  // remove - delete the node with the specified id from the binary heap
  //
  // If pKey is supplied, write to that address the key of the node
  // being deleted. If ppData is supplied, write to that address the
  // associated void pointer.
  //
  // Returns:
  //   0 on success
  //   1 if a node with the given id does not exist
  //
    bool b;

    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    
    if(b == false){
        return 1;
    }

    int position = getPos(pn);
    data[0] = data[position]; //start

    mapping.setPointer(data[position].id, &data[position]);

    if (pKey != nullptr){
        *pKey = data[position].key;
    }

    if(ppData != nullptr){
        *(static_cast<void **> (ppData)) = data[1].pData;
    }

    int lowest = data[1].key;

    setKey(id, lowest-1);

    //deleteMin(lowest, key, ppData);
    percolateDown(1);

    data[0] = data[1];
    data[1] = data[filled--];

    mapping.remove(data[0].id);
    percolateDown(1);

    return 0;

}

void heap::percolateUp(int posCur){

    data[0] = data[posCur];

    for( ; posCur > 1; posCur/=2) {
        if (data[0].key < data[posCur/2].key){
            data[posCur] = data[posCur/2];
        } else {
            break;
        }
        mapping.setPointer(data[posCur].id, &data[posCur]);
    }

    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);

    //cout<< data[posCur].id << endl;
    //cout << &data[posCur] << endl;
}

void heap::percolateDown(int posCur){
    int child;
    //int tmp;
    //posCur = data[posCur].key;
    data[0] = data[posCur];

    for( ; posCur * 2 <= filled; posCur = child ) {
        child = posCur * 2;
        if( child != filled && data[child + 1].key < data[child].key ){
            child++;
        }
        if( data[child].key < data[posCur].key ){

            data[posCur] = data[child];
            mapping.setPointer(data[posCur].id, &data[posCur]);

        } else {
            break;
        }
    }

    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn){

  int pos = pn - &data[0];
  return pos;

}