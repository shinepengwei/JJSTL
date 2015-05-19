//
//  main.cpp
//  JJSTL
//
//  Created by yangpengwei on 15/5/15.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//
#include "jjalloc.h"
#include <iostream>
#include "jjvector.h"
#include "vector_test.h"
#include "jj_list.h"
using namespace JJ;

void testVector1(){
    unsigned int i;
    JJ::vector<int> iv(4,1);
    for (i = 0;i < iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    iv[1] = 2;
    iv[2] = 3;
    cout<<endl;
    
    JJ::vector<int>::iterator iter = iv.begin();
    cout<<*iter<<endl;
    iter++;
    cout<<*iter<<endl;
    iter++;
    cout<<*iter<<endl;
    
}
void testList(){
    JJ::list<int> il;
    il.push_back(1);
    il.push_back(2);
    il.push_back(3);
    JJ::list<int>::iterator it = il.begin();
    cout<<*it<<endl;
    ++it;
    cout<<*it<<endl;
    ++it;
    cout<<*it<<endl;
    
}
int main(int argc, const char * argv[]) {
    testList();
    return 0;
}
