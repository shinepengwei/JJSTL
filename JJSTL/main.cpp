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
#include "jj_deque.h"
#include "deque_test.h"
using namespace JJ;

void testVector1(){
    unsigned int i;
    JJ::vector<int> iv(4,1);
    for (i = 0;i < iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    iv[1] = 2;
    iv[2] = 3;
    for (i = 0;i < iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    
    JJ::vector<int>::iterator iter = iv.begin();
    cout<<*iter<<endl;
    iter++;
    cout<<*iter<<endl;
    iter++;
    cout<<*iter<<endl;
cout<<"capacity:"<<iv.capacity()<<endl;
    iv.push_back(4);
    cout<<"capacity:"<<iv.capacity()<<endl;
    iv.push_back(5);
    cout<<"capacity:"<<iv.capacity()<<endl;
    for (i = 0;i < iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    
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
    ++it;
    cout<<*it<<endl;
    ++it;
    cout<<*it<<endl;
    ++it;
    cout<<*it<<endl;
    
    cout<<"size:"<<il.size()<<endl;
    it = il.erase(it);
    cout<<"after erase:"<<*it<<endl;
    it = il.erase(it);
    cout<<"after erase:"<<*it<<endl;
    il.erase(it);
    cout<<"erase:"<<*it<<endl;//TODO：猜的：：这里指向的内存应该已经释放了，但是数据还没有被覆盖。因此还可以访问

    cout<<il.size()<<endl;
    
}


int main(int argc, const char * argv[]) {
    deque_test* dt = new deque_test();
    dt->all_test_case();
    //testDeque();
    
}
