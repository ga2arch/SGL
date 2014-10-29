//
//  PoolAllocator.h
//  SGL
//
//  Created by Gabriele Carrettoni on 28/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__PoolAllocator__
#define __SGL__PoolAllocator__

#include <stdio.h>
#include <ostream>
#include "Memory.h"

class PoolAllocator {
    
public:
    PoolAllocator(size_t num, size_t size);
    ~PoolAllocator();
    
    void* get();
    void free_block(void* mem);
    
    void free();
    
private:
    void* mem;
    uintptr_t* mems;

    size_t current;
    size_t num;
    size_t size;
};


#endif /* defined(__SGL__PoolAllocator__) */
