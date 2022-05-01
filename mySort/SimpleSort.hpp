#pragma once
#include<iostream>
using namespace std;
//Three simple sort methods based on swap (O(N^2));

//Insertion Sort
void InsertionSort(int* a,int n)
{
    int j,pos=1;//pos is the position of the inserting element
    for(pos=1;pos<n;pos++)
    {
        int newVal=a[pos];
        for(j=pos;j>0&&a[j-1]>newVal;j--)
        {
            a[j]=a[j-1];
        }
        a[j]=newVal;
    }
    return;
}
//Bubble Sort
void BubbleSort(int*a ,int n)
{
    int i,j;
    for(j=n-1;j>0;j--)
    {
        for(i=0;i<j;i++)
        {
            if(a[i]>a[i+1])
            {
                int temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
        }
    }
}
//Selection Sort
void SelectionSort(int* a,int n)
{
    int i,j,minIndex;
    for(i=0;i<n;i++)
    {
        minIndex=i;
        for(j=i;j<n;j++)
        {
            if(a[j]<a[minIndex])
                minIndex=j;
        }
        int temp=a[i];
        a[i]=a[minIndex];
        a[minIndex]=temp;
    }
}
