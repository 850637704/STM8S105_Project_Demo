
#include "mymath.h"
#include <stdlib.h>

double my_pow(double num,int n)													// 计算num的n次幂，其中n为整数
{
	double powint=1;
	int i;
	for(i=1;i<=n;i++) powint*=num;
	return powint;
}
//获取到最小为m，最大为n，总数为k个的不同随机数的函数
void get_rand(uint8_t *a, uint8_t m, uint8_t n, uint8_t k)//结果存在a中 
{ 
    uint8_t i,j,t; 
    for(i = 0; i < k; ) 
    {
        t = rand()%(n-m+1)+m; 
        for(j = 0; j < i; j ++) 
            if(a[j] == t) break; 
        if(j == i)//不重复 
            a[i++] = t;//记录随机数。 
    } 
}
/*--------------Write-by-xiao-kai-2017-10-13-09-28----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/



