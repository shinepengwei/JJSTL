//
//  deque_test.h
//  JJSTL
//
//  Created by yangpengwei on 15/6/18.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__deque_test__
#define __JJSTL__deque_test__

#include <stdio.h>
#include "unit_test.h"
#include "jj_deque.h"
//
namespace JJ{
    class deque_test:public unit_test{
    public:
        deque_test():unit_test("deque_test"){}
        
    private:
        void test_case1(){
            std::cout<<"测试：创建／push_back／push_front/重新分配"<<std::endl;
            deque<int,8> ideq(13,1);
            ideq.print();
            //测试创建一个新的buffer
            ideq.push_back(10);
            ideq.print();
            
            ideq.push_front(-1);
            ideq.print();
            
            //测试创建新的map
            
            for (int i =0; i<20; i++) {
                ideq.push_back(-i);
            }
            ideq.print();
        }
    };

}


#endif /* defined(__JJSTL__deque_test__) */
