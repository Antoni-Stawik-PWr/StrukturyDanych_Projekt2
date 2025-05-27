#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include "PriorityQueue_SinglyLinkedList.hpp"
#include "PriorityQueue_DoublyLinkedList.hpp"
#include "PriorityQueue_Array.hpp"

using namespace std;
using namespace chrono;

int main() {
    ofstream pushFile("push.csv");
    ofstream popFile("pop.csv");
    ofstream changeFile("changePriority.csv");
    ofstream peekFile("peek.csv");
    ofstream sizeFile("size.csv");

    pushFile << "n;Singly(µs);Doubly(µs);Array(µs)\n";
    popFile << "n;Singly(µs);Doubly(µs);Array(µs)\n";
    changeFile << "n;Singly(µs);Doubly(µs);Array(µs)\n";
    peekFile << "n;Singly(µs);Doubly(µs);Array(µs)\n";
    sizeFile << "n;Singly(µs);Doubly(µs);Array(µs)\n";

    srand(time(NULL));
    int repeatCount = 100000;

    for (int n = 5000; n <= 50000; n += 5000) {
        long long tS = 0, tD = 0, tA = 0;

        // push
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_SinglyLinkedList sl;
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) sl.push(rand(), rand() % 100);
            auto end = high_resolution_clock::now();
            tS += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_DoublyLinkedList dl;
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) dl.push(rand(), rand() % 100);
            auto end = high_resolution_clock::now();
            tD += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_Array ar;
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) ar.push(rand(), rand() % 100);
            auto end = high_resolution_clock::now();
            tA += duration_cast<microseconds>(end - start).count();
        }
        pushFile << n << ";" << tS / 5 << ";" << tD / 5 << ";" << tA / 5 << "\n";

        // pop
        tS = tD = tA = 0;
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_SinglyLinkedList sl;
            for (int j = 0; j < n; j++) sl.push(rand(), rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) sl.pop();
            auto end = high_resolution_clock::now();
            tS += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_DoublyLinkedList dl;
            for (int j = 0; j < n; j++) dl.push(rand(), rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) dl.pop();
            auto end = high_resolution_clock::now();
            tD += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_Array ar;
            for (int j = 0; j < n; j++) ar.push(rand(), rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) ar.pop();
            auto end = high_resolution_clock::now();
            tA += duration_cast<microseconds>(end - start).count();
        }
        popFile << n << ";" << tS / 5 << ";" << tD / 5 << ";" << tA / 5 << "\n";

        // changePriority
        tS = tD = tA = 0;
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_SinglyLinkedList sl;
            for (int j = 0; j < n; j++) sl.push(j, rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) sl.changePriority(j, rand() % 100);
            auto end = high_resolution_clock::now();
            tS += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_DoublyLinkedList dl;
            for (int j = 0; j < n; j++) dl.push(j, rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) dl.changePriority(j, rand() % 100);
            auto end = high_resolution_clock::now();
            tD += duration_cast<microseconds>(end - start).count();
        }
        for (int i = 0; i < 5; ++i) {
            PriorityQueue_Array ar;
            for (int j = 0; j < n; j++) ar.push(j, rand() % 100);
            auto start = high_resolution_clock::now();
            for (int j = 0; j < n; j++) ar.changePriority(j, rand() % 100);
            auto end = high_resolution_clock::now();
            tA += duration_cast<microseconds>(end - start).count();
        }
        changeFile << n << ";" << tS / 5 << ";" << tD / 5 << ";" << tA / 5 << "\n";

        // peek
        PriorityQueue_SinglyLinkedList sl;
        PriorityQueue_DoublyLinkedList dl;
        PriorityQueue_Array ar;
        for (int j = 0; j < n; j++) {
            sl.push(j, rand() % 100);
            dl.push(j, rand() % 100);
            ar.push(j, rand() % 100);
        }

        auto t1 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) sl.peek();
        auto t2 = high_resolution_clock::now();
        auto t3 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) dl.peek();
        auto t4 = high_resolution_clock::now();
        auto t5 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) ar.peek();
        auto t6 = high_resolution_clock::now();

        peekFile << n << ";"
            << duration_cast<microseconds>(t2 - t1).count() / repeatCount << ";"
            << duration_cast<microseconds>(t4 - t3).count() / repeatCount << ";"
            << duration_cast<microseconds>(t6 - t5).count() / repeatCount << "\n";

        // size
        t1 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) sl.size();
        t2 = high_resolution_clock::now();
        t3 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) dl.size();
        t4 = high_resolution_clock::now();
        t5 = high_resolution_clock::now();
        for (int i = 0; i < repeatCount; ++i) ar.size();
        t6 = high_resolution_clock::now();

        sizeFile << n << ";"
            << duration_cast<microseconds>(t2 - t1).count() / repeatCount << ";"
            << duration_cast<microseconds>(t4 - t3).count() / repeatCount << ";"
            << duration_cast<microseconds>(t6 - t5).count() / repeatCount << "\n";
    }

    pushFile.close();
    popFile.close();
    changeFile.close();
    peekFile.close();
    sizeFile.close();

    cout << "Wszystkie testy zakoñczone!" << endl;
    return 0;
}
