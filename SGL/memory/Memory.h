//
//  Memory.h
//  SGL
//
//  Created by Gabriele on 25/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__Memory__
#define __SGL__Memory__

#include <stdio.h>
#include <ostream>

std::shared_ptr<void> allocate_aligned(size_t size_bytes, size_t alignment);
void  free_aligned(void* mem);

#endif /* defined(__SGL__Memory__) */
