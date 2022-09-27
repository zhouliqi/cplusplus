#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>


std::atomic<bool> flag = false;
std::mutex mu;
std::condition_variable cv;


void bar(int i) {
    std::unique_lock<std::mutex> lk(mu);
    cv.wait(lk, [&]() {
        return flag == false;
    });
    std::cout << i << ": Hello, ";
    flag = true;
    cv.notify_all();
}

void foo() {
    std::unique_lock<std::mutex> lk(mu);
    cv.wait(lk, [&]() {
        return flag == true;
    });
    std::cout << "world\n";
    flag = false;
    cv.notify_all();
}


int main() {
    int n = 10;
    std::thread t1([&]() {
        for (int i = 0; i < n; ++i) {
            bar(i);
        }
    });
    std::thread t2([&]() {
        for (int i = 0; i < n; ++i) {
            foo();
        }
    });
    std::cout << "begin\n";
    t1.join();
    t2.join();
    return 0;
}
