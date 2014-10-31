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

typedef struct {
    char name;
} zap;

using namespace std;

int main(int argc, const char * argv[]) {

    PoolAllocator pool(10, 10);
    
    zap* m = (zap*)pool.get();
    
    pool.free_block(m+1);
    
    LinkedList<int> l;
    
    l.push_back(3);
    l.push_front(1);
    
    auto n = l.head.next;

    while (n) {
        cout << n->elem << endl;
        n = n->next;
    }
}
