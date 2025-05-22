#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <queue>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    struct CompareDeadline {
        bool operator()(const T& a, const T& b) {
            return a.deadline > b.deadline;
        }
    };
    std::priority_queue<T, std::vector<T>, CompareDeadline> heap;
public:
    void tambah(const T& item) { heap.push(item); }
    T ambil() { 
        T item = heap.top();
        heap.pop();
        return item;
    }
    bool isEmpty() const { return heap.empty(); }
};

#endif