/******************************************************************************************
* Data Structures in C++ -- Huffman编树的实现
* 丁酉鸡年二月 2017/3/28 11:25
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include"../BinTree/Bintree.h"
#include <ctime>
typedef BinTree<char> PFCTree; // PFC树

#include "../vector/vector.h"
typedef Vector<PFCTree*> PFCForest; // PFC森林

#include"../Bitmap/Bitmap.h" //使用位图实现二进制编码串
#include <map>
typedef std::map<char, char*> PFCTable; // PFC编码表，词条格式为：（key = 字符,value = 编码串)

#define N_CHAR (0x80 - 0x20) // 只考虑可打印的字符

// 初始化PFC森林
PFCForest* initForest()
{
	PFCForest* forest = new PFCForest;
	for (int i = 0;i < N_CHAR;i++) // 对每一个可打印的字符(0x20,0x80)
	{
		forest->insert(i, new PFCTree());
		(*forest)[i]->insertAsRoot(0x20 + i); // 只包含对应的一个（根、叶）节点
	}
	return forest; // 返回包含N_CHAR颗树的森林，其中每棵树各包含一个字符
}

// 构造PFC编码树
PFCTree* generateTree(PFCForest* forest)
{
	srand(static_cast<unsigned int>(time(nullptr))); // 这里将随机取树合并，故先设置随机种子
	while (1 < forest->size()) // 共做|forest| - 1次合并
	{
		PFCTree* s = new PFCTree;s->insertAsRoot('^'); // 创建新树（根标记为"^"）
		Rank r1 = rand() % forest->size(); // 随机选取r1,且
		s->attachAsLC(s->root(), (*forest)[r1]); // 作为左子树接入后
		forest->remove(r1); // 随即剔除
		Rank r2 = rand() % forest->size(); // 随机选取r2，且
		s->attachAsRC(s->root(), (*forest)[r2]); // 作为右子树接入后
		forest->remove(r2); // 随即剔除
		forest->insert(forest->size(), s); // 合并后的PFC树重新接入PFC森林
	}
	return (*forest)[0]; // 至此，森林种尚存的一棵树，即全局PFC编码树
}

// 生成PFC编码表
void generateCT // 通过遍历获取各字符的编码
(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
	if (IsLeaf(*v)) // 若是叶节点
	{
	}
}
