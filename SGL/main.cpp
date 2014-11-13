//
//  main.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include "Memory.h"
#include "StackAllocator.h"
#include "PoolAllocator.h"
#include "LinkedList.h"
#include "FixedHashMap.h"
#include "FixedArray.h"
#include "Queue.h"

using namespace std;
using namespace sgl::structures;

class Zap: public Link<Zap> {
    
public:
    int v;

    Zap() {
        cout << "Costructor" << endl;
    };
    
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
    FixedHashMap<int, unique_ptr<Zap>, 10> m;
    
    auto z = sgl::make_unique<Zap>(10);
    
    m.put(10, std::move(z));
    auto z1 = m.pop(10);
    
    cout << z1->v << endl;
    
    FixedArray<Zap, 10> a;
    
    Zap z2(10);
    a.insert<0>(Zap(10));
    
    sgl::memory::PoolAllocator pool(10, sizeof(Zap));
    Queue<Zap> q(pool);
    
    q.emplace(10);
    
    auto&& z3 = q.dequeue();
    
    cout << z3.v << endl;
    
}







