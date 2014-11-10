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
};

using namespace std;

int main(int argc, const char * argv[]) {
    
    PoolAllocator pool(10, sizeof(int));
    Queue<int> q(pool);
    
    Zap z1(10);
    Zap z2(3);
    
//    q.enqueue(std::move(z1));
//    q.enqueue(std::move(z2));
//    q.enqueue(std::move(z2));
//
//    cout << q.dequeue()->v << endl;
//
    q.enqueue(10);
    
    cout << *q.dequeue() << endl;
}







