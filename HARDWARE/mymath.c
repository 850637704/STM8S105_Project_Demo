
#include "mymath.h"
#include <stdlib.h>

double my_pow(double num,int n)													// ����num��n���ݣ�����nΪ����
{
	double powint=1;
	int i;
	for(i=1;i<=n;i++) powint*=num;
	return powint;
}
//��ȡ����СΪm�����Ϊn������Ϊk���Ĳ�ͬ������ĺ���
void get_rand(uint8_t *a, uint8_t m, uint8_t n, uint8_t k)//�������a�� 
{ 
    uint8_t i,j,t; 
    for(i = 0; i < k; ) 
    {
        t = rand()%(n-m+1)+m; 
        for(j = 0; j < i; j ++) 
            if(a[j] == t) break; 
        if(j == i)//���ظ� 
            a[i++] = t;//��¼������� 
    } 
}
/*--------------Write-by-xiao-kai-2017-10-13-09-28----QQ-850637704------------*/
/*-------------------------Always-have-a-nice-day-----------------------------*/



