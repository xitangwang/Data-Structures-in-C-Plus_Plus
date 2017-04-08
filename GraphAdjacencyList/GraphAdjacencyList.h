/******************************************************************************************
* Data Structures in C++ -- Graph 的邻接表(adjacency matrix)实现
* 丁酉鸡年三月 2017/4/5 0：00
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../vector/vector.h"
#include "../GraphMatrix/Graph.h"

/*
template <typename Tv> struct Vertex // 顶点对象（为简化起见，并未严格封装）
{
	Tv data;int inDegree, outDegree, VStatus, status; // 数据，出入度数，状态
	int dTime, fTime; // 时间标签
	int parent;int priority; // 在遍历树中的父节点，优先级数
	Vertex(Tv const& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {	} // 暂不考虑权重溢出
};

template <typename Te> struct Edge // 边对象（为简化起见，并未严格封装）
{
	Te data;int weight;EType type; // 数据，权重，类型
	int v; // 关联顶点
	Edge(Te const& d, int w,int v) :data(d), weight(w), type(UNETERMINED),v(v) {  } // 构造
};

*/

template <typename Tv,typename Te> // 顶点类型、边类型
class GraphAdjacencyList : public Graph<Tv,Te>
{
private:
	Vector<Vertex<Tv>> V; // 顶点集（向量）
	Vector<List<Edge<Te>*>> E; // 边集（邻接表）

public:
	GraphAdjacencyList() { n = e = 0; }
	~GraphAdjacencyList()
	{
		
	}

// 顶点的基本操作：查询第i个顶点(0 <= n)
	virtual Tv& vertex(int i) { return V[i].data; } 
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual int firstNbr(int i) { return E[i][0].v;}
	virtual int nextNbr(int i,int j)
	{
		return E[i][++j].v;
	} // 改变了下一个邻居的接口，各种搜索算法必须要改变一下
	virtual VStatus& status(int i) { return V[i].status; } // 状态
	virtual int& dTime(int i) { return V[i].dTime; } // 时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; } // 时间标签fTime
	virtual int& parent(int i) { return V[i].parent; } // 在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; } // 在遍历树中的优先级数

// 顶点的动态操作
	virtual int insert(Tv const& vertex) // 
	{
		E.insert(List<Edge<Te>*>()); // 增加一条邻接表
		return V.insert(Vertex<Tv>(vertex));
	}

	virtual Tv remove(int i) // 删除第i个顶点及其关联边( 0 <= i < n )
	{
		for(int j = 0;j < E[i].size();++j)
		{
			Edge<Te>* e = E[i].remove(j);
			delete e;V[i].inDegree--;--j;
		}
		for(int m = 0;m < E.size();++m)
		{
			for(int n = 0;n < E[m].size();++n)
			{
				if (E[m][n].v > i)
					E[m][n].v--;
				else if(E[m][n].v == i)
				{
					Edge<Te>* e = E[m].remove(n);
					delete e;V[m].inDegree--;--n;
				}
			}
		}
		Tv vBak = vertex(i);V.remove(i); // 删除顶点i
		return vBak;
	}
// 边的确认操作
	virtual bool exists(int i,int j) // 
	{
		for(int n = 0;i < E[i].size();++n)
		{
			if (E[i][n].v == j)
				return true;
		}
		return false;
	}

// 边的基本操作：查询顶点i与j之间的联边( 0 <= i,j < n且exists(i,j)
	virtual EType& type(int i, int j) { return E[i][j]->type; } // 边(i,j)的类型
	virtual Te& edge(int i, int j) { return E[i][j]->data; } // 边(i,j)的数据
	virtual int& weight(int i, int j) { return E[i][j]->weight; } // 边(i,j)的权重

//边的动态操作
	virtual void insert(Te const& edge,int w,int i,int j) // 插入权重为w的边e = (i,j)
	{
		if (exists(i, j))
			return;
		E[i].insert(new Edge<Te>(edge, w,j));
		e++;V[i].outDegree++;V[j].inDegree++;
	}

	virtual Te remove(int i,int j) // 删除顶点i的第j个联边(exists(i,j))
	{
		Te eBak = edge(i, j);E[i].remove(j);
		e--;V[i].outDegree--;V[eBak.v].inDegree--;
		return eBak;
	}
};
