//
//  main.cpp
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include "Memory.h"

int main(int argc, const char * argv[]) {
    
    int* ptr = (int *)allocate_aligned(sizeof ptr, 4);
    int* ptr2 = (int *)malloc(sizeof(ptr2));
    
    *ptr = 2;
    *ptr2 = 4;
    
    free_aligned(ptr);
    free(ptr2);
    
}
