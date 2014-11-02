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

class Zap: public Link<Zap> {
public:
    int v;
};

using namespace std;

int main(int argc, const char * argv[]) {

//    PoolAllocator pool(10, 10);
//    LinkedList<Zap> l;
//    
//    auto z = reinterpret_cast<Link<Zap>*>(pool.get_block());
//    
//    ((Zap*)z)->v = 10;
//    
//    l.push_back(z);
////    l.remove(z);
//
//    auto n = l.head.next;
//
//    while (n) {
//        cout << ((Zap*)n)->v << endl;
//        n = n->next;
//    }
    
    Zap z1;
    Zap z2;
    
    z1.v = 10;
    z2.v = 12;
    
    HashMap<string, Zap, 10> m;
    string k1("ciao");
    string k2("ilaria");
    
    m.put(k1, z1);
    m.put(k2, z2);
    
    cout << m.get(k2)->v << endl;
    
}





