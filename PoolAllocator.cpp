//
//  PoolAllocator.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 28/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(size_t num, size_t size): num(num), size(size) {
    mem     = allocate_aligned(num*size, 16);
    mems    = new uintptr_t[num];
    
    for(int i=0; i<num; i++) {
        mems[i] = reinterpret_cast<uintptr_t>(mem) + i*size;
    }
    
    current = static_cast<int>(num-1);
}

void* PoolAllocator::get() {
    if (current >= 0) {
        void* m = reinterpret_cast<void*>(mems[current]);
        current--;
        return m;
    }
    else
        throw("Error: No more free blocks available in the pool");
}

void PoolAllocator::free_block(void* c_mem) {
    auto m1 = reinterpret_cast<uintptr_t>(c_mem);
    auto m2 = reinterpret_cast<uintptr_t>(mem);
    ptrdiff_t d = m1 - m2;

    if (d < num*size)
        mems[++current] = reinterpret_cast<uintptr_t>(mem);
    else
        throw("Error: It's not a block of the pool, cannot free");
}

PoolAllocator::~PoolAllocator() {
    free_aligned(mem);
}