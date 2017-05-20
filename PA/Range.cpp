/******************************************************************************************
* Data Structures in C++ -- PA第一题 范围查询(Range)
* 丁酉鸡年三月 2017/4/6 8:50
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
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

描述
数轴上有n个点，对于任一闭区间 [a, b]，试计算落在其内的点数。

输入
第一行包括两个整数：点的总数n，查询的次数m。

第二行包含n个数，为各个点的坐标。

以下m行，各包含两个整数：查询区间的左、右边界a和b。

输出
对每次查询，输出落在闭区间[a, b]内点的个数。

样例
见英文题面

限制
0 ≤ n, m ≤ 5×105

对于每次查询的区间[a, b]，都有a ≤ b

各点的坐标互异

各点的坐标、查询区间的边界a、b，均为不超过10^7的非负整数

时间：2 sec

内存：256 MB*/

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
