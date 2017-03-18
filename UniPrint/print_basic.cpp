/******************************************************************************************
* Data Structures in C++ -- 基本类型的输出方法实现
* 丁酉鸡年正月 2017/2/26 10:36
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"print.h"

void UniPrint::p(int e) { printf("%04d", e); }
void UniPrint::p(float e) { printf("%4.1f", e); }
void UniPrint::p(double e) { printf("%4.1f", e); }
void UniPrint::p(char e) { printf("%c", (31 < e) && (e < 128) ? e : '$'); }

template <typename T>
void UniPrint::p(T& s)
{
	printf("%s[%d]*%d:\n", typeid(s).name, &s, s.size()); // 基本信息
	s.traverse(print);
	printf("\n");
}
