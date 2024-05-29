//
// Created by Usuario on 29/05/2024.
//
#include <iostream>
#include <vector>

using namespace std;

// Estructura para manejar pares de (número de soldados, índice de fila)
struct Pair {
    int soldiers;
    int index;
};

// Implementación de un heap mínimo
class MinHeap {
public:
    MinHeap(int capacity) {
        size = 0;
        this->capacity = capacity;
        heap = new Pair[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(Pair p) {
        if (size == capacity) {
            return; // No insert if heap is full
        }
        heap[size] = p;
        int current = size;
        size++;
        // Bubble up
        while (current > 0 && compare(heap[current], heap[parent(current)])) {
            swap(&heap[current], &heap[parent(current)]);
            current = parent(current);
        }
    }

    Pair extractMin() {
        if (size == 0) {
            return {0, 0}; // Return a default value if heap is empty
        }
        Pair root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }

private:
    Pair* heap;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

    void swap(Pair* x, Pair* y) {
        Pair temp = *x;
        *x = *y;
        *y = temp;
    }

    bool compare(Pair p1, Pair p2) {
        if (p1.soldiers == p2.soldiers) {
            return p1.index < p2.index;
        }
        return p1.soldiers < p2.soldiers;
    }

    void heapify(int i) {
        int l = leftChild(i);
        int r = rightChild(i);
        int smallest = i;
        if (l < size && compare(heap[l], heap[i])) {
            smallest = l;
        }
        if (r < size && compare(heap[r], heap[smallest])) {
            smallest = r;
        }
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            heapify(smallest);
        }
    }
};

// Función para contar el número de soldados (1's) en una fila
int countSoldiers(const vector<int>& row) {
    int count = 0;
    for (int val : row) {
        if (val == 1) {
            count++;
        }
    }
    return count;
}

vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
    int m = mat.size();
    MinHeap minHeap(m);

    // Rellenar el heap con el conteo de soldados y el índice de cada fila
    for (int i = 0; i < m; ++i) {
        int soldiers = countSoldiers(mat[i]);
        minHeap.insert({soldiers, i});
    }

    // Extraer las k filas más débiles
    vector<int> weakestRows;
    for (int i = 0; i < k; ++i) {
        Pair p = minHeap.extractMin();
        weakestRows.push_back(p.index);
    }

    return weakestRows;
}

int main() {
    vector<vector<int>> mat = {
            {1, 1, 0, 0, 0},
            {1, 1, 1, 1, 0},
            {1, 0, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {1, 1, 1, 1, 1}
    };
    int k = 3;

    vector<int> result = kWeakestRows(mat, k);

    // Imprimir los resultados
    for (int idx : result) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}

