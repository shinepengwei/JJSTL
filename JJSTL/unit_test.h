//
//  unit_test.h
//  JJSTL
//
//  Created by yangpengwei on 15/6/18.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__unit_test__
#define __JJSTL__unit_test__

#include <stdio.h>
#include <iostream>
#include <assert.h>
using std::cout;
using std::endl;
namespace JJ {
    class unit_test{
    private:
        std::string test_case_name;
        virtual void test_case1() {
        };
        virtual void test_case2() {
        };
        virtual void test_case3() {
        };
        virtual void test_case4() {
        };
        virtual void test_case5() {
        };
        virtual void test_case6() {
        };
        virtual void test_case7() {
        };
        virtual void test_case8() {
        };
        virtual void test_case9() {
        };
        virtual void test_case10() {
        };
    public:
        unit_test(std::string name):test_case_name(name){}
        void all_test_case() {
            cout<<endl;
            cout<<test_case_name<<" being:"<<endl;
            cout<<"test case 1"<<endl;
            test_case1();
            cout<<"========================="<<endl;
            cout<<"test case 2"<<endl;
            test_case2();
            cout<<endl;
            cout<<"test case 3"<<endl;
            test_case3();
            cout<<endl;
            cout<<"test case 4"<<endl;
            test_case4();
        };
    };
}





#endif /* defined(__JJSTL__unit_test__) */
