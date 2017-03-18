/******************************************************************************************
* Data Structures in C++ -- �������������
* ���ϼ������� 2017/2/26 11:27
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/


#pragma once

#include<iostream>
#include<time.h> // ͨ���õ�ǰʱ�������������

static int dice(int range) { return rand() % range; }
static int dice(int lo, int hi) { return lo + rand() % (hi - lo); }
static float dice(float range) { return rand() % (1000 * static_cast<int>(range)) / static_cast<int>(1000); }
static double dice(double range) { return rand() % (1000 * static_cast<int>(range)) / static_cast<double>(1000.); }
static char dice(char range) { return static_cast<char>(32 + rand() % 96); }
