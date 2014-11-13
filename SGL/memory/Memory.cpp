//
//  Memory.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "Memory.h"
#include <ostream>
#include <cassert>

namespace sgl { namespace memory {

    void* allocate_aligned(size_t size_bytes, size_t alignment) {
        assert(alignment >= 1);
        assert(alignment <= 128);
        assert((alignment & (alignment - 1)) == 0);
        
        size_t expandedSize_bytes = size_bytes + alignment;
        
        uintptr_t raw_address = reinterpret_cast<uintptr_t>(new char[expandedSize_bytes]);
        size_t mask = (alignment - 1);
        uintptr_t misalignment = (raw_address & mask);
        ptrdiff_t adjustement = alignment - misalignment;
        
        uintptr_t aligned_address = raw_address + adjustement;
        assert(adjustement < 256);
        
        uint8_t* p_aligned_mem = reinterpret_cast<uint8_t*>(aligned_address);
        p_aligned_mem[-1] = static_cast<uint8_t>(adjustement);
        
        return static_cast<void*>(p_aligned_mem);
    }

    void free_aligned(void* mem) {
        const uint8_t* p_aligned_mem = reinterpret_cast<const uint8_t*>(mem);
        uintptr_t aligned_address = reinterpret_cast<uintptr_t>(p_aligned_mem);
        ptrdiff_t adjustement = static_cast<ptrdiff_t>(p_aligned_mem[-1]);
        
        
        uintptr_t raw_address = aligned_address - adjustement;
        void* p_raw_mem = reinterpret_cast<void*>(raw_address);
        
        free(p_raw_mem);
    }
    
}}
