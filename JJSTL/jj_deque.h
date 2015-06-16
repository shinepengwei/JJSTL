//
//  jj_deque.h
//  JJSTL
//
//  Created by yangpengwei on 15/6/1.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__jj_deque__
#define __JJSTL__jj_deque__

#include <stdio.h>
#include "jj_iterator.h"
#include "jjalloc.h"
#include "jjmemory.h"
#endif /* defined(__JJSTL__jj_deque__) */

namespace JJ {
    //计算
    inline size_t __deque_buf_size(size_t n, size_t sz){
        return n!=0? n:(sz < 512 ? size_t(512/sz) : size_t(1));
    }
    
    template <class T, size_t BUfSize>
    struct __deque_iterator:public iterator<random_access_iterator_tag,T>{
        typedef iterator<random_access_iterator_tag, T> super_type;
        typedef __deque_iterator self_type;
        typedef __deque_iterator<T,BUfSize> iterator;
        typedef  __deque_iterator<T, BUfSize> const_iterator;
        typedef T** map_pointer;
        
        
        //每个buf所存放的元素个数
        //buf:一个map node节点指向的缓冲区
        static size_t buffer_size(){return __deque_buf_size(BUfSize,sizeof(T));}
        
        T* cur;//迭代器当前指向。
        T* first;//缓冲区第一个
        T* last;//缓冲区最后一个
        map_pointer node;//管控中心map中的节点
        
        void set_node(map_pointer new_node){
            node = new_node;
            first = *new_node;
            last = first + typename super_type::difference_type(buffer_size());
        }
        
        typename super_type::reference operator*() const {return * cur;}
        typename super_type::pointer operator->() const{return &(operator*());}
        
        typename super_type::difference_type operator-(const self_type & x) const{
            return typename super_type::difference_type(buffer_size()) * (node -x.node-1) + (cur-first) + (x.last-x.cur);
        }
        
        self_type& operator++(){
            ++cur;
            if (cur == last){
                set_node(node +1);
                cur = first;
            }
            return *this;
        }
        
//        self_type operator++(int){
//            self tmp = *this;
//            ++*this;
//            return tmp;
//        }
        
        bool operator ==(const self_type &x){return cur == x.cur;}
        
        bool operator <(const self_type &x){
            return (node ==x.node)?(cur <x.cur):(node <x.node);
        }
    };
    
    template <class T, size_t BUfSize = 0>//,  class Alloc = JJ::allocator<T>>
    class deque{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef size_t size_type;
        
    public:
        typedef __deque_iterator<T, BUfSize> iterator;
        void push_back(const value_type & t){
            JJ::construct(finish.cur, t);
            ++finish.cur;
        }
        iterator begin(){return start;}
        iterator end(){return finish;}
        
    protected:
        typedef pointer * map_pointer;
        //每个buf所存放的元素个数
        static size_t buffer_size(){return __deque_buf_size(BUfSize,sizeof(T));}
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;
        
        
        typedef JJ::allocator<value_type> data_allocator;
        typedef JJ::allocator<pointer> map_allocator;
        
        void fill_initialize(size_type n, const value_type &value){
            create_map_and_nodes(n);
            map_pointer cur;
            for(cur = start.node;cur<finish.node;++cur){
                uninitialized_fill(*cur, *cur + buffer_size(),value);
            }
        }
        void create_map_and_nodes(size_type num_eles){
            size_type num_nodes = num_eles/ buffer_size() + 1;
            map_size =  num_nodes + 4;//前面留两个，后面留两个
            map = map_allocator::allocate(map_size);
            
            map_pointer nstart = map+ (map_size - num_nodes)/2;
            map_pointer nfinish = nstart + num_nodes - 1;
            
            map_pointer cur;
            for (cur = nstart; cur <=nfinish; ++cur) {
                *cur = data_allocator::allocate(buffer_size());
            }
            
            start.set_node(nstart);
            finish.set_node(nfinish);
            start.cur = start.first;
            finish.cur = finish.first + num_nodes%buffer_size();
        }
        
    public:
        deque(int n, const value_type &value):start(),finish(),map(0),map_size(0){
            this->fill_initialize(n,value);
        };
        
        
    };
    
    
    
    
    
}