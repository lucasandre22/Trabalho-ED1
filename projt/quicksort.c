#include "quicksort.h"
#include <stdlib.h>
#include <stdio.h>

void _swap(char v[],int barreira,int j)
{
    int aux;
    aux=v[barreira];
    v[barreira]=v[j];
    v[j]=aux;
}

int _partition(char v[],int begin,int end)
{
    int j,barreira=begin-1,pivo=v[end];
    for(j=begin;j<=end;j++)
    {
        if(v[j]<=pivo)
            _swap(v,++barreira,j);
    }
    return barreira;


}

void quick_sort(char v[], int begin, int end)
{
    int p;
    if(begin>=end)return;
    p=_partition(v,begin,end);
    quick_sort(v,begin,p-1);
    quick_sort(v,p+1,end);
}

/*int main()
{
    int v[MAX],j,n;
    scanf("%d", &n);
    for(j=0;j<n;j++)
        scanf("%d", &v[j]);
    quick_sort(v,0,n-1);
    for(j=0;j<n;j++)
    {
        printf("%s%d", j ? " ":"", v[j]);
    }
    return 0;
}*/

