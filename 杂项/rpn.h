/******************************************************************************************
* Data Structures in C++ -- 逆波兰表达式运算接口及实现
* 丁酉鸡年正月 2017/2/27 16:36
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#pragma warning(disable : 4996)

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#include"../stack/Stack@list.h"
#include"priority.h"
#include <memory>
#include "../UniPrint/print.h"

inline __int64 facI(int n) { __int64 f = 1;while (n > 1) f *= n--;return f; }

float calChildu(float a, char op, float b)
{
	switch (op)
	{
	case '+': //加
		return a + b;
	case '-': //减
		return a - b;
	case '*': //乘
		return a * b;
	case '/': //除
		return a / b;
	case '^': //乘方
		return pow(a, b);
	default:
		break;
	}
}

float calChildu(char op, float b)
{
	return facI(static_cast<int>(b));
}

//输出运算符
void printChar(char& p)
{
	('\0' == p) ? printf("\\0") : printf("%c", p);
}

//显示表达式处理进展
void displayProgress(char* expr, char* pCh, Stack<float>& opndStk, Stack<char>& optrStk, char* rpn)
{
	system("cls");
	printf("\n");
	for (char *p = expr;'\0' != *p;p++) printf(" %c", *p);printf(" $\n");
	for (char *p = expr;p < pCh;p++)printf("  ");
	if('\0' != *(pCh - 1))
	{
		for (char* p = pCh;'\0' != *p;p++)printf(" %c", *p);printf(" $");
	}
	printf("\n");
	for (char* p = expr;p < pCh;p++) printf("--");printf(" ^\n\n");
	print(optrStk);printf("\n");
	print(opndStk);printf("\n");
	printf("RPN:\n %s\n\n", rpn);
	getchar();
}

// 读取字符串的数字，直到非数字字符
void readNumber(char*& S, Stack<float>& opnd)
{
	bool hasPoint = false;    
	float num = atoi(S);++S;
	while (isdigit(*S) || *S == '.')
	{
		if (*S == '.')
			hasPoint = true;
		else
		{
			if (hasPoint)
				num += atoi(S);
			else
				num = num * 10 + atoi(S);
		}
		++S;
	}
	opnd.push(num);
}

// 由运算符转译出编号
Operator optr2rank(char optr) 
{
	switch (optr) {
	case '+': return ADD; //加
	case '-': return SUB; //减
	case '*': return MUL; //乘
	case '/': return DIV; //除
	case '^': return POW; //乘方
	case '!': return FAC; //阶乘
	case '(': return L_P; //左括号
	case ')': return R_P; //右括号
	case '\0': return EOE; //起始符与终止符
	default: exit(-1); //未知运算符
	}
}

// 比较两运算符之间的优先级
char orderBetween(char optr1, char optr2) 
{
	return pri[optr2rank(optr1)][optr2rank(optr2)];
}

// 将操作数接至RPN末尾
void append(char*& rpn, float opnd) 
{
	int n = strlen(rpn);
	char buf[64];
	if (opnd != static_cast<float>(static_cast<int>(opnd)))
		sprintf(buf, "%.2f \0", opnd);
	else
		sprintf(buf, "%d \0", static_cast<int>(opnd));
	rpn = static_cast<char*>(realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)));
	strcat(rpn, buf);
}

//将运算符接至RPN末尾
void append(char*& rpn, char optr) 
{
	int n = strlen(rpn);
	rpn = static_cast<char*>(realloc(rpn, sizeof(char) * (n + 3)));
	sprintf(rpn + n, "%c ", optr);rpn[n + 2] = '\0';
}


float evaluate(char* S, char*& RPN) { //对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
	Stack<float> opnd; Stack<char> optr; //运算数栈、运算符栈 /*DSA*/任何时刻，其中每对相邻元素之间均大小一致
	/*DSA*/ char* expr = S;
	optr.push('\0'); //尾哨兵'\0'也作为头哨兵首先入栈
	while (!optr.empty()) { //在运算符栈非空之前，逐个处理表达式中各字符
		if (isdigit(*S)) { //若当前字符为操作数，则
			readNumber(S, opnd); append(RPN, opnd.top()); //读入操作数，并将其接至RPN末尾
		}
		else //若当前字符为运算符，则
			switch (orderBetween(optr.top(), *S)) { //视其与栈顶运算符之间优先级高低分别处理
			case '<': //栈顶运算符优先级更低时
				optr.push(*S); S++; //计算推迟，当前运算符进栈
				break;
			case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
				optr.pop(); S++; //脱括号并接收下一个字符
				break;
			case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
				char op = optr.pop(); append(RPN, op); //栈顶运算符出栈并续接至RPN末尾
				if ('!' == op) { //若属于一元运算符
					float pOpnd = opnd.pop(); //只需取出一个操作数，并
					opnd.push(calChildu(op, pOpnd)); //实施一元计算，结果入栈
				}
				else { //对于其它（二元）运算符
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //取出后、前操作数 /*DSA*/提问：可否省去两个临时变量？
					opnd.push(calChildu(pOpnd1, op, pOpnd2)); //实施二元计算，结果入栈
				}
				break;
			}
			default: exit(-1); //逢语法错误，不做处理直接退出
			}//switch
		/*DSA*/displayProgress(expr, S, opnd, optr, RPN);
	}//while
	return opnd.pop(); //弹出并返回最后的计算结果
}