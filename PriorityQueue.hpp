// NOTE: This is a template class for a PriorityQueue. Any data type can be used but they must support comparison operators (<, >).
// The custom struct emergencyCase will define these comparators based on priority level.
// -------------------------------------------------------------------------------------
#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
using namespace std;
// -------------------------------------------------------------------------------------
template <typename T> // Template's Java equivalent is Generics
class PriorityQueue
{
private:
    T *heap; // Binary tree represented as an array, max-heap (parent nodes are greater than child nodes)
    int capacity;
    int size;

    int parent(int index)
    {
        return (index - 1) / 2; // Automatically rounds down
    }
    int left(int index)
    {
        return 2 * index + 1;
    }
    int right(int index)
    {
        return 2 * index + 2;
    }

    void swap(int i, int j)
    {
        T temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index) // IDK why its called this but everyone uses this name
    { // Repeatedly compare and swap with parent until parent value is less than or equal to current value
        while (index != 0 && heap[parent(index)] < heap[index])
        {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void heapifyDown(int index)
    { // Pop temporarily moves the last element to the root.
        int largest = index;
        int leftChild = left(index);
        int rightChild = right(index);

        if (leftChild < size && heap[leftChild] > heap[largest])
        {
            largest = leftChild;
        }
        if (rightChild < size && heap[rightChild] > heap[largest])
        {
            largest = rightChild;
        }
        if (largest != index)
        {
            swap(index, largest);
            heapifyDown(largest);
        }
    }

public:
    // CONSTRUCTOR & DESTRUCTOR
    PriorityQueue(int cap = 20) // Default capacity is 20
    {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
    }
    ~PriorityQueue()
    {
        delete[] heap;
    } 

    // MEMBER FUNCTIONS
    bool isEmpty()
    {
        return size == 0;
    }

    void push(const T &value) // Insert new element at the end, then restore heap property
    {
        if (size == capacity)
        {
            cout << "Priority Queue is full!" << endl;
            return;
        }
        heap[size] = value;
        heapifyUp(size); // New size - 1 times
        size++;
    }

    T pop() // Return root element, then restore heap property
    {
        if (isEmpty())
        {
            throw runtime_error("Priority Queue is empty!");
        }
        T root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0); // Last element moved to root
        return root;
    }

    // void display()
    // {
    //     if (isEmpty())
    //     {
    //         cout << "Priority Queue is empty!" << endl;
    //         return;
    //     }

    //     for (int i = 0; i < size; i++)
    //     {
    //         cout << heap[i] << " ";
    //     }
    //     cout << endl;
    // }
};

#endif