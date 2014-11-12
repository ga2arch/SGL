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
#include "HashMap.h"
#include "Queue.h"

class Zap: Link<Zap> {
    
public:
    int v;

    Zap(int v): v(v) {}
    
    Zap(const Zap& z): v(z.v) {}
    Zap(Zap&& z): v(std::move(z.v)) {}

};

using namespace std;

int main(int argc, const char * argv[]) {
    
    PoolAllocator pool(10, sizeof(Zap));
    Queue<Zap> q(pool);
    
    Zap z1(10);
    Zap z2(3);
    auto zap = shared_ptr<Zap>(new Zap(20));
    
//    q.enqueue(std::move(z1));
//    q.enqueue(std::move(z2));
//    q.enqueue(std::move(z2));
//
//    cout << q.dequeue()->v << endl;
//
    q.enqueue(z2);
    
    cout << q.dequeue().v << endl;
}







