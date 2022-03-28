#include <iostream>
#include <functional>
#include <type_traits>
#include <vector>
#include <list>
// #include <ext/pool_allocator.h>
using namespace std;

class Screen {
public:
    Screen(int x): i(x) {}
    int get() { return i; }
    // 重载
    void* operator new(size_t);
    void operator delete(void*, size_t);

private:
    int i;
    Screen *next;
    static Screen *freeStore;
    static const int screenChunk;
};
// 类内静态变量再次声明，为什么？？
Screen* Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size) {
    Screen *p;
    if (!freeStore) {
        // linked list 是空的，所以申请一大截
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
        // 将一大块分割成片，当作 linked list 串接起来
        for (; p != &freeStore[screenChunk - 1]; ++p)
            p->next = p + 1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void *p, size_t) {
    // 将 deleted object 插回 free list 前端
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

void noMoreMemory() {
    cerr << "out of memory" << endl;
    abort();
}

int main() {
    // vector<string, __gnu_cxx::__pool_alloc<int>> vec;
    set_new_handler(noMoreMemory);

    cout << sizeof(Screen) << endl;
    ::operator new(512);

    size_t const N = 100;
    Screen *p[100000000000000];

    for (int i = 0; i < N; ++i) {
        p[i] = new Screen(i);
    }

    for (int i = 0; i < 10; ++i) {
        cout << p[i] << endl;
    }

    for (int i = 0; i < N; ++i) {
        delete p[i];
    }
    vector<int>().push_back(2);

    list<int>().push_back(2);



    return 0;
}