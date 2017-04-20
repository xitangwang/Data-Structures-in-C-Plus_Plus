/******************************************************************************************
* Data Structures in C++ -- 二叉搜索树ADT接口（binary serach tree)
* 丁酉鸡年三月 2017/4/7 23:03
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../BinTree/BinTree.h"

template <typename K,typename V> struct Entry // 词条模板类
{
	K key;V value; // 关键码、数值
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // 默认构造函数
	Entry(Entry<K, V> const & e) :key(e.key), value(e.value) {}; // 克隆
// 比较器、判等器（从此，不必严格区分词条及其对应的关键码）
	bool operator< (Entry<K, V> const & e) { return key < e.key; } // 小于
	bool operator> (Entry<K, V> const & e) { return key > e.key; } // 大于
	bool operator==(Entry<K, V> const & e) { return key == e.key; } // 等于
	bool operator!=(Entry<K, V> const & e) { return key != e.key; } // 不等
};

template <typename T> class BST : public BinTree<T> // 由BinTree派生
{
protected:
	BinNodePosi(T) _hot; // 命中节点的父亲

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

	BinNodePosi(T) rotateAt(BinNodePosi(T) v) // 旋转调整
	{
		BinNodePosi(T) p = v->parent;BinNodePosi(T) g = p->parent; // 父亲、祖父
		if(IsLChild(*p)) // zig
		{
			if(IsLChild(*v)) // zig-zig
			{
				p->parent = g->parent; // 向上联结
				return connect34(v, p, g,
					v->lChild, v->rChild, p->rChild, g->rChild);
			}else // zig-zag
			{
				v->parent = g->parent;
				return connect34(p, v, g,
					p->lChild, v->lChild, v->rChild, g->rChild);
			}
		}
		else // zag
		{
			if(IsLChild(*v)) // zag-zig
			{
				v->parent = g->parent;
				return connect34(g, v, p,
					g->lChild, v->lChild, v->rChild, p->rChild);
			}else // zag-zag
			{
				p->parent = g->parent;
				return connect34(g, p, v,
					g->lChild, p->lChild, v->lChild, v->rChild);
			}
		}
	}

public: // 以virtual修饰，以便派生类重写
	virtual BinNodePosi(T) & search(const T & e) // 查找
	{
		return searchIn_I(_root, e, _hot = nullptr); // _hot用来方便插入算法
	}

	virtual List<BinNodePosi(T)> searchAll(const T & e)
	{
		return searchRange(e, e); 
	}

	virtual List<BinNodePosi(T)> searchRange(const T & l,const T & r)
	{
		BinNodePosi(T) nodeL = searchIn_R(_root, l, _hot = nullptr);
		BinNodePosi(T) nodeR = searchIn_R(_root, r, _hot = nullptr);
		BinNodePosi(T) L = nodeL, R = nodeR;
		while(nodeL->depth() != nodeR->depth())
		{
			nodeL->depth() < nodeR->depth() ? nodeR = nodeR->parent : nodeL = nodeL->parent;
		}
		while(nodeL != nodeR)
		{
			nodeL = nodeL->parent;
			nodeR = nodeR->parent;
		}
		return travIn(nodeL, l, r);
	}

	List<BinNodePosi(T)> travIn(BinNodePosi(T) x,const T & l,const T & r) // 二叉树中序遍历（#迭代3，无需辅助栈）
	{
		List<BinNodePosi(T)> list;
		bool backtrack = false; // 前一步是否刚从右子树回溯——省去栈，仅O(1)辅助空间
		while (true)
		{
			if (!backtrack && HasLChild(*x))
			{
				x = x->lChild;
			}
			else
			{
				/****************/
				if((x->data > l && x->data < r) || (x->data == l && x->data == r))
				{
					list.insertAsLast(x);
				}
			}
			if (HasRChild(*x))
			{
				x = x->rChild;
				backtrack = false;
			}
			else
			{
				if (!(x = x->succ()))
					break;
				backtrack = true;
			}
		}
		return list;
	}

	// 在以v为根的(AVL、SPLAY、rbTree等）BST子树中查找关键码e
	static BinNodePosi(T) & searchIn_R(
		BinNodePosi(T) & v, // 当前（子）树根
		const T & e, // 目标关键码
		BinNodePosi(T) hot) // 记忆热点
	{
		if (!v || v->data == e) return v;
		hot = v; // 记下当前非空节点
		return  searchIn_R(v->data > e ? v->lChild : v->rChild, e, hot);
	} // 运行时间正比于返回节点v的深度，不超过树高O(h)

	static BinNodePosi(T) & searchIn_I(
		BinNodePosi(T) & v,
		const T & e,
		BinNodePosi(T) hot)
	{
		while(v && v->data != e )
		{
			hot = v;
			v->data > e ? v = v->lChild : v = v->rChild;
		}
		return v;
	}

#define EQUAL(e,v) (!(v) || (e) == (v) -> data) // 节点v（或假象中的通配哨兵）的关键码等于e
	static BinNodePosi(T) & searchIn_I2( 
		BinNodePosi(T) & v,
		const T & e,
		BinNodePosi(T) hot)
	{
		if (EQUAL(e, v)) return;hot = v; // 退化情况，在子树根节点命中
		while(true)
		{
			BinNodePosi(T) & c = (e < hot->data) ? hot->lChild : hot->rChild; // 确定深入方向
			if (EQUAL(e, c))return c;hot = c; // 命中返回，或者深入一层
		} // hot始终指向一个失败节点
	} // 返回时，返回值指向命中节点（或假象的通配哨兵），hot指向其父亲（退化时为初始值 nullptr）

	virtual BinNodePosi(T) insert(const T & e) // 插入
	{
		BinNodePosi(T) & x = search(e); // 查找目标（留意_hot的设置）
		if(!x) // 即禁止雷同元素，故在查找失败时才实施插入操作
		{ 
			x = new BinNide<T>(e, _hot); // 在x处创建新节点，以_hot为父亲
			_size++;updateHeightAbove(x); // 
		}
		return x;
	} // 主要时间复杂度就是search和updateHeightAbove但时间复杂度还是O(h)

	virtual bool remove(const T & e) // 删除
	{
		BinNodePosi(T) x = search(e);
		if (!x) return false;
		removeAt(x, _hot);
		--_size;updateHeightAbove(x);
		return true;
	} // 主要时间复杂度还是search-O(h)和updateHeightAbove-O(h)

	static BinNodePosi(T) removeAt(BinNodePosi(T) & e,BinNodePosi(T) & hot)
	{
		BinNodePosi(T) w = e; // 实际被摘除的节点
		BinNodePosi(T) succ = nullptr; // 被摘除节点的接替者
		// 要分多种情况讨论
		if (!e->lChild) succ = e = e->rChild; // 这两种情况包含了
		else if (!e->rChild) succ = e = e->lChild; // 两个子树都为空的情况，并且能够正确处理
		else
		{
			rand() / 2 ? w = w->pred() : w = w->succ();
			swap(e->data, w->data);
			BinNodePosi(T) u = w->parent; // 原问题变为删除非二度节点w
			((u == e) ? u->rChild : u->lChild) = succ = w->rChild;
		}
		hot = w->parent; // 记录被摘除节点的父亲
		if (succ) succ->parent = hot; // 
		release(w->data);release(w); // 释放被摘除的节点
		return succ;
	} // 时间消耗主要有 succ()-O(h)

	// 通过zag旋转调整，将子树x拉伸成最左侧通路
	void stretchByZag(BinNodePosi(T) & x)
	{
		int h = 0;
		BinNodePosi(T) p = x;while (p->rChild) p = p->rChild; // 最大的节点必是子树的树根
		while (x->lChild) x = x->lChild;x->height = h++; // 转至初始最左侧通路的末端
		for(;x != p;x = x->parent,x->height = h++) // 若x右子树以空，则上升一层
		{
			while (x->rChild) // 否则，反复的
				x->zag(); // 以x为轴做zag旋转
		} // 直到抵达子树的根
	}
};