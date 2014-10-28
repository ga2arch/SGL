//
//  StackAllocator.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator(uint32_t size_bytes): size(size_bytes) {
    mem = allocate_aligned(size, 16);
    marker = reinterpret_cast<uintptr_t>(mem);
}

StackAllocator::~StackAllocator() {
    free();
}

void* StackAllocator::alloc(uint32_t size_bytes) {
    if (occupation + size_bytes >= size)
        throw std::invalid_argument("Not enough space");
    
    auto address = reinterpret_cast<void*>(marker);
    auto p = new (address) char[size_bytes];
    marker += size_bytes;
    return p;
}

void StackAllocator::free_to_marker(Marker m) {
    marker = m;
}

void StackAllocator::clear() {
    marker = reinterpret_cast<uintptr_t>(mem);
}

void StackAllocator::free() {
    free_aligned(mem);
    size = 0;
    marker = 0;
    mem = nullptr;
}

StackAllocator::Marker StackAllocator::get_marker() {
    return marker;
}