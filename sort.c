#include "sort.h"

void sort(void *begin,void *end,int size,int (*comp)(void*,void*)){
    void *left,
         *right;

    left = begin;
    right = end - size;

    while(left < right){
        while(left < right && comp(begin,right))
            right-= size;
        while(left < right && !comp(begin,left))
            left+= size;
        swap(left,right,size);
    }
    swap(left,begin,size);

    if((end-left-size)/size>1)
        sort(left+size,end,size,comp);
    if((left-begin)/size>1)
        sort(begin,left,size,comp);
}

void swap(void*a,void*b,int size){
    char buff;

    for(;size>0;a++,b++,size--){
        buff = *(char*)a;
        *(char*)a = *(char*)b;
        *(char*)b = buff;
    }
}

void copy(void *from,void *to,int size){

    for(;size>0;size--,from++,to++){
        *(char*)to = *(char*)from;
    }

}