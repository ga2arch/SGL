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
    
    FixedHashMap<int, Zap, 10, Linear<Zap>> m;
    
    m.put(10, Zap(10));
    m.put(20, Zap(39));
    
    //cout << m.get(10).v << endl;
}







