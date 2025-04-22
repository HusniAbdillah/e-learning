#ifndef STACK_H
#define STACK_H

#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> items;
public:
    void push(const T& item) { items.push_back(item); }
    T pop() {
        if (items.empty()) return T();
        T item = items.back();
        items.pop_back();
        return item;
    }
    bool isEmpty() const { return items.empty(); }
};

#endif