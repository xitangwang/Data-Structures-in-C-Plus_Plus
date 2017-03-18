/******************************************************************************************
* Data Structures in C++ -- �沨�����ʽ����ӿڼ�ʵ��
* ���ϼ������� 2017/2/27 16:36
* @author ������, xtwyzh@gmail.com, xtwroot.com
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
	case '+': //��
		return a + b;
	case '-': //��
		return a - b;
	case '*': //��
		return a * b;
	case '/': //��
		return a / b;
	case '^': //�˷�
		return pow(a, b);
	default:
		break;
	}
}

float calChildu(char op, float b)
{
	return facI(static_cast<int>(b));
}

//��������
void printChar(char& p)
{
	('\0' == p) ? printf("\\0") : printf("%c", p);
}

//��ʾ���ʽ�����չ
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

// ��ȡ�ַ��������֣�ֱ���������ַ�
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

// �������ת������
Operator optr2rank(char optr) 
{
	switch (optr) {
	case '+': return ADD; //��
	case '-': return SUB; //��
	case '*': return MUL; //��
	case '/': return DIV; //��
	case '^': return POW; //�˷�
	case '!': return FAC; //�׳�
	case '(': return L_P; //������
	case ')': return R_P; //������
	case '\0': return EOE; //��ʼ������ֹ��
	default: exit(-1); //δ֪�����
	}
}

// �Ƚ��������֮������ȼ�
char orderBetween(char optr1, char optr2) 
{
	return pri[optr2rank(optr1)][optr2rank(optr2)];
}

// ������������RPNĩβ
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

//�����������RPNĩβ
void append(char*& rpn, char optr) 
{
	int n = strlen(rpn);
	rpn = static_cast<char*>(realloc(rpn, sizeof(char) * (n + 3)));
	sprintf(rpn + n, "%c ", optr);rpn[n + 2] = '\0';
}


float evaluate(char* S, char*& RPN) { //�ԣ����޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽRPN
	Stack<float> opnd; Stack<char> optr; //������ջ�������ջ /*DSA*/�κ�ʱ�̣�����ÿ������Ԫ��֮�����Сһ��
	/*DSA*/ char* expr = S;
	optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
	while (!optr.empty()) { //�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
		if (isdigit(*S)) { //����ǰ�ַ�Ϊ����������
			readNumber(S, opnd); append(RPN, opnd.top()); //��������������������RPNĩβ
		}
		else //����ǰ�ַ�Ϊ���������
			switch (orderBetween(optr.top(), *S)) { //������ջ�������֮�����ȼ��ߵͷֱ���
			case '<': //ջ����������ȼ�����ʱ
				optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ
				break;
			case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
				optr.pop(); S++; //�����Ų�������һ���ַ�
				break;
			case '>': { //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
				char op = optr.pop(); append(RPN, op); //ջ���������ջ��������RPNĩβ
				if ('!' == op) { //������һԪ�����
					float pOpnd = opnd.pop(); //ֻ��ȡ��һ������������
					opnd.push(calChildu(op, pOpnd)); //ʵʩһԪ���㣬�����ջ
				}
				else { //������������Ԫ�������
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //ȡ����ǰ������ /*DSA*/���ʣ��ɷ�ʡȥ������ʱ������
					opnd.push(calChildu(pOpnd1, op, pOpnd2)); //ʵʩ��Ԫ���㣬�����ջ
				}
				break;
			}
			default: exit(-1); //���﷨���󣬲�������ֱ���˳�
			}//switch
		/*DSA*/displayProgress(expr, S, opnd, optr, RPN);
	}//while
	return opnd.pop(); //�������������ļ�����
}