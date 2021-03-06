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

using std::cout;
using std::endl;
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
        map_pointer map_node;//管控中心map中的节点
        
        void set_node(map_pointer new_node){
            map_node = new_node;
            first = *new_node;
            last = first + typename super_type::difference_type(buffer_size());
        }
        
        typename super_type::reference operator*() const {return * cur;}
        typename super_type::pointer operator->() const{return &(operator*());}
        
        typename super_type::difference_type operator-(const self_type & x) const{
            return typename super_type::difference_type(buffer_size()) * (map_node -x.map_node-1) + (cur-first) + (x.last-x.cur);
        }
        
        self_type& operator++(){
            ++cur;
            if (cur == last){
                std::cout<<"==";
                set_node(map_node +1);
                cur = first;
            }
            return *this;
        }
        self_type & operator--(){
            if(cur == first){
                set_node(map_node-1);
                cur = last;
            }
            --cur;
            return *this;
        }
        
//        self_type operator++(int){
//            self tmp = *this;
//            ++*this;
//            return tmp;
//        }
        
        bool operator ==(const self_type &x){return cur == x.cur;}
        
        bool operator <(const self_type &x){
            return (map_node ==x.map_node)?(cur <x.cur):(map_node <x.map_node);
        }
    };
    
    template <class T, size_t BUfSize = 0>//,  class Alloc = JJ::allocator<T>>
    class deque{
        friend class deque_test;
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef size_t size_type;
        typedef __deque_iterator<T, BUfSize> iterator;
        typedef typename iterator::super_type::difference_type difference_type;
        
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
            for(cur = start.map_node;cur<finish.map_node;++cur){
                uninitialized_fill(*cur, *cur + buffer_size(),value);
            }
            uninitialized_fill(finish.first, finish.cur, value);
        }
        void create_map_and_nodes(size_type num_eles){
            size_type map_node_num = num_eles/ buffer_size() + 1;
            std::cout<<"map_node_num:"<<map_node_num<<std::endl;
            map_size =  map_node_num + 4;//前面留两个，后面留两个
            map = map_allocator::allocate(map_size);
            
            map_pointer nstart = map+ (map_size - map_node_num)/2;
            map_pointer nfinish = nstart + map_node_num - 1;
            
            map_pointer cur;
            for (cur = nstart; cur <=nfinish; ++cur) {
                *cur = data_allocator::allocate(buffer_size());
            }
            
            start.set_node(nstart);
            finish.set_node(nfinish);
            start.cur = start.first;
            finish.cur = finish.first + num_eles%buffer_size();
        }
        
        void reallocate_map(size_type nodes_to_add, bool at_front){
            //TODO 没有考虑的情况：如果map很大，可以直接在map里面移动。
            size_type old_map_node_num = finish.map_node - start.map_node +1;
            size_type new_map_node_num = old_map_node_num + nodes_to_add;
            size_type new_map_size = map_size + 4;
            std::cout<<"新建map：new_map_size:"<<new_map_size<<std::endl;
            
            map_pointer new_map = map_allocator::allocate(new_map_size);
            //简单的将原来的map数据放在新的map中间，TODO可以优化
            map_pointer new_nstart = new_map + (new_map_size - new_map_node_num)/2;
            uninitialized_copy(start.map_node, finish.map_node+1, new_nstart);
            map_allocator::deallocate(map);
            map = new_map;
            map_size = new_map_size;
            
            start.set_node(new_nstart);
            finish.set_node(new_nstart+old_map_node_num-1);
        }
        
        void reserver_map_at_back(size_type nodes_to_add = 1){
            if(nodes_to_add > map_size-(finish.map_node - map +1)){
                //map尾端没有空间了，需要重新分配
                reallocate_map(nodes_to_add, false);
            }
        }
        void reserver_map_at_front(size_type nodes_to_add = 1){
            if(nodes_to_add > start.map_node - map)
                reallocate_map(nodes_to_add, true);
        }
        
        //当最后一个缓冲区只有一个空间。此时需要新建一个缓冲区，finish指向新的缓冲区。
        void push_back_aux(const value_type & t){
            reserver_map_at_back();
            value_type t_copy = t;//复制一个新的对象？TODO 为何要复制一个对象。
            construct(finish.cur, t_copy);
            *(finish.map_node +1) = data_allocator::allocate(buffer_size());
            finish.set_node(finish.map_node +1);
            finish.cur = finish.first;
            std::cout<<"尾部创建一个新的缓冲区,缓冲区数量："<<finish.map_node - start.map_node +1<<std::endl;
        }
        
        void push_front_aux(const value_type & t){
            reserver_map_at_front();
            value_type t_copy = t;
            *(start.map_node-1) = data_allocator::allocate(buffer_size());
            start.set_node(start.map_node -1);
            start.cur = start.last-1;
            construct(start.cur, t_copy);
            std::cout<<"头部创建一个新的缓冲区,缓冲区数量："<<finish.map_node - start.map_node +1<<std::endl;
        }
        iterator insert_aux(iterator pos, const value_type &x);
        //for test
        int get_buff_num(){
            return int(finish.map_node - start.map_node) + 1;
        }
        void print()
        {
            int index =0;
            iterator it = begin();
            cout<<"deque"<<endl;
            while (!(it == end())) {
                cout<<index<<":"<<*it<<", ";
                index ++;
                ++it;
            }
            cout<<endl;
        }
        
        
    public:
        deque(int n, const value_type &value):start(),finish(),map(0),map_size(0){
            this->fill_initialize(n,value);
        };
        
        void push_back(const value_type & t){
            std::cout<<"push_back"<<t<<std::endl;
            if(finish.cur != finish.last -1){
                JJ::construct(finish.cur, t);
                ++finish.cur;//在当前缓冲区内操作。
            }
            else
                push_back_aux(t);
        }
        
        void push_front(const value_type &t){
            std::cout<<"push_front:"<<t<<std::endl;
            if (start.cur != start.first){
                --start.cur;//TODO
                JJ::construct(start.cur, t);
            }
            else
                push_front_aux(t);
        }
        value_type front(){return *begin();}
        value_type back(){return * --end();}
        value_type pop_front(){
            value_type ret = *start.cur;
            destroy(start.cur);
            start.cur ++;
            if (start.cur == start.last){
                //delete buf
                data_allocator::deallocate(*start.map_node);
                start.set_node(start.map_node+1);
                start.cur = start.first;
            }
            return ret;
        }
        
        value_type pop_back(){
            if (finish.cur != finish.first){
                finish.cur --;
            }else{
                data_allocator::deallocate(*finish.map_node);
                finish.set_node(finish.map_node-1);
                finish.cur = finish.last-1;
            }
            value_type ret = *finish.cur;
            destroy(finish.cur);
            return ret;
        }
        
        void insert(iterator pos, const value_type & x){
            if (pos == this->finish){
                push_back(x);
            }else if(pos == this->start){
                push_front(x);
            }else{
                insert_aux(pos, x);
            }
            
        }
        
        iterator begin(){return start;}
        iterator end(){return finish;}
        difference_type size(){return end() - begin();}
        
    };
    
    
    template <class T, size_t BUfSize>
    typename deque<T,BUfSize>::iterator deque<T,BUfSize>::insert_aux(iterator pos, const value_type &x){
        difference_type index = pos - start;
        if(index < size()/2){
            cout<<"insert at front"<<endl;
            push_front(front());
            iterator front1 = begin();
            ++front1;
            iterator front2 =front1;
            ++front2;
            while (!(front2 == pos)) {
                JJ::construct(front1.cur, *front2);
                ++front1;
                ++front2;
            }
            --pos;//若像前拓展，则相当于在pos前面加一个
            
        }else{
            //若向后拓展，即相当于在pos的位置处加一个。
            cout<<"insert at begin"<<endl;
            push_back(back());
            iterator end1 = end();
            --end1;
            iterator end2 = end1;
            --end2;
            while (!(end2 == pos)) {
                JJ::construct(end1.cur, *end2);
                ++end1;
                ++end2;
            }
        }
        JJ::construct(pos.cur, x);
        return pos;
    }
    
    
}

#endif /* defined(__JJSTL__jj_deque__) */