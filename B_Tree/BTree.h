/******************************************************************************************
* Data Structures in C++ -- BTree ADT�ӿ�
* ���ϼ������� 2017/5/20 : 16:56
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../vector/vector.h"
#include "../_share/release.h"

#define BTNodePosi(T) BTNode<T>*

template <typename T> struct BTNode
{
	BTNodePosi(T) parent; // ���ڵ�
	Vector<T> key; // �ؼ�������
	Vector<BTNodePosi(T)> child; // �����������䳤���ܱ�key ��һ�㣩
	// ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼ��ʱ��0���ؼ����1���պ���ָ�룩
	BTNode() { parent = nullptr;child.insert(0, nullptr); }
	BTNode(T e,BTNodePosi(T) lc = nullptr,BTNodePosi(T) rc = nullptr)
	{
		parent = nullptr; // ��Ϊ���ڵ㣬���ҳ�ʼʱ
		key.insert(0, e); // ֻ��һ���ؼ��룬�Լ�
		child.insert(0, lc);child.insert(1, rc); // ��������
		if (lc) lc->parent = this;if (rc) rc->parent = this;
	}
};

template <typename T> 
class BTree // BTreeģ����
{
protected:
	int _size; // ��Źؼ�������
	int _order; // B-���Ľ״Σ�����Ϊ��--����ʱָ��
	BTNodePosi(T) _root; // ���ڵ�
	BTNodePosi(T) _hot; // BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ��
	void solveOVerflow(BTNodePosi(T) v) // ����������֮��ķ��Ѵ���
	{
		if (_order >= v->child.size()) return; // �ݹ������ǰ�ڵ㲢δ����
		Rank s = _order / 2; // ��㣨��ʱӦ��_order = key.size() = child.size() - 1��
		BTNodePosi(T) u = new BTNode<T>(); // ע�⣺�½ڵ�����һ���պ���
		for(Rank j = 0;j < _order - s - 1;j++) // v�Ҳ�_order - s - 1�����Ӽ��ؼ������Ϊ�Ҳ�ڵ�u
		{
			u->child.insert(j, v->child.remove(s + 1)); // ����ƶ�Ч�ʵ�
			u->key.insert(j, v->key.remove(s + 1)); // �β��ԿɸĽ�
		}
		u->child[_order - s - 1] = v->child.remove(s + 1); // �ƶ�v��ҵĺ���
		if (u->child[0]) // ��u�ĺ����Ƿǿգ���
			for (Rank j = 0; j < _order; ++j)
				u->child[j]->parent = u;
		BTNodePosi(T) p = v->parent; // v��ǰ�ĸ��ڵ�p
		if (!p) { _root = p = new  BTNode<T>(); p->child[0] = v; v->parent = p; } // ��pΪ���򴴽�֮
		Rank r = 1 + p->key.serach(v->key[0]); // p��ָ��u��ָ�����
		p->key.insert(r, v->key.remove(s));
		p->child.insert(r + 1, u); u->parent = p; // �½ڵ��븸�ڵ�u����
		solveOVerflow(p); // ����һ�㣬����б�Ҫ��������ѡ�������ݹ�O(logn)��
	}
	void solveUnderflow(BTNodePosi(T) v) // ��ɾ��������֮��ĺϲ�����
	{
		if ((_order + 1) / 2 <= (v->child.size())) return; // �ݹ������ǰ�ڵ㲢δ����
		BTNodePosi(T) p = v->parent;
		if(!p) // �ݹ�����ѵ����ڵ㣬û�к��ӵ�����
		{
			if(!v->key.size() && v->child[0])
			{
				// ��������Ϊ������v�Ѳ������ؼ��룬ȴ�У�Ψһ�ģ��ǿպ��ӣ���
				_root = v->child[0]; _root->parent = nullptr; // ����ڵ���Ա�����
				v->child[0] = nullptr; release(v); // ���������ö�������
			} // �����߶Ƚ���һ��
			return;
		}
		Rank r = 0; while (p->child[r] != v) r++;
		// ȷ��v��p�ĵ�r�����ӡ�����ʱv���ܲ����ؼ��룬�ʲ���ͨ���ؼ������
		// ���⣬��ʵ���˺���ָ����е���֮��Ҳ��ֱ�ӵ���Vector::find()��λ
	// ���1�������ֵܽ�ؼ���
		if(0 < r) // ��v����p�ĵ�һ�����ӣ���
		{
			BTNodePosi(T) ls = p->child[r - 1]; // ���ֵܱش���
			if((_order + 1) / 2 < ls->child.size()) // �����ֵ��㹻���֡���
			{
				v->key.insert(0, p->key[r - 1]); // p���һ���ؼ����v����Ϊ��С�ؼ��룩
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1); // ls�����ؼ���ת��p
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));
				// ͬʱls�����Ҳຢ�ӹ��̸�v
				if (v->child[0]) v->child[0]->parent = v; // ��Ϊv������ຢ��
				return; // ���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
			}
		} // ���ˡ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ�
	// ���2�������ֵܽ�ؼ���
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

	// ���3�������ֵ�ҪôΪ�գ�������ͬʱ����Ҫô̫���ݡ������ϲ�
		if(0 < r)
		{
			BTNodePosi(T) ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
			// p�ĵ�r - 1���ؼ���ת��ls��v������p�ĵ�r������
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

	int order() const { return _order; } // �״�

	int size() const { return _size; } // ��ģ

	BTNodePosi(T) & root() { return _root; } // ����
	
	bool empty() const { return !_root; } // �п�

	BTNodePosi(T) search(const T & e) // ����
	{
		BTNodePosi(T) v = _root; _hot = nullptr; // �Ӹ��ڵ����
		while(v) // ������
		{
			Rank r = v->key.serach(e); // �ڵ�ǰ�ڵ����ҵ������ڴ���e�Ĺؼ���
			if ((0 <= r) && (e == v->key[r])) return v; // ���ɹ����ڵ�ǰ�ڵ�����Ŀ��ؼ���
			_hot = v; v = v->child[r + 1]; // ����ת���Ӧ������_hotָ���丸��������Ҫ��I/O�����ʱ��
		} // ������������ʱ���֣���ͨ����_order����ֱ��˳�����
		return nullptr;
	}

	bool insert(const T & e) // ����
	{
		BTNodePosi(T) v = search(e); if (v) return false; // ȷ��Ŀ��㲻����
		Rank r = _hot->key.serach(e); // �ڽڵ�_hot������ؼ��������в����ʺϵ�λ�ò���
		_hot->key.insert(r + 1, e);
		_hot->child.insert(r + 2, nullptr); // ����ؼ���ͺ���
		_size++;
		solveOVerflow(_hot);
		return true;
	}

	bool remove(const T & e) // ɾ��
	{
		BTNodePosi(T) v = search(e); if (!v) return false; // ȷ�Ϲؼ������
		Rank r = v->key.serach(e);
		if(v->child[0]) // ��v��Ҷ�ӣ���e�ĺ�̱�����ĳҶ�ڵ㡪��������к��ӣ��Ͳ���Ҷ�ڵ�
		{
			BTNodePosi(T) u = v->child[r + 1]; // ����������һֱ���󣬼���
			while (u->child[0]) u = u->child[0]; // �ҳ�e�ĺ��
			v->key[r] = u->key[0]; v = u; r = 0; // ����֮����λ��
		} // ���ˣ�v��Ȼλ����ײ㣬�����е�r���ؼ�����Ǵ�ɾ����
		v->key.remove(r); v->child.remove(r + 1); _size--;
		solveUnderflow(v);
		return true;
	}
}; // BTree
