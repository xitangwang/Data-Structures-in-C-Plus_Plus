/******************************************************************************************
* Data Structures in C++ -- BinTree 测试、演示用小工具
* 丁酉鸡年二月 2017/3/17 21:16
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<typeinfo.h>
#include"comparator.h"

#include"rand.h"
#include"hailstone_elem.h"
#include"double_elem.h"
#include"release.h"

#if defined(DAS_DEBUG) //编译开关，控制调试输出
#define DSA(x) { x }   //输出
#else
#define DAS(x)   //不输出
#endif


