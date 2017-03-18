/******************************************************************************************
* Data Structures in C++ -- 寻路算法的实现
* 丁酉鸡年二月 2017/3/1 17:15
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "Cell.h"
#include <cstdlib>
#include "../stack/Stack@list.h"

//邻格查询
inline Cell* neighbor(Cell* cell)
{
	switch (cell->outgoing)
	{
	case EAST:return cell + LABY_MAX;
	case SOUTH:return cell + 1;
	case WEST:return cell - LABY_MAX;
	case NORTH:return cell - 1;
	default:exit(-1);
	}
}

//邻格转入
inline Cell* advance(Cell* cell)
{
	Cell* next;
	switch (cell->outgoing)
	{
	case EAST:	next = cell + LABY_MAX;	next->incoming = WEST;	break;
	case SOUTH:	next = cell + 1;		next->incoming = NORTH; break;
	case WEST:	next = cell - LABY_MAX; next->incoming = EAST;	break;
	case NORTH:	next = cell - 1;		next->incoming = SOUTH; break;
	default:exit(-1);
	}
	return next;
}

//算法实现
bool labyrinth(Cell Laby[LABY_MAX][LABY_MAX],Cell* s,Cell* t)
{
	if ((AVAILABLE != s->status) || (AVAILABLE != t->status))
		return false;
	Stack<Cell*> path;
	s->incoming = UNKNUWN;s->status = ROUTE;path.push(s);
	do
	{
		Cell* c = path.top();
		if (c == t)return true;
		while (NO_WAY > (c->outgoing = nextESWN(c->outgoing)))
			if (AVAILABLE == neighbor(c)->status) break;
		if(NO_WAY <= c->outgoing)
		{
			c->status = BACKTRACKED;
			c = path.pop();
		}
		else
		{
			path.push(c = advance(c));
			c->outgoing = UNKNUWN;
			c->status = ROUTE;
		}
	}
	while (!path.empty());
}

