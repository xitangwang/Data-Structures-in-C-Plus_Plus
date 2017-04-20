/******************************************************************************************
* Data Structures in C++ -- AVL��ADT�ӿڣ�AVL balance binary serach tree)
* ���ϼ������� 2017/4/11 16:19
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"../BST/BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild)) // ����ƽ��
#define BalFac(x) (stature((x).lChild) - stature((x).rChild)) // ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) // AVLƽ������

template <typename T> class AVL:public BST<T>
{
public: // BST::search()�Ƚӿڣ�����ֱ������

	// ��̬������Ҫ��д
	BinNodePosi(T) insert(const T & e)
	{
		BinNodePosi(T) & x = search(e);if (x) return x; 
		x = new BinNode<T>(e, _hot);_size++;BinNodePosi(T) xx = x; 
		// ���£���x�ĸ��׳���������ϣ�һ�μ���������g
		for (BinNodePosi(T) g = x->parent;g;g = g->parent)
		{
			if (AvlBalanced(*g)) // һ��ʧ�⣬��ͨ�������ָ�ƽ��
			{
				FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
				break;
			}
			else
				updateHeight(g);
		}
		return xx;
	}

	bool remove(const T & e)
	{
		BinNodePosi(T) & x = search(e);if (!x) return false;
		removeAt(x, _hot);_size--; 
		int h = -2;
		// ���£���_hot����������ϣ����μ���������g
		for(BinNodePosi(T) g = _hot;g;g = g->parent)
		{
			// ������׵ĸ߶Ȳ��䣬������˳�ѭ��
			if (g->height == h + 1)
				break;
			h = g->height;

			if (!AvlBalanced(*g)) // һ������gʧ�⣬��ͨ�������ָ�ƽ��
				g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			updateHeight(g); // ��������߶�
		} // ������Ҫ��omg(logn)�ε����������Ƿ�����������ȫ���߶�
	}

	BinNodePosi(T) connect34( // 3 + 4 �ع�
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
	)
	{
		a->lChild = T0;if (T0) T0->parent = a;
		a->rChild = T1;if (T1) T1->parent = a;updateHeight(a);
		c->lChild = T2;if (T2) T2->parent = c;
		c->rChild = T3;if (T3) T3->parent = c;updateHeight(a);
		b->lChild = a;a->parent = b;
		b->rChild = c;c->parent = b;updateHeight(b);
		return b; // ���������µĸ��ڵ�
	}
};
