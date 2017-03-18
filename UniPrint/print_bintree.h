/******************************************************************************************
* Data Structures in C++ -- �����������ӡ
* ���ϼ������ 2017/3/18 11:40
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "print.h"
#include"../Bitmap/Bitmap.h"

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

/***************************************************************************************
 * ����BinTree
 ***************************************************************************************/
template <typename T>
void UniPrint::p(BinTree<T>& bt)
{
	printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());
	Bitmap* branchType = new Bitmap;
	printBinTree(bt.root(), -1, ROOT, branchType);
	release(branchType);printf("\n");
}

/******************************************************************************************
* �����������������ͳһ��ӡ
******************************************************************************************/
template <typename T> //Ԫ������
static void printBinTree(BinNodePosi(T) bt,int depth,int type,Bitmap* bType)
{
	if (-1 < depth) //���õ�ǰ��Ĺ����־
		R_CHILD == type ? bType->set(depth) : bType->clear(depth);
	printBinTree(bt->rc, depth + 1, R_CHILD, bType); //�����������ϣ�
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
		printBinTree(bt->lc, depth + 1, L_CHILD, bType); //�����������£�
	
}

///******************************************************************************************
//* ����BinTreeʵ�ֵ�BST
//******************************************************************************************/
//template <typename T> //Ԫ������
//void UniPrint::p(BST<T> & bt) { //����
//	printf("%s[%d]*%d:\n", typeid (bt).name(), &bt, bt.size()); //������Ϣ
//	Bitmap* branchType = new Bitmap; //��¼��ǰ�ڵ����ȵķ���
//	printBinTree(bt.root(), -1, ROOT, branchType); //��״�ṹ
//	release(branchType); printf("\n");
//}
//
///******************************************************************************************
//* ����BSTʵ�ֵ�AVL
//* ���е��õ�BinNode�Ĵ�ӡ���̣�������ʾBF״̬
//******************************************************************************************/
//template <typename T> //Ԫ������
//void UniPrint::p(AVL<T> & avl) { //����
//	printf("%s[%d]*%d:\n", typeid (avl).name(), &avl, avl.size()); //������Ϣ
//	Bitmap* branchType = new Bitmap; //��¼��ǰ�ڵ����ȵķ���
//	printBinTree(avl.root(), -1, ROOT, branchType); //��״�ṹ
//	release(branchType); printf("\n");
//}
//
///******************************************************************************************
//* ����BSTʵ�ֵ�RedBlack
//* ���е��õ�BinNode�Ĵ�ӡ���̣�������ʾBF״̬
//******************************************************************************************/
//template <typename T> //Ԫ������
//void UniPrint::p(RedBlack<T> & rb) { //����
//	printf("%s[%d]*%d:\n", typeid (rb).name(), &rb, rb.size()); //������Ϣ
//	Bitmap* branchType = new Bitmap; //��¼��ǰ�ڵ����ȵķ���
//	printBinTree(rb.root(), -1, ROOT, branchType); //��״�ṹ
//	release(branchType); printf("\n");
//}
//
///******************************************************************************************
//* ����BSTʵ�ֵ�Splay
//* ����Splay��������bf֮��ĸ��ӱ�ʶ�����ӡ������BST��ȫһ��
//******************************************************************************************/
//template <typename T> //Ԫ������
//void UniPrint::p(Splay<T> & bt) { //����
//	printf("%s[%d]*%d:\n", typeid (bt).name(), &bt, bt.size()); //������Ϣ
//	Bitmap* branchType = new Bitmap; //��¼��ǰ�ڵ����ȵķ���
//	printBinTree(bt.root(), -1, ROOT, branchType); //��״�ṹ
//	release(branchType); printf("\n");
//}


