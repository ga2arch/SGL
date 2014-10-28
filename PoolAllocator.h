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
#include "Memory.h"

class PoolAllocator {
    
public:
    PoolAllocator(size_t num, size_t size);
    
    
private:
    size_t num;
    size_t size;
    
};


#endif /* defined(__SGL__PoolAllocator__) */