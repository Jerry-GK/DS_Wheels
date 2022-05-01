#pragma once
#include<iostream>
using namespace std;

//heap sort without extra space
void HeapSort(int*a, int n);
void PercDown(int*H, int pos, int size);
void swap_Heap(int*x, int*y);
void HeapSort(int*a, int n)
{
    int i;
    for(i=n/2;i>=0;i--)//Build heap
    {
        PercDown(a,i,n);
    }
    for(i=n-1;i>0;i--)
    {
        swap_Heap(a,a+i);//DelteMin
        PercDown(a,0,i);
    }
}

void PercDown(int*H, int pos, int size)//percolate down the element in the maxHeap H with size "size"(stored in H[0:size-1])
{
    while(2*pos+1<size)
    {
        if(H[2*pos+1]>H[pos] && (2*pos+2>=size || 2*pos+2<size && H[2*pos+1]>H[2*pos+2]))//exchange with left child
        {
            swap_Heap(H+pos,H+2*pos+1);
            pos=2*pos+1;
        }
        else if(2*pos+2<size && H[2*pos+2]>H[pos])//exchange with the right child
        {
            swap_Heap(H+pos,H+2*pos+2);
            pos=2*pos+2;
        }
        else
            break;
    }
}

void swap_Heap(int*x, int*y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}