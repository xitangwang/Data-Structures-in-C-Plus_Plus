/******************************************************************************************
* Data Structures in C++ -- AVL树ADT接口（AVL balance binary serach tree)
* 丁酉鸡年三月 2017/4/11 16:19
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"../BST/BST.h"

#define Balanced(x) (stature((x).lChild) == stature((x).rChild)) // 理想平衡
#define BalFac(x) (stature((x).lChild) - stature((x).rChild)) // 平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) // AVL平衡条件

template <typename T> class AVL:public BST<T>
{
public: // BST::search()等接口，可以直接沿用

	// 动态操作需要重写
	BinNodePosi(T) insert(const T & e)
	{
		BinNodePosi(T) & x = search(e);if (x) return x; 
		x = new BinNode<T>(e, _hot);_size++;BinNodePosi(T) xx = x; 
		// 以下，从x的父亲出发逐层向上，一次检查各代祖先g
		for (BinNodePosi(T) g = x->parent;g;g = g->parent)
		{
			if (AvlBalanced(*g)) // 一旦失衡，则通过调整恢复平衡
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
		// 以下，从_hot出发逐层向上，依次检查各代祖先g
		for(BinNodePosi(T) g = _hot;g;g = g->parent)
		{
			// 如果父亲的高度不变，则可以退出循环
			if (g->height == h + 1)
				break;
			h = g->height;

			if (!AvlBalanced(*g)) // 一旦发现g失衡，则通过调整恢复平衡
				g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			updateHeight(g); // 并更新其高度
		} // 可能需要做omg(logn)次调整；无论是否做过调整，全树高度
	}

	BinNodePosi(T) connect34( // 3 + 4 重构
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
		return b; // 该子树的新的根节点
	}
};
