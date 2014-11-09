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
#include "PoolAllocator.h"
#include "LinkedList.h"
#include "HashMap.h"

class Zap {
    
public:
    int v;

    Zap(int v): v(v) {}
};

using namespace std;

HashMap<int, unique_ptr<Zap>, 10, Linear, STLHasher<int>> m;

void test() {
    cout << m.get(1)->v << endl;

}

int main(int argc, const char * argv[]) {
    auto z = unique_ptr<Zap>(new Zap(10));
    m.put(1, std::move(z));

    test();
    
}







