//
//  jjmemory.ccp
//  JJSTL
//
//  Created by yangpengwei on 15/5/16.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#include "jjmemory.h"

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first ,InputIterator last, ForwardIterator result){
    ForwardIterator cur = result;
    for (; first != last; ++first, ++cur) {
        construct(&*cur, *first);
    }
    return cur;

}
