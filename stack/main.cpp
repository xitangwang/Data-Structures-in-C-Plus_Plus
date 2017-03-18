/******************************************************************************************
* Data Structures in C++ -- stack ��������
* ���ϼ������� 2017/2/26 9:33
* @author ������, xtwyzh@gmail.com, xtwroot.com
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
* ����ջ
******************************************************************************************/
template <typename T>
void testStack(int n)
{
	Stack<T> S;
	printf("\n ==== Test %2d. Growing stack\n", testID++);
	while (S.size() < n)
	{
		T e = rand() % (T)2 * n;
		if(S.empty() || (30 < (rand() % 100))) // %70������ջ
		{
			printf("pushing ");print(e);printf("...\n");
			S.push(e);
		}
		else // %30���ʳ�ջ
		{
			printf("poping with ... ");print(S.pop());printf("\n");
		}
		print(S);
	}
	printf("\n ==== Test %2d.Shrinking stack\n", testID++);
	while (!S.empty())
	{
		T e = dice((T)2 * n);
		if(70 < dice(100)) // %30������ջ
		{
			printf("pushing ");print(e);printf("...\n");
			S.push(e);
		}
		else // %70���ʳ�ջ
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
	return S.empty(); //�������ʽɨ�����ջ���������������ţ���ƥ�䣬����ջ�գ�ƥ��
}

int main1(int argc, char* argv[])
{
	// ����ջ
	srand((unsigned int)time(NULL)); // ��������
	testStack<int>(10);
	// ��������ƥ��
	char expression[] = "a / (b [ i - 1 ] + c [ i + 1 ] [ j - 1 ] ) * 2";
	char expression_true[] = "{ ( ) ( ) ( [ ] ( ) ) }";
	char expression_false[] = "( ( ( ) ) ( ( ))";

	cout << "expression_true :" << paren(expression_true) << endl;
	cout << "expression_false :" << paren(expression_false) << endl;
	cout << "expression :" << paren(expression) << endl;

	// ����ջ��ϴ
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
