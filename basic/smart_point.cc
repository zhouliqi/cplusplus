#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;


class Bar {
private:
    string a;

public:
    Bar(string a) : a(a) { cout << "Bar(): a = " << a << "\n"; }

    void hello() { cout << "hello: a = " << a << "\n"; }
    
    ~Bar() { cout << "~Bar() : a = " << a << "\n"; }
};


unique_ptr<Bar> foo() {
    printf("return a unique_ptr\n");
    return unique_ptr<Bar>(new Bar("Alice"));
}


int main(int argc, char const *argv[]) {
    int test_case = 1;
    printf("%d. unique_ptr as function return value.\n", test_case++);
    {
        auto p = foo();
    }

    printf("\n%d. using raw pointer to init unique_ptr.\n", test_case++);
    {
        Bar *bar1 = new Bar("Bob"), *bar2 = new Bar("Joy");
        unique_ptr<Bar> p1(bar1);
        // Error Code: two unique_ptr owner bar1, it will delete bar1 twice.
        /*unique_ptr<Bar> p2(bar1);
        p1->hello();
        p2->hello();
        sleep(2);*/
        p1.reset(bar2);
    }
    
    printf("\n%d. unique_ptr point to another object.\n", test_case++);
    {
        unique_ptr<Bar> p1 = make_unique<Bar>("10");
        Bar *bar = new Bar("20");
        p1.reset(bar);
    }
    
    printf("\n%d. move(unique_ptr) make unique_ptr lose control of resource.\n", test_case++);
    {
        Bar *bar = new Bar("30");
        unique_ptr<Bar> p1(bar);
        unique_ptr<Bar> p2 = move(p1);
        //p1->hello(); // p1 is invalid after it release ownership of bar
        p2->hello();
    }

    printf("\n%d. using raw pointer to init shared_ptr.\n", test_case++);
    {
        Bar* bar1 = new Bar("40");
        shared_ptr<Bar> sp1(bar1);
        Bar* bar2 = new Bar("50");
        sp1.reset(bar2);
        printf("sp1.use_count()= %ld\n", sp1.use_count());
        shared_ptr<Bar> sp2 = sp1;
        printf("sp1.use_count()= %ld, sp2.use_count()= %ld\n", sp1.use_count(), sp2.use_count());
        // move(sp2) will cause sp2 nullify
        shared_ptr<Bar> sp3(move(sp2));
        printf("sp1.use_count()= %ld, sp2.use_count()= %ld, sp3.use_count()= %ld\n", sp1.use_count(), sp2.use_count(), sp3.use_count());
        // sp2 transfer ownership of bar2 to sp3 now and can't use sp2 to call hello()
        //sp2->hello();
    }

    printf("\n%d. using shared_ptr and weak_ptr.\n", test_case++);
    {
        shared_ptr<Bar> sp1 = make_shared<Bar>("Alex");
        printf("sp1.use_count()= %ld\n", sp1.use_count());
        weak_ptr<Bar> wp1(sp1);
        printf("sp1.use_count()= %ld, wp1.use_count()= %ld\n", sp1.use_count(), wp1.use_count());
    }
    
    printf("\n%d. empty vector size = ", test_case++);
    {
        std::vector<int> v;
        printf("%ldByte\n", sizeof(v));
    }
    return 0;
}