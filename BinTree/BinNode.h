/******************************************************************************************
* Data Structures in C++ -- BinNode 模板类
* 丁酉鸡年二月 2017/3/15 21:40
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
#include "../UniPrint/print.h"
#include "../UniPrint/print_bintree.h"

typedef enum { RB_RED, RB_BLACK } RBColor;	//红黑数节点颜色

/*******************************************************************************************
* BinNode状态与性质的判断
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
* 与BinNode具有特定关系的节点及指针
********************************************************************************************/
#define sibling(p) ( \
	IsLChild(*(p)) ? \
		(p)->parent->rChild : \
		(p)->parent->lChild \
) //兄弟

#define uncle(x) ( \
	IsLChild(*((x)->parent)) ? \
		(x)->parent->parent->rChild : \
		(x)->parent->parent->lChild \
) //叔叔

#define FromParentTo(x) ( \
	IsRoot(x) ? _root : ( \
	IsLChild(x) ? (x).parent->lChild : (x).parent->rChild \
	) \
)

template <typename T> struct BinNode
{

	T data;
	BinNodePosi(T) parent; BinNodePosi(T) lChild; BinNodePosi(T) rChild;
	int height;
	int npl;
	RBColor color;

	//构造函数
	BinNode() :parent(nullptr), lChild(nullptr), rChild(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED)
		:data(e), parent(p), lChild(lc), rChild(rc), height(h), npl(l), color(c) {}

	//操作接口
	int size();
	BinNodePosi(T) insertAsLC(T const& e) { return lChild = new BinNode(e, this); }
	BinNodePosi(T) insertAsRC(T const& e) { return rChild = new BinNode(e, this); }
	//取当前节点的直接后继
	BinNodePosi(T) succ();	
	//子树层次遍历
	template <typename VST> void travLevel(VST & visit)
	{
		travLevel_L(this, visit);
	}
	//子树先序遍历
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
	//子树中续遍历
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
	//子树中续遍历
	template <typename VST> void travPost(VST &);

	//比较器、判断器
	bool operator<(BinNode const & bn) { return data < bn.data; }
	bool operator==(BinNode const & bn) { return data == bn.data; }

};