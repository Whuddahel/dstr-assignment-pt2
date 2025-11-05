#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
using namespace std;
// -------------------------------------------------------------------
template<typename T>
class PriorityQueue {
private:
    T* heap; // Binary tree represented as an array
    int capacity;
    int size;

    int parent(int index) { 
        return (index - 1) / 2; // Automatically rounds down
    }
    int left(int index) {
        return 2 * index + 1;
    }
    int right(int index) {
        return 2 * index + 2;
    }

    void swap(int i, int j) {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index) { // Repeatedly compare and swap with parent until parent value is less than or equal to current value
        while (index != 0 && heap[parent(index)] < heap[index]) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void heapifyDown(int index) { 
        int largest = index;
        int leftChild = left(index);
        int rightChild = right(index);

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        } 
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }
        if (largest != index) {
            swap(index, largest);
            heapifyDown(largest);
        }
    }
};

#endif