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
	void solveOVerflow(BTNodePosi(T) v) // 因插入而上溢之后的分裂处理
	{
		if (_order >= v->child.size()) return; // 递归基：当前节点并未上溢
		Rank s = _order / 2; // 轴点（此时应有_order = key.size() = child.size() - 1）
		BTNodePosi(T) u = new BTNode<T>(); // 注意：新节点已有一个空孩子
		for(Rank j = 0;j < _order - s - 1;j++) // v右侧_order - s - 1个孩子及关键码分裂为右侧节点u
		{
			u->child.insert(j, v->child.remove(s + 1)); // 逐个移动效率低
			u->key.insert(j, v->key.remove(s + 1)); // 次策略可改进
		}
		u->child[_order - s - 1] = v->child.remove(s + 1); // 移动v最靠右的孩子
		if (u->child[0]) // 若u的孩子们非空，则
			for (Rank j = 0; j < _order; ++j)
				u->child[j]->parent = u;
		BTNodePosi(T) p = v->parent; // v当前的父节点p
		if (!p) { _root = p = new  BTNode<T>(); p->child[0] = v; v->parent = p; } // 若p为空则创建之
		Rank r = 1 + p->key.serach(v->key[0]); // p中指向u的指针的秩
		p->key.insert(r, v->key.remove(s));
		p->child.insert(r + 1, u); u->parent = p; // 新节点与父节点u互联
		solveOVerflow(p); // 上升一层，如果有必要则继续分裂——至多递归O(logn)层
	}
	void solveUnderflow(BTNodePosi(T) v) // 因删除而下溢之后的合并处理
	{
		if ((_order + 1) / 2 <= (v->child.size())) return; // 递归基：当前节点并未下溢
		BTNodePosi(T) p = v->parent;
		if(!p) // 递归基：已到根节点，没有孩子的下限
		{
			if(!v->key.size() && v->child[0])
			{
				// 但倘若作为树根的v已不包含关键码，却有（唯一的）非空孩子，则
				_root = v->child[0]; _root->parent = nullptr; // 这个节点可以背跳过
				v->child[0] = nullptr; release(v); // 并因不再有用而背销毁
			} // 整树高度降低一层
			return;
		}
		Rank r = 0; while (p->child[r] != v) r++;
		// 确定v是p的第r个孩子——此时v可能不含关键码，故不能通过关键码查找
		// 另外，在实现了孩子指针的判等器之后，也可直接调用Vector::find()定位
	// 情况1：向左兄弟借关键码
		if(0 < r) // 若v不是p的第一个孩子，则
		{
			BTNodePosi(T) ls = p->child[r - 1]; // 左兄弟必存在
			if((_order + 1) / 2 < ls->child.size()) // 若该兄弟足够“胖”则
			{
				v->key.insert(0, p->key[r - 1]); // p借出一个关键码给v（作为最小关键码）
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1); // ls的最大关键码转入p
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));
				// 同时ls的最右侧孩子过继给v
				if (v->child[0]) v->child[0]->parent = v; // 作为v的最左侧孩子
				return; // 至此，通过右旋已完成当前层（以及所有层）的下溢处理
			}
		} // 至此。左兄弟要么为空，要么太“瘦”
	// 情况2：向右兄弟借关键码
		if(p->child.size() - 1 > r)
		{
			BTNodePosi(T) rs = p->child[r + 1];
			if((_order + 1) /2 < rs->child.size())
			{
				v->key.insert(v->key.size(), p->key[r]);
				p->key[r] = rs->key.remove(0);
				v->child.insert(v->child.size(), rs->child.remove(0));

				if (v->child[v->child.size() - 1])
					v->child[v->child.size() - 1]->parent = v;
				return;
			}
		}

	// 情况3：左右兄弟要么为空（不可能同时），要么太“瘦”——合并
		if(0 < r)
		{
			BTNodePosi(T) ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
			// p的第r - 1个关键码转入ls，v不再是p的第r个孩子
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
			while(!v->key.empty())
			{
				ls->key.insert(ls->key.size(), v->key.remove(0));
				ls->child.insert(ls->child.size(), v->child.remove(0));
				if (ls->child[ls->child.size() - 1])
					ls->child[ls->child.size() - 1]->parent = ls;
			}
		}
		else
		{
			BTNodePosi(T) rs = p->child[r + 1];
			rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if (rs->child[0])
				rs->child[0]->parent = rs;
			while (!v->key.empty())
			{
				rs->key.insert(0, v->key.remove(v->key.size() - 1));
				rs->child.insert(0, v->child.remove(v->child.size() - 1));
				if (rs->child[0])
					rs->child[0]->parent = rs;
			}
			release(v);
		}
		solveUnderflow(p);
		return;
	}
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

	int order() const { return _order; } // 阶次

	int size() const { return _size; } // 规模

	BTNodePosi(T) & root() { return _root; } // 树根
	
	bool empty() const { return !_root; } // 判空

	BTNodePosi(T) search(const T & e) // 查找
	{
		BTNodePosi(T) v = _root; _hot = nullptr; // 从根节点出发
		while(v) // 逐层查找
		{
			Rank r = v->key.serach(e); // 在当前节点中找到不至于大于e的关键码
			if ((0 <= r) && (e == v->key[r])) return v; // 若成功：在当前节点命中目标关键码
			_hot = v; v = v->child[r + 1]; // 否则，转入对应子树（_hot指向其父）——需要做I/O，最费时间
		} // 这里在向量内时二分，但通常对_order可能直接顺序查找
		return nullptr;
	}

	bool insert(const T & e) // 插入
	{
		BTNodePosi(T) v = search(e); if (v) return false; // 确认目标点不存在
		Rank r = _hot->key.serach(e); // 在节点_hot的有序关键码向量中查找适合的位置插入
		_hot->key.insert(r + 1, e);
		_hot->child.insert(r + 2, nullptr); // 插入关键码和孩子
		_size++;
		solveOVerflow(_hot);
		return true;
	}

	bool remove(const T & e) // 删除
	{
		BTNodePosi(T) v = search(e); if (!v) return false; // 确认关键码存在
		Rank r = v->key.serach(e);
		if(v->child[0]) // 若v非叶子，则e的后继必属于某叶节点——如果它有孩子，就不是叶节点
		{
			BTNodePosi(T) u = v->child[r + 1]; // 在右子树中一直向左，即可
			while (u->child[0]) u = u->child[0]; // 找出e的后继
			v->key[r] = u->key[0]; v = u; r = 0; // 并与之交换位置
		} // 至此，v必然位于最底层，且其中第r个关键码就是待删除者
		v->key.remove(r); v->child.remove(r + 1); _size--;
		solveUnderflow(v);
		return true;
	}
}; // BTree
