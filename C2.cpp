//
// Created by Usuario on 29/05/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para manejar los eventos
struct Event {
    int startTime;
    int endTime;
    int value;
};

// Implementación de un heap mínimo
class MinHeap {
public:
    MinHeap(int capacity) {
        size = 0;
        this->capacity = capacity;
        heap = new Event[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(Event event) {
        if (size == capacity) {
            return; // No insert if heap is full
        }
        heap[size] = event;
        int current = size;
        size++;
        // Bubble up
        while (current > 0 && compare(heap[current], heap[parent(current)])) {
            swap(&heap[current], &heap[parent(current)]);
            current = parent(current);
        }
    }

    Event extractMin() {
        if (size == 0) {
            return {0, 0, 0}; // Return a default value if heap is empty
        }
        Event root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);
        return root;
    }

    Event getMin() {
        if (size == 0) {
            return {0, 0, 0}; // Return a default value if heap is empty
        }
        return heap[0];
    }

    int getSize() {
        return size;
    }

private:
    Event* heap;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

    void swap(Event* x, Event* y) {
        Event temp = *x;
        *x = *y;
        *y = temp;
    }

    bool compare(Event e1, Event e2) {
        return e1.endTime < e2.endTime;
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

// Función para maximizar la suma de valores de eventos seleccionados
int maxTwoEvents(vector<Event>& events) {
    // Ordenar eventos por su hora de finalización
    sort(events.begin(), events.end(), [](Event e1, Event e2) {
        return e1.endTime < e2.endTime;
    });

    // Heap para mantener los eventos seleccionados
    MinHeap heap(events.size());

    int max_value = 0;
    int current_max_value = 0;

    for (Event event : events) {
        // Remover los eventos del heap que terminan antes de que comience el evento actual
        while (heap.getSize() > 0 && heap.getMin().endTime < event.startTime) {
            current_max_value = max(current_max_value, heap.extractMin().value);
        }

        // Evaluar el valor combinado de seleccionar el evento actual y el mejor evento anterior no solapado
        max_value = max(max_value, current_max_value + event.value);

        // Insertar el evento actual en el heap
        heap.insert(event);
    }

    return max_value;
}

int main() {
    vector<Event> events = {
            {1, 3, 2},
            {4, 5, 2},
            {2, 4, 3}
    };

    int result = maxTwoEvents(events);

    // Imprimir el resultado
    cout << result << endl;

    return 0;
}
