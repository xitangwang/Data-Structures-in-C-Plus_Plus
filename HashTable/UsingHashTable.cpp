/******************************************************************************************
* Data Structures in C++ -- 散列表应用
* 丁酉鸡年七月 2017/9/8 17:04
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include "../HashTable/HashTable.h"
#include <iostream>

/*
 * 桶排序，给定[0, M)内的n个互异整数（n <= M）
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
