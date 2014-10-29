//
//  PoolAllocator.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 28/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(size_t num, size_t size): num(num), size(size) {
    mem = allocate_aligned(num*size, 16);
    mems = new uintptr_t[num];
    
    for(int i=0; i<num; i++) {
        mems[i] = reinterpret_cast<uintptr_t>(mem) + i*size;
    }
    
    current = num-1;
}

void* PoolAllocator::get() {
    if (current > size) throw("Error: No more elements available in the pool");
    
    void* m = reinterpret_cast<void*>(mems[current]);
    current--;
    return m;
}

PoolAllocator::~PoolAllocator() {
    free_aligned(mem);
}