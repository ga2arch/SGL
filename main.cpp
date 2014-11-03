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

struct Zap {
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
    
    Zap* z1 = new Zap();
    Zap* z2 = new Zap();
    Zap* z3 = new Zap();
    
    z1->v = 2;
    z2->v = 20;
//    z3.v = 2;
    
    HashMap<int, string, 2> m;
    string k1("ciao");
    string k2("ilaria");
    string k3("bababa");
    
    m.put(0, k2);
    m.put(1, k1);
    m.remove(0);
//    m.remove(ik2);
    cout << (m.get(1) == k1);
    //cout << z << endl;
    
    delete z1;
    delete z2;
    delete z3;

}





