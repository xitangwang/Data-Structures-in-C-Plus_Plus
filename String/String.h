/******************************************************************************************
* Data Structures in C++ -- 字符串的匹配算法
* 丁酉鸡年七月 2017/9/10 14:47
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include<cstring>



/****************************************************************************************** 
* Text     :  0   1   2   .   .   .   i-j .   .   .   .   i   .   .   n-1
*             ------------------------|-------------------|------------ 
* Pattern  :                          0   .   .   .   .   j   .   . 
*                                     |-------------------| 
******************************************************************************************/
int match_1(char* P, char* T)
{
	size_t n = strlen(T), i = 0;
	size_t m = strlen(P), j = 0;
	while (j < m && i < n)
		if (T[i] == P[j])
		{ ++i;++j; }
		else 
		{ i -= j - 1;j = 0; }
	return i - j; // 若查找失败，经复位后返回的就是-1
}

/******************************************************************************************
* Text     :  0   1   2   .   .   .   i i+1   .   .   .   i+j   .   .   n-1
*             ------------------------|-------------------|------------
* Pattern  :                          0   .   .   .   .   j   .   .
*                                     |-------------------|
******************************************************************************************/
int match_2(char* P, char* T)
{
	size_t n = strlen(T), i = 0;
	size_t m = strlen(P), j = 0;
	while (j < m && i < n)
	{
		if (T[i + j] == P[j])
		{ ++j; }
		else 
		{ ++i;j = 0; }
	}
	return i;
}

int* buildNext(char* P)
{
	int length = strlen(P);
	int *next = new int[length];
	int index = 0;
	next[0] = -1;
	for (size_t i = 1; i < length; i++)
	{
		if (P[i] == P[0])
			do
				next[i] = index;
			while (P[++i] == P[++index] && i < length);
		else
			index = 0;
		next[i] = index;
	}
	return next;
}

int match_KMP(char* P, char* T)
{
	int* next = buildNext(P);
	int m = strlen(P);int i = 0;
	int n = strlen(T);int j = 0;
	while (j < m && i < n) 
	{
		if (0 > j || P[j] == T[i])
		{
			++i;++j;
		}
		else
		{
			j = next[j];
		}
	}
	delete[] next;
	return i - j;
}

