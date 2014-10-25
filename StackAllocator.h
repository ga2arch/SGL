//
//  StackAllocator.h
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__StackAllocator__
#define __SGL__StackAllocator__

#include <stdio.h>
#include <ostream>
#include "Memory.h"

class StackAllocator {

public:
    typedef uintptr_t Marker;
    
    explicit StackAllocator(uint32_t size);
    
    void* alloc(uint32_t size);
    
    Marker get_marker();
    
    void free_to_marker(Marker marker);
    
    void clear();

private:
    void* mem;
    
    Marker   marker;
    uint32_t occupation;
    uint32_t size;
};

#endif /* defined(__SGL__StackAllocator__) */
