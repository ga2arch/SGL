//
//  DoubleBufferedAllocator.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 30/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "DoubleBufferedAllocator.h"

void DoubleBufferedAllocator::swap_buffers() {
    cursor_stack = static_cast<uint32_t>(!cursor_stack);
}

void DoubleBufferedAllocator::clear_current() {
    stacks[cursor_stack].clear();
}

std::shared_ptr<void> DoubleBufferedAllocator::alloc(uint32_t bytes) {
    return stacks[cursor_stack].alloc(bytes);
}