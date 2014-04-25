#ifndef HEAP_H
#define HEAP_H
#include <QDebug>
#include <QString>
#include "HeapADT.h"

using namespace std;

template <typename E> class Heap {

private:
    E * content; // Pointer to the heap array
    int maxsize; // Maximum size of the array
    int n; // Number of elements now in the content
    // Helper function to put element in its correct place
    void heapfy(int pos) {
        while (!isLeaf(pos)) { // Stop if pos is a leaf
            int target = left(pos);
            int rc = right(pos);
            if ((rc < n) && prior(content[rc], content[target])) {
                target = rc;
            }
            if (prior(content[pos], content[target])) {
                return; // Done
            }
            swap(content, pos, target);
            pos = target; // Move down
        }
    }

public:
    Heap(E * h, int num = 0, int max = 1) {// Constructor
         content = h;
         n = num;
         maxsize = max;
         buildMaxHeap();
    }

    bool prior (E * c1, E * c2) {
        return (c1 >= c2);
    }

    int size() const{
         return n;
    }

    bool isLeaf(int pos) const{ // True if pos is a leaf
        return (pos > n/2) && (pos < n);
   }
    int left(int pos) const{
        if(!isLeaf((pos))){
        return 2*pos + 1;
        }else{
        return 0;
        }
    }

    int right(int pos) const{
        if(!isLeaf(pos)){
            return 2*pos + 2;
        }else{
        return 0;
        }
        // Return right position
    }

    int parent(int pos) const{// Return parent position
        if(pos!=0){
            return (pos-1)/2;
        }else{
            return 0;
        }

    }

    void buildMaxHeap() {// Heapify contents of Heap
        for (int i=n/2-1; i>=0; i--) {
            heapfy(i);
        }
    }

    // Insert "it" into the heap
    void insert(const E& it){
        if (n > maxsize) {
            qDebug() << "Heap is full";
            return;
        }
        int curr = n++;
        content[curr] = it; // Start at end of heap

        while ((curr!=0) && (prior(content[curr], content[parent(curr)]))) {
            swap(content, curr, parent(curr));
            curr = parent(curr);
        }
    }

    // Remove first value
    E removefirst(){
        if (n < 0) {
            qDebug() << "Heap is empty";
            return;
        }
        swap(content, 0, n--); // Swap first with last value
        if (n != 0) heapfy(0); // Siftdown new root val
        return content[n]; // Return deleted value
    }

    // Remove and return element at specified position
    E remove(int pos){
        if((pos < 0) && (pos >= n) ) {
            qDebug() << "Bad position";
            return;
        }
        if (pos == (n-1)) {
            n--; // Last element, no work to do
        }
        else {
            swap(content, pos, n--); // Swap with last value
            while ((pos != 0) && (prior(content[pos], content[parent(pos)]))) {
                swap(content, pos, parent(pos)); // Push up large key
                pos = parent(pos);
            }
            if (n != 0) heapfy(pos); // Push down small key
        }
        return content[n];
    }



};

#endif // HEAP_H

