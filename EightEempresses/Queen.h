/******************************************************************************************
* Data Structures in C++ -- �ʺ���Ķ���
* ���ϼ������ 2017/3/1 11:23
* @author ������, xtwyzh@gmail.com, xtwroot.com
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
		return (x == q.x) // �г�ͻ
			|| (y == q.y) // �г�ͻ
			|| (x + y == q.x + q.y) // �����Խ��߳�ͻ
			|| (x - y == q.x - q.y); // �ط��Խ��߳�ͻ
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