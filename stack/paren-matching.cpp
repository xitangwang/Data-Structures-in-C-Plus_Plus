///******************************************************************************************
//* Data Structures in C++ -- paren - matching
//* ���ϼ�������ʮ�� 2017/2/12 21:01
//* @author ������, xtwyzh@gmail.com, xtwroot.com
//* xtwroot Copyright (c) 2017. All rights reserved.
//******************************************************************************************/
//
//#include"Stack@vector.h"
//
//void trim(const char exp[], int & lo, int & hi)
//{                                                                               
//	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))
//		lo++;
//	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))
//		hi--;
//}
//
//int divide(const char exp[], int lo, int hi)
//{
//	int mi = lo;int crc = 1;
//	while((0 < crc) && (++mi < hi))
//	{
//		if (exp[mi] == ')') crc--;
//		if (exp[mi] == '(') crc++;
//	}
//	return mi;
//}
//
//bool paren(const char exp[], int lo, int hi)
//{
//	trim(exp, lo, hi);
//	if (lo > hi)
//		return true;
//	if (exp[lo] != '(')
//		return false;
//	if (exp[hi] != ')')
//		return false;
//	int mi = divide(exp, lo, hi);
//	if (mi > hi)return false;
//	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);
//}
//
//
///*
//bool paren(const char exp[], int lo, int hi)
//{
//	Stack<char> S;
//	for(int i = 0;exp[i];i++)
//		switch (exp[i])
//		{
//		case '(':case '[':case '{':S.push(exp[i]);
//			break;
//		case ')':if ((S.empty()) || ('(' != S.pop())) return false;
//			break;
//		case ']':if ((S.empty()) || ('[' != S.pop())) return false;
//			break;
//		case '}':if ((S.empty()) || ('{' != S.pop())) return false;
//			break;
//		default:break;
//		}
//	return S.empty(); //�������ʽɨ�����ջ���������������ţ���ƥ�䣬����ջ�գ�ƥ��
//}
//*/
//// ��ʼ