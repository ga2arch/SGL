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
#include "Queue.h"

using namespace std;
using namespace sgl::structures;

class Zap: Link<Zap> {
    
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
    }
    
    Zap& operator=(Zap&& z) {
        cout << "Moved" << endl;
        
        
        v = std::move(z.v);
        return *this;
    }

};



using namespace std;

int main(int argc, const char * argv[]) {
    FixedHashMap<int, Zap, 10> m;
    
    Zap z;
    
    m.put(10, Zap(10));
    z = m.pop(10);
    
    cout << z.v << endl;
}







