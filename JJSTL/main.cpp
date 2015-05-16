//
//  main.cpp
//  JJSTL
//
//  Created by yangpengwei on 15/5/15.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//
#include "jjalloc.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int ia[5] = {0,1,2,3,4};
    unsigned int i;
    vector<int, JJ::allocator<int>> iv(ia,ia+5);
    for (i = 0;i < iv.size(); i++) {
        cout<<iv[i]<<" ";
    }
    cout<<endl;
    return 0;
}
