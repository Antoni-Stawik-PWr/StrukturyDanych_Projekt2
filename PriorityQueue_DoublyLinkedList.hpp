#ifndef PRIORITY_QUEUE_DLL_HPP
#define PRIORITY_QUEUE_DLL_HPP

#include <iostream>
#include <stdexcept>

class PriorityQueue_DoublyLinkedList {
private:
    struct Node {
        int value;
        int priority;
        Node* next;
        Node* prev;
        Node(int v, int p) : value(v), priority(p), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    int count;

public:
    PriorityQueue_DoublyLinkedList() : head(nullptr), count(0) {}

    ~PriorityQueue_DoublyLinkedList() {
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
            if (head) head->prev = newNode;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && current->next->priority <= priority) {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
        }
        count++;
    }

    int pop() {
        if (!head) throw std::runtime_error("Kolejka jest pusta!");
        int value = head->value;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        delete temp;
        count--;
        return value;
    }

    int peek() const {
        if (!head) throw std::runtime_error("Kolejka jest pusta!");
        return head->value;
    }

    void changePriority(int value, int newPriority) {
        Node* current = head;
        while (current) {
            if (current->value == value) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;
                if (current->next) current->next->prev = current->prev;
                delete current;
                count--;
                push(value, newPriority);
                return;
            }
            current = current->next;
        }
    }

    int size() const {
        return count;
    }

    void print() const {
        Node* current = head;
        std::cout << "Kolejka [wartoœæ(priorytet)]: ";
        while (current) {
            std::cout << current->value << "(" << current->priority << ") <-> ";
            current = current->next;
        }
        std::cout << "NULL\n";
    }
};

#endif