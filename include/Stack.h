#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    T* data;
    int topIndex, capacity;
public:
    Stack(int cap = 100) : data(new T[cap]), topIndex(-1), capacity(cap) {}
    ~Stack() { delete[] data; }
    
    void push(const T& item) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = item;
        }
    }
    
    T pop() {
        return isEmpty() ? T() : data[topIndex--];
    }
    
    T peek() const { return isEmpty() ? T() : data[topIndex]; }
    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }
};

#endif