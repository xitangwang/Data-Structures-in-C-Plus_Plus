/******************************************************************************************
* Data Structures in C++ -- PA��һ�� ��Χ��ѯ(Range)
* ���ϼ������� 2017/4/6 8:50
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/*Descriptioin
Let S be a set of n integral points on the x-axis. For each given interval [a, b], you are asked to count the points lying inside.

Input
The first line contains two integers: n (size of S) and m (the number of queries).

The second line enumerates all the n points in S.

Each of the following m lines consists of two integers a and b and defines an query interval [a, b].

Output
The number of points in S lying inside each of the m query intervals.

Example
Input

5 2
1 3 7 9 11
4 6
7 12
Output

0
3
Restrictions
0 <= n, m <= 5 * 10^5

For each query interval [a, b], it is guaranteed that a <= b.

Points in S are distinct from each other.

Coordinates of each point as well as the query interval boundaries a and b are non-negative integers not greater than 10^7.

Time: 2 sec

Memory: 256 MB

����
��������n���㣬������һ������ [a, b]���Լ����������ڵĵ�����

����
��һ�а��������������������n����ѯ�Ĵ���m��

�ڶ��а���n������Ϊ����������ꡣ

����m�У�������������������ѯ��������ұ߽�a��b��

���
��ÿ�β�ѯ��������ڱ�����[a, b]�ڵ�ĸ�����

����
��Ӣ������

����
0 �� n, m �� 5��105

����ÿ�β�ѯ������[a, b]������a �� b

��������껥��

��������ꡢ��ѯ����ı߽�a��b����Ϊ������10^7�ķǸ�����

ʱ�䣺2 sec

�ڴ棺256 MB*/

#include<cstdio>
#include <cstdlib>

void Range()
{
	int numCount;
	int time;
	scanf("%d", &numCount);scanf("%d", &time);
	int *num = new int[numCount];
	int(*range)[2] = new int[time][2];
	for(int i = 0;i < numCount;++i)
		scanf("%d",&num[i]);
	for (int i = 0;i < time;++i)
	{
		scanf("%d", &range[i][0]);scanf("%d", &range[i][1]);
	}

	for (int i = 0;i < time;++i)
	{
		int count = 0;
		for (int j = 0; j < numCount; ++j)
		{
			if (num[j] >= range[i][0] && num[j] <= range[i][1])
				++count;
		}
		printf("%d\n",count);
	}
}

int main()
{
	Range();
	system("pause");
	return 0;
}
