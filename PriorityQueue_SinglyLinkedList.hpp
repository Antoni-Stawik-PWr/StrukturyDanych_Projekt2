#ifndef PRIORITY_QUEUE_SLL_HPP
#define PRIORITY_QUEUE_SLL_HPP

#include <iostream>
#include <stdexcept>

class PriorityQueue_SinglyLinkedList {
private:
    struct Node {
        int value;
        int priority;
        Node* next;
        Node(int v, int p) : value(v), priority(p), next(nullptr) {}
    };

    Node* head;
    int count;

public:
    PriorityQueue_SinglyLinkedList() : head(nullptr), count(0) {}

    ~PriorityQueue_SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(int value, int priority) {
        Node* newNode = new Node(value, priority);
        if (!head || priority < head->priority) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->priority <= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
    }

    int pop() {
        if (!head) throw std::runtime_error("Kolejka jest pusta!");
        int value = head->value;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return value;
    }

    int peek() const {
        if (!head) throw std::runtime_error("Kolejka jest pusta!");
        return head->value;
    }

    void changePriority(int value, int newPriority) {
        Node* prev = nullptr, * curr = head;
        while (curr) {
            if (curr->value == value) {
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
                count--;
                push(value, newPriority);
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    int size() const {
        return count;
    }

    void print() const {
        Node* current = head;
        std::cout << "Kolejka [wartoœæ(priorytet)]: ";
        while (current) {
            std::cout << current->value << "(" << current->priority << ") -> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }
};

#endif