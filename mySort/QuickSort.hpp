#pragma once
#define SORT_EDGE 7 //do insertion sort if length of array is less or equal than this value
#include "D:\Coding_Relative\DS_Wheels\mySort\SimpleSort.hpp"
void swap_Quick(int*x,int*y);
void MyQsort(int *a, int left, int right);//qsort a[left:right]
int getMid(int *a,int left,int right);//return the mid value of a[left],a[right] and a[(left+right)/2], and swap it with a[right-1]
void QuickSort(int *a, int n)//sort the array a[] with length n
{
    MyQsort(a,0,n-1);
    return;
}
void MyQsort(int *a,int left, int right)
{
    int pivot;
    if(right-left>SORT_EDGE)
    {
        //pick the pivot
        pivot=getMid(a,left,right);
        //using double-pointer method to partition
        int i=0,j=right-1;
        while(1)
        {
            while(a[++i]<=pivot);
            while(a[--j]>=pivot);
            if(i<j)
                swap_Quick(a+i,a+j);
            else
                break;
        }
        swap_Quick(a+i,a+right-1);//restore the pivot at the middle position i
        MyQsort(a,left,i-1);
        MyQsort(a,i+1,right);
    }
    else
    {
        InsertionSort(a+left,right-left+1);
    }
}

int getMid(int *a,int left,int right)
{
    int center=(left+right)/2;
    if(a[left]>a[center])
        swap_Quick(a+left,a+center);
    if(a[left]>a[right])
        swap_Quick(a+left,a+right);
    if(a[center]>a[right])
        swap_Quick(a+center,a+right);
    swap_Quick(a+center,a+right-1);
    return a[right-1];
}

void swap_Quick(int*x,int*y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}