#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <memory>
#include <random>
#include <string>
#include <iostream>
#include <algorithm>


#define TABLE_SIZE 100


template <typename K, typename V>
class Node {
private:
	K key_;
	V value_;
	Node<K, V> *next_;

public:
	Node(const K& key, const V& value) : key_(key), value_(value), next_(nullptr) {}

	K getKey() const { return key_; }

	V getValue() const { return value_; }

	void setValue(V& value) { value_ = value; }

	Node<K, V>* getNext() { return next_; }

	void setNext(Node<K, V>* next) { next_ = next; }
};

template <typename K, typename V, typename F = std::hash<K>>
class HashMap {
private:
	Node<K, V> **buckets_;
	
	F hash_;

public:
	explicit HashMap() {
		buckets_ = new Node<K, V> *[TABLE_SIZE];
		fill(buckets_, buckets_ + TABLE_SIZE, nullptr);
	}

	~HashMap() {
		// release memory
		for (int i = 0; i < TABLE_SIZE; ++i) {
			Node<K, V> *entry = buckets_[i], *prev = nullptr;
			while (entry != nullptr) {
				prev = entry;
				entry = entry->getNext();
				delete prev;
			}
			buckets_[i] = nullptr;
		}
		delete[] buckets_;
	}

	bool get(const K& key, V& value) {
		unsigned long index = hash_(key);
		Node<K, V> *entry = buckets_[index];
		while (entry != nullptr) {
			if (entry->getKey() == key) {
				value = entry->getValue();
				return true;
			}
			entry = entry->getNext();
		}
		return false;
	}

	void put(const K& key, V value) {
		unsigned long index = hash_(key);
		Node<K, V> *entry = buckets_[index], *prev = nullptr;

		// find proper position to insert this key and value or update value
		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			entry = new Node<K, V>(key, value);
			if (prev == nullptr) {
				// insert as first element
				buckets_[index] = entry;
			} else {
				// using linked list to solve collision
				prev->setNext(entry);
			}
		} else {
			// update value
			entry->setValue(value);
		}
	}

	void erase(const K& key) {
		unsigned long index = hash_(key);
		Node<K, V> *entry = buckets_[index], *prev = nullptr;

		while (entry != nullptr && entry->getKey() != key) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == nullptr) {
			// key not found
			return;
		}

		if (prev == nullptr) {
			// remove first element of the bucket
			buckets_[index] = entry->getNext();
		} else {
			prev->setNext(entry->getNext());
		}

		// final release memory
		delete entry;
	}
};


int main() {
	const int n = 10;
	std::string value("value0");
	bool existed = false;

	HashMap<int, std::string> mp;

	std::vector<int> keys;
	for (int i = 0; i < n; ++i) {
		keys.push_back(i);
	}
	for (int i = 0; i < n; ++i) {
		value.back() = '0' + i;
		mp.put(keys[i], value);
	}

	printf("\n1. Test all key in hashmap.\n");
	{
		for (int i = 0; i < n; ++i) {
			if (mp.get(i, value)) {
				std::cout << "key = " << i << ", value = " << value << "\n";
			} else {
				std::cout << "key " << i << " not existed.\n";
			}
		}
		printf("\n");
	}


	printf("2. Test remove some key.\n");
	{
		for (int i = 0; i < n; ++i) {
			if (i & 1) {
				mp.erase(i);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (mp.get(i, value)) {
				std::cout << "key = " << i << ", value = " << value << "\n";
			} else {
				std::cout << "key " << i << " not existed.\n";
			}
		}
		printf("\n");
	}

	return 0;
}