/******************************************************************************************
* Data Structures in C++ -- ����Ԫ�ء����ݽṹͨ������ӿ�
* ���ϼ������� 2017/2/26 10:20
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include<stdio.h>
#include <typeinfo>
#include "../BinTree/BinTree.h"
#include"../Bitmap/Bitmap.h"
#include "../BST/BST.h"
#include "../AVL/AVL.h"
#include "../Splay/Splay.h"
#include "../GraphMatrix/GraphMatrix.h"
#include "../B_Tree/BTree.h"

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

template <typename T> static void print(T* x) { x ? print(*x) : print(" <NULL>"); }
template <typename T> static void print(T & x) { UniPrint::p(x); }
template <typename T> static void print(const T& x) { UniPrint::p(x); } // for Stack
static void print(char * x) { printf(" %s", x ? x : "<NULL> "); }
static void print(const char* x) { printf("%s", x ? x : "<NULL>"); }

class UniPrint
{
public:
	static void p(int);
	static void p(float);
	static void p(double);
	static void p(char);


	template<typename T> static void p(T&); // �������б��֧��tracerse()�����ṹ�����Խṹ
	template<typename T> static void p(T* s) // ����ָ��
	{
		s ? p(*s) : print("<NULL>"); // ͳһתΪ����
	}
	template<typename T>static void p(BinNode<T> &);
	template<typename T>static void p(BinTree<T> & bt)
	{
		printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());
		Bitmap* branchType = new Bitmap;
		printBinTree(bt.root(), -1, ROOT, branchType);
		release(branchType);printf("\n");
	}

	
	template <typename T> static void p(BST<T>&); //BST
	template <typename T> static void p(AVL<T>&); //AVL
	template <typename T> static void p(Splay<T>&); //Splay
	template <typename T> static void p(BTree<T>&); //BTree
	/*
	template <typename T> static void p(RedBlack<T>&); //RedBlack
	template <typename T> static void p(Quadlist<T>&); //Quadlist
	template <typename K, typename V> static void p(Skiplist<K, V>&); //Skiplist
	template <typename K, typename V> static void p(Hashtable<K, V>&); //Hashtable
	template <typename T> static void p(PQ_List<T>&); //PQ_List
	template <typename T> static void p(PQ_ComplHeap<T>&); //PQ_ComplHeap
	template <typename T> static void p(PQ_LeftHeap<T>&); //PQ_LeftHeap
	*/
	//template <typename Tv, typename Te> static void p(GraphMatrix<Tv, Te>&); //Graph
	
}; // UniPrint

inline void UniPrint::p(int e) { printf("%04d", e); }
inline void UniPrint::p(float e) { printf("%4.1f", e); }
inline void UniPrint::p(double e) { printf("%4.1f", e); }
inline void UniPrint::p(char e) { printf("%c", (31 < e) && (e < 128) ? e : '$'); }

template <typename T>
void UniPrint::p(T& s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), &s, s.size()); // ������Ϣ
	s.traverse(print);
	printf("\n");
}



/******************************************************************************************
* �����������������ͳһ��ӡ
******************************************************************************************/
template <typename T> //Ԫ������
static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap* bType)
{
	if (!bt) return;
	if (-1 < depth) //���õ�ǰ��Ĺ����־
		R_CHILD == type ? bType->set(depth) : bType->clear(depth);
	printBinTree(bt->rChild, depth + 1, R_CHILD, bType); //�����������ϣ�
	print(bt); printf(" *");
	for (int i = -1; i < depth; i++) //�������ڸ���
		if ((0 > i) || bType->test(i) == bType->test(i + 1)) //�Ĺ����Ƿ�һ�£�����ȷ��
			printf("      "); //�Ƿ�Ӧ��
		else  printf("��    "); //��ӡ����
		switch (type) {
		case  R_CHILD:  printf("����");  break;
		case  L_CHILD:  printf("����");  break;
		default:  printf("����");  break; //root
		}
		print(bt);
#if defined(DSA_HUFFMAN)
		if (IsLeaf(*bt)) bType->print(depth + 1); //���Huffman����
#endif
		printf("\n");
		printBinTree(bt->lChild, depth + 1, L_CHILD, bType); //�����������£�

}


/******************************************************************************************
* BTree��ӡ
******************************************************************************************/
#include"print_btree.h"

template <typename T> void UniPrint::p(BinNode<T> & node)
{
	p(node.data);
	/****************************************************************************
	* height & NPL
	****************************************************************************/
#if defined(DSA_LEFTHEAP)
	printf("(%-2d),", node.npl);
#elif defined(DSA_BST)
	printf("(%-2d)", node.height);
#elif defined(DSA_AVL)
	printf("(%-2d)", node.height);
#elif defined(DSA_REDBLACK)
	printf("(%-2d)", node.height);
#elif defined(DSA_SPLAY)
	printf("(%-2d)", node.height);
#endif
	/****************************************************************************
	* ��������ָ��
	****************************************************************************/
	/*printf(
		((node.lChild && &node != node.lChild->parent) ||
		(node.rChild && node != node.rChild->parent)) ?
		"@" : " "
	);*/
	/****************************************************************************
	* �ڵ���ɫ
	****************************************************************************/
#if defined(DSA_REDBLACK)
	printf(node.color == RB_BLACK ? "B" : " ");
#endif
	/****************************************************************************
	* ���ӣ��ڣ��߶ȡ�NPLƥ��
	****************************************************************************/
#if defined(DSA_PQ_COMPLHEAP)
	//�߶Ȳ���ƥ��
#elif defined(DSA_PQ_LEFTHEAP)
	printf( // NPL
		(node.rChild && node.npl != 1 + node.rChild->npl) ||
		(node.lChildhild && node.npl > 1 + node.lChildhild->npl) ?
		"%%" : " "
	);
#elif defined(DSA_REDBLACK)
	printf(BlackHeightUpdated(node) ? " " : "!");//�ڸ߶�
#else
	//printf(HeightUpdated(node) ? " " : "!");//�����棩�߶�
#endif
/****************************************************************************
* ����ƽ��
****************************************************************************/
#if defined(DSA_AVL)
	if (!AvlBalanced(node)) printf("X"); // AVLƽ��
	else if (0 < BalFac(node)) printf("\\"); //AVLƽ��
	else if (BalFac(node) < 0) printf("/"); //AVLƽ��
	else printf("_"); //AVLƽ��
#elif defined(DSA_REDBLACK)
	if (!Balanced(node)) printf("X"); //RBƽ��
	else if (0 < BalFac(node)) printf("\\"); //RBƽ��
	else if (BalFac(node) < 0)printf("/"); //RBƽ��
	else printf("_"); //RBƽ��
#else
											//ƽ������ν
#endif
}
