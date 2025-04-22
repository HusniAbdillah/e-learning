#ifndef QUEUE_H
#define QUEUE_H

#include <queue>

template <typename T>
class AntrianPenilaian {
private:
    std::queue<T> items;
public:
    void enqueue(const T& item) { items.push(item); }
    T dequeue() { 
        T item = items.front();
        items.pop();
        return item;
    }
    bool isEmpty() const { return items.empty(); }
};

#endif