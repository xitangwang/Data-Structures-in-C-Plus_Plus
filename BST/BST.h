/******************************************************************************************
* Data Structures in C++ -- ����������ADT�ӿڣ�binary serach tree)
* ���ϼ������� 2017/4/7 23:03
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../BinTree/BinTree.h"

template <typename K,typename V> struct Entry // ����ģ����
{
	K key;V value; // �ؼ��롢��ֵ
	Entry(K k = K(), V v = V()) :key(k), value(v) {}; // Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const & e) :key(e.key), value(e.value) {}; // ��¡
// �Ƚ������е������Ӵˣ������ϸ����ִ��������Ӧ�Ĺؼ��룩
	bool operator< (Entry<K, V> const & e) { return key < e.key; } // С��
	bool operator> (Entry<K, V> const & e) { return key > e.key; } // ����
	bool operator==(Entry<K, V> const & e) { return key == e.key; } // ����
	bool operator!=(Entry<K, V> const & e) { return key != e.key; } // ����
};

template <typename T> class BST : public BinTree<T> // ��BinTree����
{
protected:
	BinNodePosi(T) _hot; // ���нڵ�ĸ���

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

	BinNodePosi(T) rotateAt(BinNodePosi(T) v) // ��ת����
	{
		BinNodePosi(T) p = v->parent;BinNodePosi(T) g = p->parent; // ���ס��游
		if(IsLChild(*p)) // zig
		{
			if(IsLChild(*v)) // zig-zig
			{
				p->parent = g->parent; // ��������
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

public: // ��virtual���Σ��Ա���������д
	virtual BinNodePosi(T) & search(const T & e) // ����
	{
		return searchIn_I(_root, e, _hot = nullptr); // _hot������������㷨
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

	List<BinNodePosi(T)> travIn(BinNodePosi(T) x,const T & l,const T & r) // ���������������#����3�����踨��ջ��
	{
		List<BinNodePosi(T)> list;
		bool backtrack = false; // ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ�
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

	// ����vΪ����(AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
	static BinNodePosi(T) & searchIn_R(
		BinNodePosi(T) & v, // ��ǰ���ӣ�����
		const T & e, // Ŀ��ؼ���
		BinNodePosi(T) hot) // �����ȵ�
	{
		if (!v || v->data == e) return v;
		hot = v; // ���µ�ǰ�ǿսڵ�
		return  searchIn_R(v->data > e ? v->lChild : v->rChild, e, hot);
	} // ����ʱ�������ڷ��ؽڵ�v����ȣ�����������O(h)

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

#define EQUAL(e,v) (!(v) || (e) == (v) -> data) // �ڵ�v��������е�ͨ���ڱ����Ĺؼ������e
	static BinNodePosi(T) & searchIn_I2( 
		BinNodePosi(T) & v,
		const T & e,
		BinNodePosi(T) hot)
	{
		if (EQUAL(e, v)) return;hot = v; // �˻���������������ڵ�����
		while(true)
		{
			BinNodePosi(T) & c = (e < hot->data) ? hot->lChild : hot->rChild; // ȷ�����뷽��
			if (EQUAL(e, c))return c;hot = c; // ���з��أ���������һ��
		} // hotʼ��ָ��һ��ʧ�ܽڵ�
	} // ����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵ nullptr��

	virtual BinNodePosi(T) insert(const T & e) // ����
	{
		BinNodePosi(T) & x = search(e); // ����Ŀ�꣨����_hot�����ã�
		if(!x) // ����ֹ��ͬԪ�أ����ڲ���ʧ��ʱ��ʵʩ�������
		{ 
			x = new BinNide<T>(e, _hot); // ��x�������½ڵ㣬��_hotΪ����
			_size++;updateHeightAbove(x); // 
		}
		return x;
	} // ��Ҫʱ�临�ӶȾ���search��updateHeightAbove��ʱ�临�ӶȻ���O(h)

	virtual bool remove(const T & e) // ɾ��
	{
		BinNodePosi(T) x = search(e);
		if (!x) return false;
		removeAt(x, _hot);
		--_size;updateHeightAbove(x);
		return true;
	} // ��Ҫʱ�临�ӶȻ���search-O(h)��updateHeightAbove-O(h)

	static BinNodePosi(T) removeAt(BinNodePosi(T) & e,BinNodePosi(T) & hot)
	{
		BinNodePosi(T) w = e; // ʵ�ʱ�ժ���Ľڵ�
		BinNodePosi(T) succ = nullptr; // ��ժ���ڵ�Ľ�����
		// Ҫ�ֶ����������
		if (!e->lChild) succ = e = e->rChild; // ���������������
		else if (!e->rChild) succ = e = e->lChild; // ����������Ϊ�յ�����������ܹ���ȷ����
		else
		{
			rand() / 2 ? w = w->pred() : w = w->succ();
			swap(e->data, w->data);
			BinNodePosi(T) u = w->parent; // ԭ�����Ϊɾ���Ƕ��Ƚڵ�w
			((u == e) ? u->rChild : u->lChild) = succ = w->rChild;
		}
		hot = w->parent; // ��¼��ժ���ڵ�ĸ���
		if (succ) succ->parent = hot; // 
		release(w->data);release(w); // �ͷű�ժ���Ľڵ�
		return succ;
	} // ʱ��������Ҫ�� succ()-O(h)

	// ͨ��zag��ת������������x����������ͨ·
	void stretchByZag(BinNodePosi(T) & x)
	{
		int h = 0;
		BinNodePosi(T) p = x;while (p->rChild) p = p->rChild; // ���Ľڵ��������������
		while (x->lChild) x = x->lChild;x->height = h++; // ת����ʼ�����ͨ·��ĩ��
		for(;x != p;x = x->parent,x->height = h++) // ��x�������Կգ�������һ��
		{
			while (x->rChild) // ���򣬷�����
				x->zag(); // ��xΪ����zag��ת
		} // ֱ���ִ������ĸ�
	}
};