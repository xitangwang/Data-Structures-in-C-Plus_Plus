/******************************************************************************************
* Data Structures in C++ -- BinNode ģ����
* ���ϼ������ 2017/3/15 21:40
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
#include "../UniPrint/print.h"
#include "../UniPrint/print_bintree.h"

typedef enum { RB_RED, RB_BLACK } RBColor;	//������ڵ���ɫ

/*******************************************************************************************
* BinNode״̬�����ʵ��ж�
********************************************************************************************/
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lChild))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rChild))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lChild)
#define HasRChild(x) ((x).rChild)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))

/*******************************************************************************************
* ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
********************************************************************************************/
#define sibling(p) ( \
	IsLChild(*(p)) ? \
		(p)->parent->rChild : \
		(p)->parent->lChild \
) //�ֵ�

#define uncle(x) ( \
	IsLChild(*((x)->parent)) ? \
		(x)->parent->parent->rChild : \
		(x)->parent->parent->lChild \
) //����

#define FromParentTo(x) ( \
	IsRoot(x) ? _root : ( \
	IsLChild(x) ? (x).parent->lChild : (x).parent->rChild \
	) \
)

template <typename T> struct BinNode
{
	T data;
	BinNodePosi(T) parent; BinNod  ePosi(T) lChild; BinNodePosi(T) rChild;
	int height;
	int npl;
	RBColor color;

	//���캯��
	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED)
		:data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {}

	int depth()
	{
		int i = 0;BinNodePosi(T) s = this;
		while(s != nullptr)
		{
			++i;s = s->parent;
		}
		return i;
	}

	//�����ӿ�
	int size()
	{
		int s = 1;
		if (lChild) s += lChild->size();
		if (rChild) s += rChild->size();
		return s;
	}
	BinNodePosi(T) insertAsLC(T const& e) { return lChild = new BinNode(e, this); }
	BinNodePosi(T) insertAsRC(T const& e) { return rChild = new BinNode(e, this); }
	//ȡ��ǰ�ڵ��ֱ�Ӻ��
	BinNodePosi(T) succ()
	{
		BinNodePosi(T) s = this;
		if(HasRChild(*s))
		{
			s = s->rChild;
			while (HasLChild(*s)) s = s->lChild;
		}
		else
		{
			while (IsRChild(*s)) s = s->parent;
			s = s->parent;
		}
		return s;
	}

	//ȡ��ǰ�ڵ��ֱ��ǰ��
	BinNodePosi(T) pred()
	{
		BinNodePosi(T) s = this;
		if(HasLChild(*s))
		{
			s = s->lChild;
			while (HasRChild(*s)) s = s->rChild;
		}
		else
		{
			while (IsLChild(*s)) s = s->parent;
			s = s->parent;
		}
		return s;
	}

	//������α���
	template <typename VST> void travLevel(VST & visit)
	{
		travLevel_L(this, visit);
	}
	//�����������
	template <typename VST> void travPre(VST & visit)
	{
		switch (rand() % 3)
		{
		case 1:travPre_R(this, visit);
			break;
		case 2:travPre_L(this, visit);
			break;
		default:travPre_L2(this, visit);
			break;

		}
	}
	//������������
	template <typename VST> void travIn(VST & visit)
	{
		switch (rand() % 2)
		{
		case 1:travIn_L(this, visit);
			break;
		default:travIn_R(this, visit);
			break;
		}
	}
	//������������
	template <typename VST> void travPost(VST & visit)
	{
		travPost_R(this, visit);
	}

	BinNodePosi(T) zig()
	{
		BinNodePosi(T) v = this;
		BinNodePosi(T) c = v->lChild;
		c->parent = v->parent;v->parent = c;
		v->lChild = c->rChild;
		return c;
	}

	BinNodePosi(T) zag()
	{
		BinNodePosi(T) v = this;
		BinNodePosi(T) c = v->rChild;
		c->parent = v->parent;v->parent = c;
		v->rChild = c->lChild;
		return c;
	}

	//�Ƚ������ж���
	bool operator<(BinNode const & bn) { return data < bn.data; }
	bool operator==(BinNode const & bn) { return data == bn.data; }
};