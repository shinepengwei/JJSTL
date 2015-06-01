//
//  jj_deque.cpp
//  JJSTL
//
//  Created by yangpengwei on 15/6/1.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#include "jj_deque.h"
#include "jjmemory.h"
//namespace JJ{
//template <class T, size_t BUfSize>
//void deque<T,BUfSize>::fill_initialize(size_type n, const value_type &value){
//    create_map_and_nodes(n);
//    map_pointer cur;
//    for(cur = start.node;cur<finish.node;++cur){
//        uninitialized_fill(*cur, *cur + buffer_size(),value);
//    }
//}
//
//template <class T, size_t BUfSize>
//void deque<T,BUfSize>::create_map_and_nodes(size_type num_eles){
//    size_type num_nodes = num_eles/ buffer_size() + 1;
//    map_size =  num_nodes + 4;//前面留两个，后面留两个
//    map = map_allocator::allocate(map_size);
//    
//    map_pointer nstart = map+ (map_size - num_nodes)/2;
//    map_pointer nfinish = nstart + num_nodes - 1;
//    
//    map_pointer cur;
//    for (cur = nstart; cur <=finish; ++cur) {
//        *cur = data_allocator::allocate(buffer_size());
//    }
//    
//    start.set_node(nstart);
//    finish.set_node(nfinish);
//    start.cur = start.first;
//    finish.cur = finish.first + num_nodes%buffer_size();
//    
//}
//}