/******************************************************************************************
* Data Structures in C++ -- Graph 的邻接矩阵(adjacency matrix)实现
* 丁酉鸡年二月 2017/3/30 18:56
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../vector/vector.h"
#include "Graph.h"
#include <climits>

// 运用struct，里面的元素全部公有

template <typename Tv> struct Vertex // 顶点对象（为简化起见，并未严格封装）
{
	Tv data;int inDegree, outDegree; VStatus status; // 数据，出入度数，状态
	int dTime, fTime; // 时间标签
	int parent;int priority; // 在遍历树中的父节点，优先级数
	Vertex(Tv const& d = (Tv)0) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
				dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {	} // 暂不考虑权重溢出
};

template <typename Te> struct Edge // 边对象（为简化起见，并未严格封装）
{
	Te data;int weight;EType type; // 数据，权重，类型
	Edge(Te const& d, int w) :data(d), weight(w), type(UNETERMINED) {  } // 构造
};

template <typename Tv,typename Te>
class GraphMatrix :public Graph<Tv, Te> // 基于vector一邻接矩阵方式实现的图
{
private:
	Vector<Vertex<Tv>> V; // 顶点集（向量）
	Vector<Vector<Edge<Te>*>> E; // 边集（邻接矩阵）
public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix()
	{
		for (int j = 0;j < n;j++) // 所有动态创建的边记录
			for (int k = 0;k < n;k++)
				delete E[j][k]; // 逐条清除
	}
	// 顶点的基本操作：查询第i个顶点（0 <= n）
	virtual Tv& vertex(int i) { return V[i].data; } // 数据
	virtual int inDegree(int i) { return V[i].inDegree; } // 入度
	virtual int outDegree(int i) { return V[i].outDegree; } // 出度
	virtual int firstNbr(int i) { return nextNbr(i, n); } // 首个邻接点 （从后往前推）
	virtual int nextNbr(int i,int j) // 相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
	{
		while ((-1 < j) && (!exists(i, --j)));
		return j; // 逆向线性试探
	}
	virtual VStatus& status(int i) { return V[i].status; } // 状态
	virtual int& dTime(int i) { return V[i].dTime; } // 时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; } // 时间标签fTime
	virtual int& parent(int i) { return V[i].parent; } // 在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; } // 在遍历树中的优先级数

//顶点的动态操作
	virtual int insert(Tv const& vertex) // 插入顶点，返回编号
	{
		for (int j = 0;j < n;j++)E[j].insert(nullptr);n++; // 各顶点预留一条潜在的关联边
		E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te>*)nullptr)); // 创建新顶点对应的边向量
		return V.insert(Vertex<Tv>(vertex)); // 顶点向量增加一个顶点
	}

	virtual Tv remove(int i) // 删除第i个顶点及其关联边( 0 <= i < n )
	{
		for(int j = 0;j < n;j++)
			if (exists(i, j))
			{
				delete E[i][j];V[j].inDegree--;
			}
		E.remove(i);n--; // 删除第i行
		Tv vBak = vertex(i);V.remove(i); // 删除顶点i
		for(int j = 0;j < n;j++) // 所有入边
			if(Edge<Te> * e = E[j].remove(i))
			{
				delete e;V[j].outDegree--; // 逐条删除
			}
		return vBak; // 返回被删除顶点的信息
	}

// 边的确认操作
	virtual bool exists(int i,int j) // 边（i,j）是否存在
	{
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != nullptr;
	}

// 边的基本操作：查询顶点i与j之间的联边( 0 <= i,j < n且exists(i,j)
	virtual EType& type(int i, int j) { return E[i][j]->type; } // 边(i,j)的类型
	virtual Te& edge(int i, int j) { return E[i][j]->data; } // 边(i,j)的数据
	virtual int& weight(int i, int j) { return E[i][j]->weight; } // 边(i,j)的权重

// 边的动态操作
	virtual void insert(Te const& edge,int w,int i,int j) // 插入权重为w的边e = (i,j)
	{
		if (exists(i, j)) // 确保该边尚不存在
			return;
		E[i][j] = new Edge<Te>(edge, w); // 创建新边
		e++;V[i].outDegree++;V[j].inDegree++; // 更新边计数与关联顶点的度数
	}
	virtual Te remove(int i,int j) // 删除顶点i和j之间的联边(exists(i,j))
	{
		Te eBak = edge(i, j);delete E[i][j];E[i][j] = nullptr; // 备份后删除边记录
		e--;V[i].outDegree--;V[j].inDegree--; // 更新边计数与关联顶点的度数
		return eBak;
	}
};