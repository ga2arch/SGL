//
//  PoolAllocator.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 28/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "PoolAllocator.h"
#include <cmath>

PoolAllocator::PoolAllocator(size_t num, size_t size): num(num),
                                                       size(size) {
    mem     = allocate_aligned(num*size, 16);
    mems    = new uintptr_t[num];
    
    for(int i=0; i<num; i++) {
        mems[i] = reinterpret_cast<uintptr_t>(mem) + i*size;
    }
    
    current = static_cast<int>(num-1);
}

void* PoolAllocator::get() {
    if (current >= 0)
        return reinterpret_cast<void*>(mems[current--]);
    else
        throw("Error: No more free blocks available in the pool");
}

void PoolAllocator::free_block(void* f_mem) {
    auto m1 = reinterpret_cast<uintptr_t>(f_mem);
    auto m2 = reinterpret_cast<uintptr_t>(mem);
    ptrdiff_t d = m2 - m1;

    if (d > num*size) {
        if (d % num == 0)
            mems[++current] = m1;
        else {
            auto t = trunc(d / num);
            auto m = (m2 + t*size);
            mems[++current] = m;
        }
    }
    else
        throw("Error: It's not a block of the pool, cannot free");
}

PoolAllocator::~PoolAllocator() {
    free_aligned(mem);
}