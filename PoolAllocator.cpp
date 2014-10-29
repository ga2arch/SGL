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
    fblocks = new uintptr_t[num];
    
    for(int i=0; i<num; i++) {
        mems[i] = reinterpret_cast<uintptr_t>(mem) + i*size;
    }
    
    current = static_cast<int>(num-1);
    index   = -1;
}

void* PoolAllocator::get() {
    if (index >= 0) {
        auto m = reinterpret_cast<void*>(fblocks[index]);
        index--;
        return m;
    }
    
    if (current >= 0) {
        void* m = reinterpret_cast<void*>(mems[current]);
        current--;
        return m;
    }
    
    throw("Error: No more free blocks available in the pool");
}

void PoolAllocator::free_block(void *mem) {
    fblocks[++index] = reinterpret_cast<uintptr_t>(mem);
}

PoolAllocator::~PoolAllocator() {
    free_aligned(mem);
}