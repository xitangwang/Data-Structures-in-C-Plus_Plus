/******************************************************************************************
* Data Structures in C++ -- 根据运算符的优先级，实现表达式求值
* 丁酉鸡年正月 2017/2/26 21:25
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "Stack@list.h"
#include <cctype>
#include <cstdlib>
#include "../杂项/rpn.h"

float evaluate(char * S,char *& PRN)
{
	Stack<float> opnd;Stack<char> optr;
	optr.push('\0');
	while(!optr.empty())
	{
		if(isdigit(*S))
		{
			readNumber(S, opnd);append(PRN, opnd.top());
		}
		else
			switch (orderBetween(optr.top(),*S))
			{
			case '<':
				optr.push(*S);S++;
				break;
			case '=':
				optr.pop();S++;
				break;
			case '>':
				{
					char op = optr.pop();append(PRN, op);
					if ('!' == op)
					{
						float pOpnd = opnd.pop();
						opnd.push(calcu(op, pOpnd));
					}
					else
					{
						float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
						opnd.push(calcu(pOpnd1, op, pOpnd2));
					}
					break;
				}
			default:exit(-1);
			} // swich
		return opnd.pop();
	}
}
