/******************************************************************************************
* Data Structures in C++ -- 皇后类的定义
* 丁酉鸡年二月 2017/3/1 11:23
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../stack/Stack@list.h"

int nCheck = 0;
int nSolu = 0;

struct Queen
{
	int x, y;
	Queen(int xx = 0, int yy = 0) :x(xx), y(yy) {};
	bool operator==(Queen const& q) const
	{
		return (x == q.x) // 行冲突
			|| (y == q.y) // 列冲突
			|| (x + y == q.x + q.y) // 沿正对角线冲突
			|| (x - y == q.x - q.y); // 沿反对角线冲突
	}
	bool operator!=(Queen const& q) const { return !(*this == q); }
};

void placeQueens(int N)
{
	Stack<Queen> solu;
	Queen q(0, 0);
	do
	{
		if(N <= solu.size() || N <= q.y)
		{
			q = solu.pop();q.y++;
		}else
		{
			while ((q.y < N) && (0 <= solu.find(q)));
			{q.y++;nCheck++;}
			if(N > q.y)
			{
				solu.push(q);
				if (N <= solu.size()) nSolu++;
				q.x++;q.y = 0;
			}
		}
	} while ((0 < q.x) || (q.y < N));
}