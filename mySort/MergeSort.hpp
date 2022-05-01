#pragma once
#include<iostream>
using namespace std;
void MergeSort(int* a,int n);
void MSort(int* a, int* TempArr,int left, int right);
void Merge(int*a, int*TempArr, int Lpos, int Rpos, int RightEnd);

void MergeSort(int* a,int n)
{
    int *TempArr;
    TempArr=new int[n];
    if(TempArr!=NULL)
    {
        MSort(a,TempArr,0,n-1);
    }
    else
        cout<<"Error!No extra space!"<<endl;
}

void MSort(int* a, int* TempArr,int left, int right)
{
    if(left<right)
    {
        int center=(left+right)/2;
        MSort(a,TempArr,left,center);
        MSort(a,TempArr,center+1,right);
        Merge(a,TempArr,left,center+1,right);//O(N)
    }
    else
        return;//do nothing to array whose length is 0 or 1
}

void Merge(int*a, int*TempArr, int Lpos, int Rpos, int RightEnd)
{
    //Merge the two sorted array a[Lpos:Rpos-1] and a[Rpos,RightEnd] into TempArr[Lpos:RightEnd]
    //Then copy TempArr[Lpos:RightEnd] back to a[Lpos:RightEnd]
    int LeftBegin=Lpos;
    int LeftEnd=Rpos-1;
    int TempPos=Lpos;
    while(Lpos<=LeftEnd && Rpos<=RightEnd)
    {
        if(a[Lpos]<a[Rpos])
            TempArr[TempPos++]=a[Lpos++];
        else if((a[Lpos]>=a[Rpos]))
            TempArr[TempPos++]=a[Rpos++];
    }

    //copy the rest into TempArr
    while(Lpos<=LeftEnd)
        TempArr[TempPos++]=a[Lpos++];
    while(Rpos<=RightEnd)
        TempArr[TempPos++]=a[Rpos++];

    //copy back
    for(int i=LeftBegin;i<=RightEnd;i++)
        a[i]=TempArr[i];
}