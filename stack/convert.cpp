/******************************************************************************************
* Data Structures in C++ -- convertor
* 丙申猴年腊月廿八 2017/1/25 17:33
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"Stack@list.h"

// 递归版进制转换器
void convert(Stack<char>& S,__int64 n,int base)
{
	static char digit[]
		= { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	if(0<n)
	{
		convert(S, n / base, base);
		S.push(digit[n%base]);
	}
}
/*
// 迭代版进制转换器
void convert(Stack<char>& S,__int64 n,int base)
{
	static char digit[]
		= { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while(n>0)
	{
		int remainder = static_cast<int>(n % base); S.push(digit[remainder]);
		n /= base;
	}
}
*/