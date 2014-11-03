//
//  main.cpp
//  UnitTest
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>

#include "HashMapTest.h"

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
