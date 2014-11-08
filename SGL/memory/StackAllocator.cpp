//
//  StackAllocator.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "StackAllocator.h"

StackAllocator::StackAllocator(uint32_t size_bytes): size(size_bytes),
                                                     mem(allocate_aligned(size_bytes, 16)) {
    marker = reinterpret_cast<uintptr_t>(mem.get());
}

std::shared_ptr<void> StackAllocator::alloc(uint32_t size_bytes) {
    if (occupation + size_bytes >= size)
        throw std::out_of_range("Error: Not enough space");
    
    auto address = reinterpret_cast<void*>(marker);
    auto p = std::shared_ptr<void> (new (address) char[size_bytes]);
    marker += size_bytes;
    return p;
}

void StackAllocator::free_to_marker(Marker m) {
    marker = m;
}

void StackAllocator::clear() {
    marker = reinterpret_cast<uintptr_t>(mem.get());
}

StackAllocator::Marker StackAllocator::get_marker() {
    return marker;
}