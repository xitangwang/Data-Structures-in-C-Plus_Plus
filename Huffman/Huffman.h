/******************************************************************************************
* Data Structures in C++ -- Huffman������ʵ��
* ���ϼ������ 2017/3/28 11:25
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include"../BinTree/Bintree.h"
#include <ctime>
typedef BinTree<char> PFCTree; // PFC��

#include "../vector/vector.h"
typedef Vector<PFCTree*> PFCForest; // PFCɭ��

#include"../Bitmap/Bitmap.h" //ʹ��λͼʵ�ֶ����Ʊ��봮
#include <map>
typedef std::map<char, char*> PFCTable; // PFC�����������ʽΪ����key = �ַ�,value = ���봮)

#define N_CHAR (0x80 - 0x20) // ֻ���ǿɴ�ӡ���ַ�

// ��ʼ��PFCɭ��
PFCForest* initForest()
{
	PFCForest* forest = new PFCForest;
	for (int i = 0;i < N_CHAR;i++) // ��ÿһ���ɴ�ӡ���ַ�(0x20,0x80)
	{
		forest->insert(i, new PFCTree());
		(*forest)[i]->insertAsRoot(0x20 + i); // ֻ������Ӧ��һ��������Ҷ���ڵ�
	}
	return forest; // ���ذ���N_CHAR������ɭ�֣�����ÿ����������һ���ַ�
}

// ����PFC������
PFCTree* generateTree(PFCForest* forest)
{
	srand(static_cast<unsigned int>(time(nullptr))); // ���ｫ���ȡ���ϲ������������������
	while (1 < forest->size()) // ����|forest| - 1�κϲ�
	{
		PFCTree* s = new PFCTree;s->insertAsRoot('^'); // ���������������Ϊ"^"��
		Rank r1 = rand() % forest->size(); // ���ѡȡr1,��
		s->attachAsLC(s->root(), (*forest)[r1]); // ��Ϊ�����������
		forest->remove(r1); // �漴�޳�
		Rank r2 = rand() % forest->size(); // ���ѡȡr2����
		s->attachAsRC(s->root(), (*forest)[r2]); // ��Ϊ�����������
		forest->remove(r2); // �漴�޳�
		forest->insert(forest->size(), s); // �ϲ����PFC�����½���PFCɭ��
	}
	return (*forest)[0]; // ���ˣ�ɭ�����д��һ��������ȫ��PFC������
}

// ����PFC�����
void generateCT // ͨ��������ȡ���ַ��ı���
(Bitmap* code, int length, PFCTable* table, BinNodePosi(char) v)
{
	if (IsLeaf(*v)) // ����Ҷ�ڵ�
	{
	}
}
