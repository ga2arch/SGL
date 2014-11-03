//
//  DoubleBufferedAllocator.h
//  SGL
//
//  Created by Gabriele Carrettoni on 30/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__DoubleBufferedAllocator__
#define __SGL__DoubleBufferedAllocator__

#include <stdio.h>
#include <ostream>
#include "StackAllocator.h"

class DoubleBufferedAllocator {
    
public:
    explicit DoubleBufferedAllocator();
    ~DoubleBufferedAllocator();
    
    void swap_buffers();
    void clear_current();
    void* alloc(uint32_t bytes);
    
private:
    uint32_t cursor_stack;
    StackAllocator stacks[2];
    
};

#endif /* defined(__SGL__DoubleBufferedAllocator__) */
