/******************************************************************************************
* Data Structures in C++ -- 随机生成和随机组成 BST
* 丁酉鸡年三月 2017/4/16 19:57
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/
#include<vector>

void RandomGeneration(int n) // 随机生成
{
	int * array = new int[n];
	for (int i = 0;i < n;++i)
		array[i] = i + 1;

}

void RandomComposition(int n) // 随机组成
{
	std::vector<int> vector;
	vector.push_back(1);

}