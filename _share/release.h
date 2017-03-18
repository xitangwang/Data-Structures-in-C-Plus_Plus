/******************************************************************************************
* Data Structures in C++ -- �ͷų�Ա������ռ�Ŀռ��release����
* ���ϼ������ 2017/3/18 9:31
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include <typeinfo.h>

/******************************************************************************************
 * �б������Ƚṹ�ڵĽڵ��У����Դ�Ż������ͻ�������
 * ���ձ���Լ��������Ч�ʵĿ��ǣ����ں�һ���ͨ��ֻ��������ָ��
 * ��ˣ�������ṹ����֮ǰ����Ҫ�����ͷ���Щ��Ա������ռ�Ŀռ�
 * �˴�������C++��ƫ�ػ����������������������������Ӧ����
 ******************************************************************************************/

template <typename T> struct Cleaner
{
	static void clean(T x)	//�൱�ݹ��
	{
#ifdef _DEBUG
		static int n = 0;
		if (7 > strlen(typeid(T).name()))	//��������һ�ź��ԣ�ֻ�����������
		{
			printf("\t<%s>[%d]", typeid(T).name(), ++n);
			print(x);
			printf("purged\n");
		}
#endif
	}
};

template <typename T> struct Cleaner<T*>
{
	static void clean(T* x)
	{
		if (x) { delete x; }	//������а���ָ�룬�ݹ��ͷ�
#ifdef _DEBUG
		static int n = 0;
		printf("\t <%p>[%d] released\n", typeid(T*).name(), ++n);
#endif
	}
};

template <typename T> void release(T x) { Cleaner<T>::clean(x); }