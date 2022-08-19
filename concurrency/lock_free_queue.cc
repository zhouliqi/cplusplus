#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <atomic>
#include <memory>
#include <random>
#include <thread>
#include <iostream>
#include <algorithm>


template <typename T>
class LockFreeQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;
        Node() {}
        Node(const T& data) : data(std::make_shared<T>(data)) {}
    };

    std::atomic<Node*> head_;
    std::atomic<Node*> tail_;

public:
    LockFreeQueue() {
        Node* n = new Node();
        head_.store(n);
        tail_.store(n);
    }

    void push(const T& data) {
        std::atomic<Node*> const new_node(new Node(data));
        while (true) {
            Node* tail = tail_.load();
            Node* next = tail->next.load();
            if (tail == tail_.load()) {
                if (next == nullptr) {
                    if (tail->next.compare_exchange_weak(next, new_node)) {
                        tail_.compare_exchange_weak(tail, new_node);
                        return;
                    }
                } else {
                    tail_.compare_exchange_weak(tail, next);
                }
            }
        }
    }

    std::shared_ptr<T> pop() {
        while (true) {
            Node* head = head_.load();
            Node* tail = tail_.load();
            Node* next = head->next.load();
            if (head == head_.load()) {
                if (head == tail) {
                    if (next == nullptr) {
                        return nullptr;
                    }
                    tail_.compare_exchange_weak(tail, next);
                } else {
                    std::shared_ptr<T> v = next->data;
                    if (head_.compare_exchange_weak(head, next)) {
                        return v;
                    }
                }
            }
        }
    }

    bool empty() {
        return head_ == tail_;
    }
};

LockFreeQueue<int> lkf;
int n = 1e5;

void bar() {
    for (int i = 0; i < n; i += 2) {
        lkf.push(i);
    }
}

void foo() {
    for (int i = 1; i < n; i += 2) {
        lkf.push(i);
    }
}

int main() {

    {
        std::thread t1(bar);
        std::thread t2(foo);
        std::cout << "begin add element to queue.\n";
        t1.join();
        t2.join();
        int count = 0;
        while (!lkf.empty()) {
            auto v = lkf.pop();
            if (v != nullptr) {
                ++count;
            }
            //std::cout << *v << " ";
        }
        std::cout << count << "\n";
    }

    return 0;
}