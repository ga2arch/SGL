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
    
}

void* PoolAllocator::get() {
    
}