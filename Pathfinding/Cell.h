/******************************************************************************************
* Data Structures in C++ -- �Թ������Ķ���
* ���ϼ������ 2017/3/1 17:05
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

typedef enum{AVAILABLE,ROUTE,BACKTRACKED,WALL} Status; // �Թ���Ԫ���״̬

typedef enum{UNKNUWN,EAST,SOUTH,WEST,NORTH,NO_WAY} ESWN; // ��Ԫ������ڽӷ���
// δ���������ϡ�����������·��ͨ

inline ESWN nextESWN(ESWN eswn) { return ESWN(eswn + 1); }

struct Cell
{
	int x, y;Status status;
	ESWN incoming, outgoing;
};

#define LABY_MAX 24
Cell laby[LABY_MAX][LABY_MAX];//�Թ�
