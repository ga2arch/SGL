//
//  LinkedListTest.h
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__LinkedListTest__
#define __SGL__LinkedListTest__

#include <stdio.h>
#include <gtest/gtest.h>
#include "LinkedList.h"

using namespace sgl::structures;

class Elem: public Link<Elem> {
public:
    explicit Elem(int v): value(v) {};
    int value;
};

#endif /* defined(__SGL__LinkedListTest__) */
