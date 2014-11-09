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
    
//    Zap* z1 = new Zap();
//    Zap* z2 = new Zap();
//    Zap* z3 = new Zap();
//    
//    z1->v = 2;
//    z2->v = 20;
////    z3.v = 2;
//    
//    HashMap<string*, string, 2> m;
//    string* k = new string("ciao");
//    string k2("ilaria");
//    string k3("bababa");
//    
//    m.put(k, k2);
////    m.put(k2, k1);
//
//    cout << m.get(k) << endl;
//    
//    delete z1;
//    delete z2;
//    delete z3;
//    delete k;

    HashMap<int, unique_ptr<Zap>, 10> m;
    auto z1 = unique_ptr<Zap>(new Zap(2));
    
    m.put(10, std::move(z1));
    
    HashMap<int, shared_ptr<Zap>, 10> m1;
    auto z2 = shared_ptr<Zap>(new Zap(3));
    
    m1.put(10, std::move(z2));
    
    cout << z1->v << endl;
    
    HashMap<int, int, 10> m2;

    m2.put(10, 10);
}





