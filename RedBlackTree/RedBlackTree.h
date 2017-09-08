/******************************************************************************************
* Data Structures in C++ -- RedBlackTree ADT接口
* 丁酉鸡年三月 2017/7/06 21:09
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include"../BST/BST.h"
#include "../BinTree/BinNode.h"

#define IsBlack(p) ( !(p) || (RB_BLACK == (p)->color) )
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( \
	(stature((x).lChild) == stature((x).rChild)) && \
	((x).heigth == (IsRed(&x) ? stature((x).lChild) : stature((x).lChild + 1)))

template <typename T>
class RedBlackTree : public BST<T> 
{
protected:
	void solveDoubleRed(BinNodePosi(T) x);// 双红修正
	void sloveDoubleBlack(BinNodePosi(T) x);// 双黑修正
	int updateHeight(BinNodePosi(T) x) override;// 更新节点x的高度
public:
	BinNodePosi(T) insert(const T& e); // 插入（重写）
	bool remove(const T& e) override; // 删除（重写）
// BST::search() 等接口继续使用
};

template <typename T>
void RedBlackTree<T>::solveDoubleRed(BinNode<T>* x)
{
	BinNode<T> parent = x->parent;
	BinNode<T> uncle = uncle(x);
	if(IsBlack(uncle))
	{
		if(IsLChild(*x) == IsLChild(parent)) // 如果x与其父节点同侧
		{
			parent.color = RB_BLACK;
		}
		else
		{
			x->color = RB_BLACK;
		}
		parent.parent->color = RB_RED;
		BinNode<T> gg = parent.parent->parent;
		BinNodePosi(T) r = FromParentTo(*parent) = rotateAt(x);
		r->parent = gg;
	}
	else
	{  
		parent.color = RB_BLACK; parent.height++;
		uncle.color = RB_BLACK; uncle.height++;
		if (!IsRoot(parent.parent)) parent.parent->color = RB_RED;
		solveDoubleRed(parent.parent);
	}
}

template <typename T>
void RedBlackTree<T>::sloveDoubleBlack(BinNode<T>* x)
{
	BinNodePosi(T) p = x->parent;
	BinNodePosi(T) s = IsLChild(*x) ? x->parent->rChild : x->parent->lChild;
	BinNodePosi(T) t;
	if(s->color == RB_BLACK)
	{
		//(1)
		if (s->lChild->color == RB_RED || s->rChild->color == RB_RED)
		{
			if (s->lChild->color == RB_RED)
				t = s->lChild;
			else
				t = s->rChild;
			p->color = s->color = RB_BLACK;
			if (IsLChild(*x))
				p->rChild = IsLChild(*t) ? s->rChild : s->lChild;
			else
				p->lChild = IsLChild(*t) ? s->rChild : s->lChild;
			if (IsLChild(*t))
				s->rChild = p;
			else
				s->lChild = p;

		}
		//(2-R)
		else if(p->color == RB_RED)
		{
			p->color = RB_BLACK;
			s->color = RB_RED;
		}
		//(2-B)
		else
		{
			s->color = RB_RED;
			sloveDoubleBlack(p);
		}
	}
	//(3)
	else
	{
		s->color = RB_BLACK;
		p->color = RB_RED;
		BinNodePosi(T) t = IsLChild(*s) ? s->lChild : s->rChild;
		_hot = p;
		FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(x);
	}
}

template <typename T>
int RedBlackTree<T>::updateHeight(BinNode<T>* x)
{
	x->height = max(stature(x->lChild), stature(x->rChild));
	return IsBlack(x) ? x->height++ : x->height;
}


template <typename T>
BinNode<T>* RedBlackTree<T>::insert(const T& e)
{
	BinNodePosi(T) x = search(e);
	if (x) return x;
	x = new BinNode<T>(e, _hot, nullptr, nullptr, -1);
	solveDoubleRed(x); return x ? x : _hot->parent; // 
}

template <typename T>
bool RedBlackTree<T>::remove(const T& e)
{
	BinNodePosi(T) x = search(e); if (x) return false;

	BinNodePosi(T) r = removeAt(x); // removeAt会返回替代x的节点
	if (!(--_size)) return true; // 如果删除的是最后一个节点，直接返回
	if(IsRoot(*r))
	{
		r->color = RB_BLACK;
	}
	solveDoubleBakck(x);
	return true;
}