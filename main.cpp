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

typedef struct {
    char name;
} zap;

using namespace std;

int main(int argc, const char * argv[]) {
   
    PoolAllocator pool(2, sizeof(char));
    
    auto ptr = reinterpret_cast<char*>(pool.get());
    
    *ptr = 'Z';
    
    auto ptr2 = reinterpret_cast<char*>(pool.get());
    
    *ptr2 = 'A';
    
    cout << *ptr2 << endl;
}
