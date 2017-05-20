/******************************************************************************************
* Data Structures in C++ -- 伸展树(splay)ADT接口
* 丁酉鸡年三月 2017/4/22 9:03
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/
#pragma once

#include"../BST/BST.h"

template <typename NodePosi> inline // 在节点*p与*lc（可能为空）之间建立父子（左）关系
void attachAsLChild(NodePosi p, NodePosi lc) { p->lChild = lc; if (lc) lc->parent = p; }

template <typename NodePosi> inline // 在节点*p与*lc（可能为空）之间建立父子（右）关系
void attachAsRChild(NodePosi p, NodePosi rc) { p->rChild = rc; if (rc) rc->parent = p; };

template <typename T>
class Splay : public BST<T>
{
public:
	Splay();
	~Splay();
protected:

	BinNodePosi(T) splay(BinNodePosi(T) v) // 将v伸展至根
	{
		if (!v) return nullptr; BinNodePosi(T) p; BinNodePosi(T) g; // 父亲、祖父
		while ((p = v->parent) && (g = p->parent)) {
			BinNodePosi(T) gg = g->parent; // 每轮之后，v都将以原曾祖父为父
			if (IsLChild(*v))
				if (IsLChild(*p)) // zig-zig
				{ // 不用真的旋转，直接变换到结果
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
			if (!gg) v->parent = nullptr; // 若*v原来的曾祖父*gg不存在，则*v现在应为树根
			else // 否则，*gg此后应该以*v作为左或右孩子
				(g == gg->lChild) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
			updateHeight(g); updateHeight(p); updateHeight(v);
		}
		if (p = v->parent) // 若p果真非空，则额外再做一次单旋
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

private: // 伸展树的查找也会引起整个树的结构调整，故search()也需要重写

	BinNodePosi(T) & search(const T & e) // 查找（重写）
	{
		BinNodePosi(T) p = searchIn(_root, e, _hot = nullptr);
		// 无论成功与否，最后被访问的有效节点都将伸展至根
		_root = splay(p ? p : _hot);// 成功、失败
		return _root;
	}

	BinNodePosi(T) insert(const T & e) // 插入（重写）
	{
		BinNodePosi(T) p = search(e);
		BinNodePosi(T) rc = p->rChild;
		BinNode<T> v = new BinNode<T>(e);
		attachAsRChild(v, rc);
		attachAsLChild(v, p);
		return v;
	}

	bool remove(const T & e) // 删除（重写）
	{
		if (!_root || (e != search(e)->data)) return false;
		BinNodePosi(T) w = _root; // assert: 经search()后e节点已被伸展至树根
		if (!HasLChild(*_root)) // 若无左子树，直接删除
		{
			_root = _root->rChild; if (_root) _root->parent = nullptr;
		}
		else if (!HasLChild(*_root))
		{
			_root = _root->lChild;
		}
		else
		{ // 若左右子树同时存在，则
			BinNodePosi(T) lTree = _root->lChild;
			lTree->parent = nullptr; _root->lChild = nullptr; // 暂时将左子树切除
			_root = _root->rChild; _root->parent = nullptr; // 只保留右子树
			search(w->data); // 以原树根为目标，做一次（必定失败的）查找
			///// assert: 至此，右子树中最小的节点必伸展至根，且（因无雷同节点）其左子树必空，于是
			_root->lChild = lTree; lTree->parent = _root; // 只需将原左子树接回原为即可
		}
		release(w->data); release(w); _size--;
		if (_root) updateHeight(_root);
		return true;
	}
};