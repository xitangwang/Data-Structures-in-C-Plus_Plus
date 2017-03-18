/******************************************************************************************
* Data Structures in C++ -- 
* 丁酉鸡年二月 2017/3/1 11:01
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../stack/Stack@list.h"
#include"rpn.h"
#include <cctype>

float rpnEvaluation(char* expr)
{
	Stack<float> S;
	while('\0' != *expr)
	{
		if (isdigit(*expr))
			readNumber(expr,S);
		else
		{
			if ('^' == *expr)
				calChildu(*expr, S.pop());
			else
			{
				float num1 = S.pop(), num2 = S.pop();
				calChildu(num2, *expr, num1);
			}
		}
		++expr;
	}
	return S.top();
}
