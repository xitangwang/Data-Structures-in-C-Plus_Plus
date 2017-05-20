/******************************************************************************************
* Data Structures in C++ -- BTree ADT接口
* 丁酉鸡年三月 2017/5/20 : 16:56
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../vector/vector.h"
#include "../_share/release.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T> struct BTNode
{
	BTNodePosi(T) parent; // 父节点
	Vector<T> key; // 关键码向量
	Vector<BTNodePosi(T)> child; // 孩子向量（其长度总比key 多一点）
	// 构造函数（注意：BTNode只能作为根节点创建，而且初始化时有0个关键码和1个空孩子指针）
	BTNode() { parent = nullptr;child.insert(0, nullptr); }
	BTNode(T e,BTNodePosi(T) lc = nullptr,BTNodePosi(T) rc = nullptr)
	{
		parent = nullptr; // 作为根节点，而且初始时
		key.insert(0, e); // 只有一个关键码，以及
		child.insert(0, lc);child.insert(1, rc); // 两个孩子
		if (lc) lc->parent = this;if (rc) rc->parent = this;
	}
};

template <typename T> 
class BTree // BTree模板类
{
protected:
	int _size; // 存放关键码总数
	int _order; // B-数的阶次，至少为三--创建时指定
	BTNodePosi(T) _root; // 根节点
	BTNodePosi(T) _hot; // BTree::search()最后访问的非空（除非数空）的节点位置
	void solveOVerflow(BTNodePosi(T) ); // 因插入而上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T)); // 因删除而下溢之后的合并处理
public:
	BTree(int order = 3):_order(order),_size(0)
	{
		_root = new BTNode<T>();
	}

	~BTree()
	{
		if (_root)
			release(_root);
	}

	int const order() { return _order; } // 阶次

	int const size() { return _size; } // 规模

	BTNodePosi(T) & root() { return _root; } // 树根
	
	bool empty() const { return !_root; } // 判空

	BTNodePosi(T) search(const T & e); // 查找

	bool insert(const T & e); // 插入

	bool remove(const T & e); // 删除
}; // BTree
