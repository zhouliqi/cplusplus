#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;


template <typename T>
class Sort final {
private:
    void adjustDown(T& array, int i, int n) {
        int idx = i;
        while (i < n) {
            // 找到节点 i 和它左右孩子节点的较大值
            int left = (i << 1) + 1;
            if (left < n && array[left] > array[idx]) {
                idx = left;
            }
            if (left + 1 < n && array[left + 1] > array[idx]) {
                idx = left + 1;
            }
            if (i != idx) {
                swap(array[i], array[idx]);
                i = idx;
            } else {
                break;
            }
        }
    }

    int partition(T& array, int lo, int hi) {
        // swap(array[lo], array[(lo + hi) / 2]);
        int pivot = array[lo], i = lo, j = hi;
        while (i < j) {
            while (i < j && pivot < array[j]) {
                --j;
            }
            if (i < j) {
                array[i++] = array[j];
            }
            while (i < j && pivot > array[i]) {
                ++i;
            }
            if (i < j) {
                array[j--] = array[i];
            }
        }
        array[i] = pivot;
        return i;
    }

    void merge(T& array, T& tmp, int lo, int mid, int hi) {
        int i = lo, j = mid + 1, idx = lo;
        while (i <= mid && j <= hi) {
            if (array[i] <= array[j]) {
                tmp[idx++] = array[i++];
            } else {
                tmp[idx++] = array[j++];
            }
        }
        while (i <= mid) {
            tmp[idx++] = array[i++];
        }
        while (j <= hi) {
            tmp[idx++] = array[j++];
        }
        for (int i = lo; i <= hi; ++i) {
            array[i] = tmp[i];
        }
    }

public:
    /**
     * 打印数组的信息
     */
    void print(const T& array, const bool flag, const string& info) {
        if (!flag) {
            return;
        }
        cout << info;
        for (auto& x : array) {
            cout << x << " ";
        }
        cout << "\n";
    }

    /**
     * 冒泡排序
     */
    void bubbleSort(T& array) {
        int n = array.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (array[j] > array[j + 1]) {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }

    /**
     * 简单选择排序
     */
    void selectionSort(T& array) {
        int n = array.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < n; ++j) {
                if (array[j] < array[minIdx]) {
                    minIdx = j;
                }
            }
            swap(array[i], array[minIdx]);
        }
    }

    /**
     * 直接插入排序
     */
    void insertionSort(T& array) {
        int n = array.size();
        for (int i = 1; i < n; ++i) {
            int j = i - 1, tmp = array[i];
            while (j >= 0 && array[j] > tmp) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = tmp;
        }
    }

    /**
     * 堆排序
     */
    void heapSort(T& array) {
        int n = array.size();
        // 1. 建大根堆
        for (int i = (n >> 1); i >= 0; --i) {
            adjustDown(array, i, n);
        }
        // 2. 排序
        for (int i = n - 1; i >= 0; --i) {
            swap(array[0], array[i]);
            adjustDown(array, 0, i);
        }
    }

    /**
     * 快速排序
     */
    void quickSort(T& array, int lo, int hi) {
        if (lo >= hi) {
            return;
        }
        int pivot = partition(array, lo, hi);
        quickSort(array, lo, pivot - 1);
        quickSort(array, pivot + 1, hi);
    }

    /**
     * 归并排序
     */
    void mergeSort(T& array, T& tmp, int lo, int hi) {
        if (lo >= hi) {
            return;
        }
        int mid = lo + (hi - lo) / 2;
        mergeSort(array, tmp, lo, mid);
        mergeSort(array, tmp, mid + 1, hi);
        merge(array, tmp, lo, mid, hi);
    }
};

int main() {
    bool flag = false;
    int n = 1e6;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(0, 30);

    vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        array[i] = dist(rng);
    }
    Sort<vector<int>> s;

    /*printf("1. heap sort.\n");
    {
        vector<int> v(array.begin(), array.end());
        s.print(v, flag, "origin:     ");
        clock_t tStart = clock();
        s.heapSort(v);
        printf("heap sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        s.print(v, flag, "after sort: ");
    }

    printf("\n2. quick sort.\n");
    {
        vector<int> v(array.begin(), array.end());
        s.print(v, flag, "origin:     ");
        clock_t tStart = clock();
        s.quickSort(v, 0, n - 1);
        printf("quick sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        s.print(v, flag, "after sort: ");
    }

    printf("\n3. merge sort.\n");
    {
        vector<int> v(array.begin(), array.end());
        vector<int> tmp(n);
        s.print(v, flag, "origin:     ");
        clock_t tStart = clock();
        s.mergeSort(v, tmp, 0, n - 1);;
        printf("merge sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        s.print(v, flag, "after sort: ");
    }*/

    printf("\n4. test sort algorithm time cost.\n");
    {
        vector<int> v1(array.begin(), array.end());
        vector<int> v2(array.begin(), array.end());
        vector<int> v3(array.begin(), array.end());
        vector<int> v4(array.begin(), array.end());
        clock_t tStart;
        
        tStart = clock();
        s.heapSort(v1);
        printf("heap sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        
        tStart = clock();
        s.quickSort(v2, 0, n - 1);
        printf("quick sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

        vector<int> tmp(n);
        tStart = clock();
        s.mergeSort(v3, tmp, 0, n - 1);
        printf("merge sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

        tStart = clock();
        sort(v4.begin(), v4.end());
        printf("std sort time taken: %.7fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    }
}