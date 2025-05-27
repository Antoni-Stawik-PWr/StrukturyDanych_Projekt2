#ifndef PRIORITY_QUEUE_ARRAY_HPP
#define PRIORITY_QUEUE_ARRAY_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

class PriorityQueue_Array {
private:
    struct Element {
        int value;
        int priority;
    };

    std::vector<Element> data;

public:
    void push(int value, int priority) {
        Element e{ value, priority };
        auto it = data.begin();
        while (it != data.end() && it->priority <= priority) {
            ++it;
        }
        data.insert(it, e);

    int pop() {
        if (data.empty()) throw std::runtime_error("Kolejka jest pusta!");
        int val = data.front().value;
        data.erase(data.begin());
        return val;
    }

    int peek() const {
        if (data.empty()) throw std::runtime_error("Kolejka jest pusta!");
        return data.front().value;
    }

    void changePriority(int value, int newPriority) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->value == value) {
                data.erase(it);
                push(value, newPriority);
                return;
            }
        }
    }

    int size() const {
        return data.size();
    }

    void print() const {
        std::cout << "Kolejka [wartoœæ(priorytet)]: ";
        for (const auto& e : data) {
            std::cout << e.value << "(" << e.priority << ") -> ";
        }
        std::cout << "NULL\n";
    }
};

#endif
