/******************************************************************************************
* Data Structures in C++ -- ɢ�б�Ӧ��
* ���ϼ������� 2017/9/8 17:04
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include "../HashTable/HashTable.h"
#include <iostream>

/*
 * Ͱ���򣬸���[0, M)�ڵ�n������������n <= M��
 */
void BucketSort(int min,int max,int array[],int n)
{
	HashTable<int, int> hash(max - min);
	for (int i = 0; i < n; ++i)
	{
		hash.put(hashCode(i), array[i]);
	}
	int index = 0;
	for (int i = 0; i < hash.size(); ++i)
	{
		if(hash.get(i) != nullptr)
		{
			array[index++] = *hash.get(i);
		}
	}
}

void main()
{
	int array[] = { 3,9,5,8,2 };
	BucketSort(2, 9, array, 5);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << array[i] << std::endl;
	}
	std::cin.get();
}
