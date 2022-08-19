#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


std::mutex mu;
std::condition_variable cv;
std::vector<int> v;
int i = 0;

void bar() {
    while (i < v.size()) {
        std::unique_lock<std::mutex> lk(mu);
        cv.wait(lk, []() {
            return (i & 1) == 0;
        });
        if (i < v.size()) {
            std::cout << "bar: " << v[i++] << "\n";
        }
        lk.unlock();
        cv.notify_all();
    }
}

void foo() {
    while (i < v.size()) {
        std::unique_lock<std::mutex> lk(mu);
        cv.wait(lk, []() {
            return (i & 1) == 1;
        });
        if (i < v.size()) {
            std::cout << "foo: " << v[i++] << "\n";
        }
        lk.unlock();
        cv.notify_all();
    }
}


int main() {
    int n = 10;
    v.resize(n);
    for (int j = 0; j < n; ++j) {
        v[j] = j;
    }
    std::thread t1(bar);
    std::thread t2(foo);
    std::cout << "begin\n";
    t1.join();
    t2.join();
    return 0;
}
