/******************************************************************************************
* Data Structures in C++ -- 迷宫格点类的定义
* 丁酉鸡年二月 2017/3/1 17:05
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

typedef enum{AVAILABLE,ROUTE,BACKTRACKED,WALL} Status; // 迷宫单元格的状态

typedef enum{UNKNUWN,EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN; // 单元的相对邻接方向
// 未定、东、南、西、北、无路可通

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }

struct Cell
{
	int x, y;Status status;
	ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];//迷宫
