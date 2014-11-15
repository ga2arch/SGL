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
#include "Allocator.h"

#include <iostream>
#include <iomanip>
#include <numeric>		// For std::accumulate
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;
using namespace sgl::structures;
using namespace sgl::memory;

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

using namespace std;

int main(int argc, const char * argv[]) {
//    ProducerConsumerQueue<Zap> q(10);
//    
//    q.enqueue(20);
//    Zap z;
//    
//    cout << q.try_dequeue(z) << endl;
//    cout << z.v << endl;
//    
    Allocator<Stack<10>> pool;
    //PoolAllocator pool(10, sizeof(Zap));
    
    void* mem;
    pool.alloc(sizeof(Zap), mem);
    auto z1 = new (mem) Zap(10);
    
    cout << z1->v << endl;
        
    
}







