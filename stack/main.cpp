/******************************************************************************************
* Data Structures in C++ -- stack 测试用例
* 丁酉鸡年正月 2017/2/26 9:33
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include<iostream>
#include"Stack@list.h"
#include "../_share/rand.h"
#include"../UniPrint/print.h"
#include "StackShuffle.h"

using namespace std;

int testID = 0;
/******************************************************************************************
* 测试栈
******************************************************************************************/
template <typename T>
void testStack(int n)
{
	Stack<T> S;
	printf("\n ==== Test %2d. Growing stack\n", testID++);
	while (S.size() < n)
	{
		T e = rand() % (T)2 * n;
		if(S.empty() || (30 < (rand() % 100))) // %70概率入栈
		{
			printf("pushing ");print(e);printf("...\n");
			S.push(e);
		}
		else // %30概率出栈
		{
			printf("poping with ... ");print(S.pop());printf("\n");
		}
		print(S);
	}
	printf("\n ==== Test %2d.Shrinking stack\n", testID++);
	while (!S.empty())
	{
		T e = dice((T)2 * n);
		if(70 < dice(100)) // %30概率入栈
		{
			printf("pushing ");print(e);printf("...\n");
			S.push(e);
		}
		else // %70概率出栈
		{
			printf("poping ");print(S.pop());printf("...\n");
		}
		print(S);
	}
}

bool paren(const char exp[])
{
	Stack<char> S;
	for (int i = 0;exp[i];i++)
		switch (exp[i])
		{
		case '(':case '[':case '{':S.push(exp[i]);
			break;
		case ')':if ((S.empty()) || ('(' != S.pop())) return false;
			break;
		case ']':if ((S.empty()) || ('[' != S.pop())) return false;
			break;
		case '}':if ((S.empty()) || ('{' != S.pop())) return false;
			break;
		default:break;
		}
	return S.empty(); //整个表达式扫描过后，栈中若残留（左）括号，则不匹配，否则（栈空）匹配
}

int main1(int argc, char* argv[])
{
	// 测试栈
	srand((unsigned int)time(NULL)); // 设置种子
	testStack<int>(10);
	// 测试括号匹配
	char expression[] = "a / (b [ i - 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char expression_true[] = "{ ( ) ( ) ( [ ] ( ) ) }";
	char expression_false[] = "( ( ( ) ) ( ( ))";

	cout << "expression_true :" << paren(expression_true) << endl;
	cout << "expression_false :" << paren(expression_false) << endl;
	cout << "expression :" << paren(expression) << endl;

	// 测试栈混洗
	Stack<char> A;
	Stack<char> S;
	for (int i = 65;i < 91;++i)
	{
		A.push(static_cast<char>(i));
	}
	cout << "Stack A:";print(A);
	shuffle(A, S);
	cout << "Stack S:";print(S);

	cin.get();
	return 0;
}
