#include "..\include\mySort\ShellSort.h"

void ShellSort(int* a,int n,string seq)
{
    int IncSeq[MAX_SIZE]={0};
    int i,pos,j,k,t;//1=h0<h2<....<h(t-1) is the increasement sequence
    //obtain the increasement sequence due to the input string
    if(seq=="Shell")//worst N^2, avg N^3/2
    {
        i=1;
        IncSeq[0]=n/2;
        while(1)
        {
            IncSeq[i]=IncSeq[i-1]/2;
            if(IncSeq[i]==1)
                break;
            i++;
        }            
        t=i+1;
        //reverse
        for(i=t-1;i>t-1-i;i--)
        {
            int temp=IncSeq[i];
            IncSeq[i]=IncSeq[t-i-1];
            IncSeq[t-i-1]=temp;
        }
    }
    else if(seq=="Hibbard")//worst N^3/2, avg N^5/4
    {
        i=0;
        IncSeq[i]=1;
        while(1)//IncSeq[i] = 2^(i+1)-1
        {
            IncSeq[i]=(IncSeq[i-1]+1)*2-1;
            if(IncSeq[i]>n)
                break;
            i++;
        }
        t=i;
    }

    //shell sort based on this sequence
    for(k=t-1;k>=0;k--)
    {
        //do hk-sort
        for(pos=IncSeq[k];pos<n;pos+=1)
        {
            int temp=a[pos];
            for(j=pos;j>=IncSeq[k]&&a[j-IncSeq[k]]>temp;j-=IncSeq[k])
            {
                a[j]=a[j-IncSeq[k]];
            }
            a[j]=temp;
        }
    }
}