//
// Created by Usuario on 29/05/2024.
//
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Estructura de un heap máximo
class MaxHeap {
public:
    MaxHeap(int capacity) : capacity(capacity), size(0) {
        heap = new int[capacity];
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void insert(int value) {
        if (size == capacity) return;
        heap[size] = value;
        int current = size;
        size++;
        while (current > 0 && heap[current] > heap[parent(current)]) {
            swap(heap[current], heap[parent(current)]);
            current = parent(current);
        }
    }

    int extractMax() {
        if (size == 0) return -1;
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }

    int getMax() {
        return size > 0 ? heap[0] : -1;
    }

    int getSize() {
        return size;
    }

private:
    int* heap;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }

    void heapify(int i) {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        if (left < size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
};

// Estructura de un heap mínimo
class MinHeap {
public:
    MinHeap(int capacity) : capacity(capacity), size(0) {
        heap = new int[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(int value) {
        if (size == capacity) return;
        heap[size] = value;
        int current = size;
        size++;
        while (current > 0 && heap[current] < heap[parent(current)]) {
            swap(heap[current], heap[parent(current)]);
            current = parent(current);
        }
    }

    int extractMin() {
        if (size == 0) return -1;
        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }

    int getMin() {
        return size > 0 ? heap[0] : -1;
    }

    int getSize() {
        return size;
    }

private:
    int* heap;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }

    void heapify(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

class MedianFinder {
public:
    MedianFinder() : maxHeap(50000), minHeap(50000) {}

    void addNum(int num) {
        if (maxHeap.getSize() == 0 || num <= maxHeap.getMax()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }

        if (maxHeap.getSize() > minHeap.getSize() + 1) {
            minHeap.insert(maxHeap.extractMax());
        } else if (minHeap.getSize() > maxHeap.getSize()) {
            maxHeap.insert(minHeap.extractMin());
        }
    }

    double findMedian() {
        if (maxHeap.getSize() > minHeap.getSize()) {
            return maxHeap.getMax();
        } else {
            return (maxHeap.getMax() + minHeap.getMin()) / 2.0;
        }
    }

private:
    MaxHeap maxHeap;
    MinHeap minHeap;
};

int main() {
    vector<string> commands = {"MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"};
    vector<vector<int>> inputs = {{}, {1}, {2}, {}, {3}, {}};

    MedianFinder* medianFinder = nullptr;
    vector<string> output;

    for (size_t i = 0; i < commands.size(); ++i) {
        if (commands[i] == "MedianFinder") {
            medianFinder = new MedianFinder();
            output.push_back("null");
        } else if (commands[i] == "addNum") {
            medianFinder->addNum(inputs[i][0]);
            output.push_back("null");
        } else if (commands[i] == "findMedian") {
            double median = medianFinder->findMedian();
            ostringstream ss;
            ss.precision(5);
            ss << fixed << median;
            output.push_back(ss.str());
        }
    }

    // Imprimir el resultado en el formato esperado
    cout << "[";
    for (size_t i = 0; i < output.size(); ++i) {
        cout << output[i];
        if (i < output.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    delete medianFinder;
    return 0;
}
