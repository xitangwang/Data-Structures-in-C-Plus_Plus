///******************************************************************************************
//* Data Structures in C++ -- rpn - ��������
//* ���ϼ������ 2017/2/28 21:23
//* @author ������, xtwyzh@gmail.com, xtwroot.com
//* xtwroot Copyright (c) 2017. All rights reserved.
//******************************************************************************************/
//
//#include"../����/rpn.h"
//
////�޳�s[]�еĿո�
//char* removeSpace(char* s)
//{
//	char* p = s, *q = s;
//	while (true)
//	{
//		while (isspace(*q))q++;
//		if('\0' == *q)
//		{
//			*p = '\0';
//			return s;
//		}
//		*p++ = *q++;
//	}
//}
//
//int main2(int argc,char* argv[])
//{
//	for(auto i = 1;i<argc;i++)
//	{
//		system("cls");
//		printf("\nPress any key to evaluste:[%s]\a\n",argv[i]);
//		getchar();
//		auto rpn = static_cast<char *>(malloc(sizeof(char) * 1)); rpn[0] = '\0';
//		float value = evaluate(removeSpace(argv[i]), rpn);
//		printf("EXPR\t:%s\n", argv[i]);
//		printf("Value\t= %.1f = %d\n", value, static_cast<int>(value));
//		free(rpn);rpn = nullptr;
//		getchar();
//	}
//	return 0;
//}
