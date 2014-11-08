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
    
    std::shared_ptr<void> get_block();
    void free_block(std::shared_ptr<void> block);

private:
    std::shared_ptr<void> mem;
    uintptr_t* mems;
    
    int current;

    size_t num;
    size_t size;
    
    void free_block(void* block);
};


#endif /* defined(__SGL__PoolAllocator__) */
