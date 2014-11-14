//
//  main.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include <thread>
#include "Memory.h"
#include "StackAllocator.h"
#include "PoolAllocator.h"
#include "LinkedList.h"
#include "FixedHashMap.h"
#include "FixedArray.h"
#include "Queue.h"
#include "Functions.h"
#include "ProducerConsumerQueue.h"

#include <iostream>
#include <iomanip>
#include <numeric>		// For std::accumulate
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;
using namespace sgl::structures;

class Zap: public Link<Zap> {
    
public:
    int v;

    Zap() {
        cout << "Costructor" << endl;
    };
    
    ~Zap() {
        cout << "Decostructor" << endl;
    }
    
    Zap(int v_): v(v_) {
        cout << "Costructor" << endl;
    };
    
    Zap(Zap&& z): v(std::move(z.v)) {
        cout << "Move costructed" << endl;
    };
    
    Zap(const Zap& o): v(o.v) {
        cout << "Copy costructed" << endl;
    };
    
    Zap& operator=(const Zap& o) {
        cout << "Copied" << endl;
        
        v = o.v;
        return *this;
    };
    
    Zap& operator=(Zap&& z) {
        cout << "Moved" << endl;
        
        v = std::move(z.v);
        return *this;
    };

};

struct Zap2 {
    int v;
    
    Zap2() {};
    Zap2(int v_): v(v_) {};
};

template<typename F, typename ...Args>
typename std::chrono::nanoseconds::rep execution(F func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // Now call the function with all the parameters you need.
    func(std::forward<Args>(args)...);
    
    auto duration =
    std::chrono::
    duration_cast<std::chrono::nanoseconds>(std::chrono::
                         high_resolution_clock::now() - start);
    
    return duration.count();
}

using namespace std;

int main(int argc, const char * argv[]) {
//    FixedHashMap<int, unique_ptr<Zap>, 10> m;
//    
//    auto z = sgl::make_unique<Zap>(10);
//    
//    m.put(10, std::move(z));
//    auto z1 = m.pop(10);
//    
//    cout << z1->v << endl;
//    
//    FixedArray<Zap, 10> a;
//    
//    Zap z2(10);
//    a.insert<0>(Zap(10));
//    auto& b = a.get<0>();
//    
//    b.v = 2;
//    
//    cout << a.get<0>().v << endl;
//    
//    sgl::memory::PoolAllocator pool(10, sizeof(Zap));
//    Queue<Zap> q(pool);
//    
//    q.emplace(10);
//    
//    auto&& z3 = q.dequeue();
//    
//    cout << z3.v << endl;
    
//     cout << execution(([]() {
//              volatile int forceNoOptimizeDummy;
//        const size_t MAX = 300 * 1000;
//
//    ProducerConsumerQueue<int> q(MAX);
//    
//        int element = -1;
//        int* n = new int(10);
//
//    std::thread producer([&]() {
//        size_t num = 0;
//        for (size_t i = 0; i != MAX; ++i) {
//            q.enqueue(10);
//            ++num;
//        }
//    });
//    
//        std::thread consumer([&]() {
//            for (size_t i = 0; i != MAX; ++i) {
//                q.try_dequeue(element);
//            }
//        });
//        
//    producer.join();
//    consumer.join();
//    forceNoOptimizeDummy = (bool)(q.try_dequeue(element));
//
//    }));

    ProducerConsumerQueue<Zap> q(10);
    
    q.enqueue(10);
    q.enqueue(20);
    Zap z;
    
    cout << q.try_dequeue(z) << endl;
    cout << z.v << endl;
    
}







