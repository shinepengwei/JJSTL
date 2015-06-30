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
using std::cout;
using std::endl;
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
            assert(ideq.get_buff_num() == 6);
            
        }
        
        void test_case2(){
            cout<<"test deque:pop_back,pop_front,clear"<<endl;
            deque<int,8> ideq(15,1);
            assert(ideq.get_buff_num() == 2);
            
            ideq.push_front(-2);
            ideq.push_front(-1);
            assert(ideq.get_buff_num() == 3);
            ideq.print();
            
            int t = ideq.pop_front();
            assert(ideq.get_buff_num() == 3);
            assert(t == -1);
            t = ideq.pop_front();
            assert(t == -2);
            assert(ideq.get_buff_num() == 2);
            ideq.print();

            
            ideq.push_back(2);
            assert(ideq.get_buff_num() == 3);
            ideq.push_back(3);
            assert(ideq.get_buff_num() == 3);
            
            t = ideq.pop_back();
            assert(t == 3);
            assert(ideq.get_buff_num() == 3);
            t = ideq.pop_back();
            assert(t == 2);
            assert(ideq.get_buff_num() == 2);
            ideq.print();
            for (int i =0; i<8; i++) {
                ideq.pop_back();
            }
            assert(ideq.get_buff_num() == 1);
            ideq.print();
        
        }
        void test_case3(){
            cout<<"test deque: insert"<<endl;
            
        }
        
    };

}


#endif /* defined(__JJSTL__deque_test__) */
