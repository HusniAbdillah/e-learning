#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> data;
    static bool compare(const T& a, const T& b) {
        return a.deadline > b.deadline;
    }
public:
    void tambah(const T& item) {
        data.push_back(item);
        std::sort(data.begin(), data.end(), compare);
    }
    T ambil() {
        if (data.empty()) throw std::out_of_range("PriorityQueue kosong");
        T item = data.back();
        data.pop_back();
        return item;
    }
    bool isEmpty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

#endif