//
//  StackAllocator.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator(uint32_t size): size(size) {
    mem = allocate_aligned(size, 16);
    
    marker = reinterpret_cast<uintptr_t>(mem);
}

void* StackAllocator::alloc(uint32_t size_bytes) {
    auto address = reinterpret_cast<void*>(marker);
    auto p = new (address) char[size_bytes];
    marker += size_bytes;
    return p;
}

void StackAllocator::free_to_marker(Marker marker) {
    auto raw_address = reinterpret_cast<void*>(marker);
    free(raw_address);
}

void StackAllocator::clear() {
    free_aligned(mem);
}

StackAllocator::Marker StackAllocator::get_marker() {
    return marker;
}