/******************************************************************************************
* Data Structures in C++ -- ��չ��(splay)ADT�ӿ�
* ���ϼ������� 2017/4/22 9:03
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/
#pragma once

#include"../BST/BST.h"

template <typename NodePosi> inline // �ڽڵ�*p��*lc������Ϊ�գ�֮�佨�����ӣ��󣩹�ϵ
void attachAsLChild(NodePosi p, NodePosi lc) { p->lChild = lc; if (lc) lc->parent = p; }

template <typename NodePosi> inline // �ڽڵ�*p��*lc������Ϊ�գ�֮�佨�����ӣ��ң���ϵ
void attachAsRChild(NodePosi p, NodePosi rc) { p->rChild = rc; if (rc) rc->parent = p; };

template <typename T>
class Splay : public BST<T>
{
public:
	Splay();
	~Splay();
protected:

	BinNodePosi(T) splay(BinNodePosi(T) v) // ��v��չ����
	{
		if (!v) return nullptr; BinNodePosi(T) p; BinNodePosi(T) g; // ���ס��游
		while ((p = v->parent) && (g = p->parent)) {
			BinNodePosi(T) gg = g->parent; // ÿ��֮��v������ԭ���游Ϊ��
			if (IsLChild(*v))
				if (IsLChild(*p)) // zig-zig
				{ // ���������ת��ֱ�ӱ任�����
					attachAsLChild(g, p->rChild); attachAsLChild(p, v->rChild);
					attachAsRChild(p, g); attachAsRChild(v, p);
				}
				else // zig-zag
				{
					attachAsRChild(p, v->lChild); attachAsLChild(g, v->rChild);
					attachAsLChild(v, p); attachAsRChild(v, g);
				}
			else
				if (IsLChild(*p)) // zag-zig
				{
					attachAsRChild(g, v->lChild); attachAsLChild(p, v->rChild);
					attachAsLChild(v, g); attachAsRChild(v, p);
				}
				else // zag-zag
				{
					attachAsRChild(g, p->lChild); attachAsRChild(p, v->lChild);
					attachAsLChild(p, g); attachAsRChild(v, p);
				}
			if (!gg) v->parent = nullptr; // ��*vԭ�������游*gg�����ڣ���*v����ӦΪ����
			else // ����*gg�˺�Ӧ����*v��Ϊ����Һ���
				(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
			updateHeight(g); updateHeight(p); updateHeight(v);
		}
		if (p = v->parent) // ��p����ǿգ����������һ�ε���
		{
			if (IsLChild) {
				attachAsLChild(p, v->rChild); attachAsRChild(v, p);
			}
			else {
				attachAsRChild(p, v->lChild); attachAsLChild(v, p);
				updateHeight(p); updateHeight(v);
			}
		}
		v->parent = nullptr;
		return v;
	}

private: // ��չ���Ĳ���Ҳ�������������Ľṹ��������search()Ҳ��Ҫ��д

	BinNodePosi(T) & search(const T & e) // ���ң���д��
	{
		BinNodePosi(T) p = searchIn(_root, e, _hot = nullptr);
		// ���۳ɹ������󱻷��ʵ���Ч�ڵ㶼����չ����
		_root = splay(p ? p : _hot);// �ɹ���ʧ��
		return _root;
	}

	BinNodePosi(T) insert(const T & e) // ���루��д��
	{
		BinNodePosi(T) p = search(e);
		BinNodePosi(T) rc = p->rChild;
		BinNode<T> v = new BinNode<T>(e);
		attachAsRChild(v, rc);
		attachAsLChild(v, p);
		return v;
	}

	bool remove(const T & e) // ɾ������д��
	{
		if (!_root || (e != search(e)->data)) return false;
		BinNodePosi(T) w = _root; // assert: ��search()��e�ڵ��ѱ���չ������
		if (!HasLChild(*_root)) // ������������ֱ��ɾ��
		{
			_root = _root->rChild; if (_root) _root->parent = nullptr;
		}
		else if (!HasLChild(*_root))
		{
			_root = _root->lChild;
		}
		else
		{ // ����������ͬʱ���ڣ���
			BinNodePosi(T) lTree = _root->lChild;
			lTree->parent = nullptr; _root->lChild = nullptr; // ��ʱ���������г�
			_root = _root->rChild; _root->parent = nullptr; // ֻ����������
			search(w->data); // ��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ�����
			///// assert: ���ˣ�����������С�Ľڵ����չ�������ң�������ͬ�ڵ㣩���������ؿգ�����
			_root->lChild = lTree; lTree->parent = _root; // ֻ�轫ԭ�������ӻ�ԭΪ����
		}
		release(w->data); release(w); _size--;
		if (_root) updateHeight(_root);
		return true;
	}
};