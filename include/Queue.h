#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
private:
    T* data;
    int front, rear, capacity, size;
public:
    Queue(int cap = 100) : data(new T[cap]), front(0), rear(-1), capacity(cap), size(0) {}
    ~Queue() { delete[] data; }
    
    void enqueue(const T& item) {
        if (size < capacity) {
            rear = (rear + 1) % capacity;
            data[rear] = item;
            size++;
        }
    }
    
    T dequeue() {
        if (!isEmpty()) {
            T item = data[front];
            front = (front + 1) % capacity;
            size--;
            return item;
        }
        return T();
    }
    
    T peek() const { return isEmpty() ? T() : data[front]; }
    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
};

#endif