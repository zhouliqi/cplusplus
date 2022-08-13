#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


std::mutex mu;
std::condition_variable cv;
std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int i = 0;

void bar() {
	while (true) {
		std::unique_lock<std::mutex> lk(mu);
		cv.wait(lk, []() {
			return (i & 1) == 0;
		});
		if (i < v.size()) {
			std::cout << "bar: " << v[i] << "\n";
			++i;
		}
		lk.unlock();
		cv.notify_all();
		if (i >= v.size()) {
			break;
		}
	}
}

void foo() {
	while (i < v.size()) {
		std::unique_lock<std::mutex> lk(mu);
		cv.wait(lk, []() {
			return (i & 1) == 1;
		});
		if (i < v.size()) {
			std::cout << "foo: " << v[i] << "\n";
			++i;
		}
		lk.unlock();
		cv.notify_all();
		if (i >= v.size()) {
			break;
		}
	}
}


int main() {
	std::thread t1(bar);
	std::thread t2(foo);
	std::cout << "begin\n";
	t1.join();
	t2.join();
	return 0;
}
