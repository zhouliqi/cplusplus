#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>

class Bar {
private:
	std::string a;

public:
	Bar(std::string a) : a(a) { std::cout << "Bar(): a = " << a << "\n"; }

	void hello() { std::cout << "hello: a = " << a << "\n"; }
	
	~Bar() { std::cout << "~Bar() : a = " << a << "\n"; }
};

template <typename T>
class SharedPtr {
private:
	// 引用计数
	std::size_t* ref_cnt_;

	// 保存所管理的对象的指针
	T* raw_ptr_;

public:
	explicit SharedPtr() : ref_cnt_(nullptr), raw_ptr_(nullptr) {}

	explicit SharedPtr(T* ptr) : ref_cnt_(new std::size_t(0)), raw_ptr_(ptr) {
		if (ptr != nullptr) {
			++(*ref_cnt_);
		}
		std::cout << "Constructor SharedPtr.\n";
	}

	// 拷贝构造函数
	SharedPtr(const SharedPtr& rhs) : ref_cnt_(rhs.ref_cnt_), raw_ptr_(rhs.raw_ptr_) {
		++(*ref_cnt_);
		std::cout << "After copy constructor, reference count = " << *ref_cnt_ << "\n";
	}

	// 拷贝赋值操作
	SharedPtr& operator=(const SharedPtr& rhs) {
		if (this != &rhs) {
			++(*rhs.ref_cnt_);
			if (ref_cnt_ != nullptr && --(*ref_cnt_) <= 0) {
				// 释放当前的资源
				delete ref_cnt_;
				delete raw_ptr_;
				std::cout << "Release current resource.\n";
			}
			ref_cnt_ = rhs.ref_cnt_;
			raw_ptr_ = rhs.raw_ptr_;
			std::cout << "After copy assignment, reference count = " << *ref_cnt_ << "\n";;
		}
		return *this;
	}

	~SharedPtr() {
		std::cout << "begin deconstructor SharedPtr." << "\n";
		if (ref_cnt_ != nullptr && --(*ref_cnt_) <= 0) {
			delete ref_cnt_;
			delete raw_ptr_;
			std::cout << "SharedPtr release resource.\n";
		}
		raw_ptr_ = nullptr;
	}
};

int main() {

	printf("\n1. SharedPtr init.\n");
	{
		SharedPtr<Bar> sp1;
	}

	printf("\n2. SharedPtr begin manage object.\n");
	{
		Bar* bar1 = new Bar("Alice");
		SharedPtr<Bar> sp1(bar1);

		SharedPtr<Bar> sp2(new Bar("Bob"));
	}

	printf("\n3. SharedPtr copy constructor.\n");
	{
		SharedPtr<Bar> sp1(new Bar("Joy"));
		SharedPtr<Bar> sp2(sp1);
	}

	printf("\n4. SharedPtr copy assignment.\n");
	{
		SharedPtr<Bar> sp1(new Bar("Joy"));
		SharedPtr<Bar> sp2;
		sp2 = sp1;
	}
	printf("\n");
	{
		SharedPtr<Bar> sp1(new Bar("Joy"));
		SharedPtr<Bar> sp2(new Bar("Lislie"));
		sp2 = sp1;
	}


	return 0;
}