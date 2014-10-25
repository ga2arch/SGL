//
//  main.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include "Memory.h"
#include "StackAllocator.h"

typedef struct {
    char name[4];
} zap;

int main(int argc, const char * argv[]) {
   
    StackAllocator stack_allocator(100);
    
    zap* ptr = (zap*)stack_allocator.alloc(sizeof(zap));
    
    ptr->name[0] = 'z'; // z
    
    zap* ptr2 = (zap*)stack_allocator.alloc(sizeof(zap));
    
    ptr2->name[0] = 'a'; // a
    
    auto m = stack_allocator.get_marker();
    
    zap* ptr3 = (zap*)stack_allocator.alloc(sizeof(zap));
    
    ptr3->name[0] = 'p'; // p .. dopo il free C
    
    stack_allocator.free_to_marker(m);
    
    zap* ptr4 = (zap*)stack_allocator.alloc(sizeof(zap));
    
    ptr4->name[0] = 'C'; // C

    stack_allocator.clear();
    
    
}
