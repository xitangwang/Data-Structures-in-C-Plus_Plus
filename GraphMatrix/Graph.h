/******************************************************************************************
* Data Structures in C++ -- Graph ADT接口
* 丁酉鸡年三月 2017/3/30 11:16
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "../stack/Stack@list.h"
#include "../Queue/Queue.h"
#include <climits>

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus; // 顶点状态
typedef enum { UNETERMINED, TREE, CROSS, FORWORD, BACKWORD } EType; // 边在遍历树中所属的类型

template <typename Tv, typename Te> // 顶点类型、边类型
class Graph;

// 优先级更新器

// 最小支撑树
template <typename Tv, typename Te> struct PrimPU // 针对Prim算法的优先级更新器
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) // 对于uk每一尚未发现的邻接顶点v
		{
			if (g->priority(v) > g->weight(uk, v)) // 按Prim策略做松弛
			{
				g->priority(v) = g->weight(uk, v); //更新优先级
				g->parent(v) = uk; // 更新父节点
			}
		}
	}
};

// 最短路径
template <typename Tv, typename Te> struct DijkstraPU // 针对Dijkstra算法的优先级更新器
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (UNDISCOVERED == g->status(v)) // 针对uk每一尚未发现的邻接顶点v，按Dijkstra策略
		{
			if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) // 做松弛
			{
				g->priority(v) = g->priority(uk) + g->weight(uk, v); // 更新优先级
				g->parent(v) = uk; // 并同时更新父节点
			}
		}
	}
};
                                                                                                                                                                                                                                                                                  
// BFS算法
template <typename Tv,typename Te> struct BfsPU
{
	virtual void operator()(Graph<Tv,Te>* g,int uk,int v)
	{
		if (g->status(v) == UNDISCOVERED) // 对于uk每一尚未发现的邻接顶点v
			if (g->priority(v) > g->priority(uk) + 1) // 将其到起点的距离作为优先级数
			{
				g->priority(v) = g->priority(uk) + 1; // 更新优先级数
				g->parent(v) = uk; // 更新父节点
			} // 如此效果等同于，被发现者优先
	}
};

// DFS算法
template <typename Tv,typename Te> struct DfsPU
{
	virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
	{
		if (g->status() == UNDISCOVERED)
		{
			if(g->priority(v) > g->priority(uk) - 1) // 距离顶点越远，优先级越高
			{
				g->priority(v) = g->priority(uk) - 1;
				g->parent(v) = uk;
			}
			return; // 注意：与BfsPU()不同，这里只要有一个邻接点可以更新，即可立即返回
		}
	}
};

template <typename Tv, typename Te> // 顶点类型、边类型
class Graph
{
private:
	void reset() // 所有顶点、边的辅助信息复位
	{
		for (int i = 0; i < n; ++i) // 所有顶点
		{
			status(i) = UNDISCOVERED;dTime(i) = fTime(i) = -1; // 状态、时间标签
			parent(i) = -1;priority(i) = INT_MAX; // （在遍历树中的）父节点、优先级数
			for (int j = 0;j < n;j++) // 所有边的
				if (exists(i, j)) type(i, j) = UNDISCOVERED; // 类型
		}
	}

	void reset_1()
	{
		
	}

	// (连通域）广度优先搜索算法
	int BFS(int v, int& clock)
	{
		// assert:0 <= v < n
		Queue<int> Q; // 引入辅助队列
		status(v) = DISCOVERED;Q.enqueue(v); // 初始化起点
		while (!Q.empty())
		{
			int v = Q.dequeue();dTime(v) = ++clock; // 取出队首顶点v
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // 枚举v的所有邻居u
			{
				if (UNDISCOVERED == status(u)) // 若未被发现，则
				{
					status(u) == DISCOVERED;Q.enqueue(u); // 发现该顶点
					type(v, u) = TREE;parent(u) = v; // 引入树边拓展支撑树
				}
				else // 如果已被发现或被访问
				{
					type(v, u) = CROSS; // 将(v,u)归为跨边
				}
			}
			status(v) = VISITED; // 至此，当前顶点访问完毕
		}
		return v;
	} // S: O(n + e) T: O(n + e)

	// （连通域）深度优先搜索算法--递归版
	void DFS(int v, int& clock)
	{
		// assert:0 <= v < n
		dTime(v) = ++clock;status(v) = DISCOVERED; // 发现当前顶点v
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // 枚举v的所有邻居u
		{
			switch (status(u)) // 根据状态做处理
			{
			case UNDISCOVERED: // u尚未发现，意味着支撑树可在此扩展
				type(v, u) = TREE;parent(u) = v;DFS(u, clock);break;
			case DISCOVERED: // u已被发现但尚未访问，应属被后代指向的祖先
				type(v, u) = BACKWORD;break;
			default: // u已被访问完毕(VISITED,有向图)则视其继承关系为前向边或跨边
				type(v, u) = (dTime(v) < dTime(u)) ? FORWORD : CROSS;break;
			}
		}
		status(v) = VISITED;fTime(v) = ++clock; // 至此，当前顶点v访问完毕
	} // S: O(n + e) T: O(n + e)

	// （连通域）深度优先搜索算法--迭代版
	void DFS_I(int v, int& clock)
	{
		// assert:0 <= v < n
		Stack<int> S;S.push(v); // 发现当前节点，入栈
		while (!S.empty())
		{
			v = S.top();dTime(v) = ++clock;status(v) = DISCOVERED;// 发现当前顶点v
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u))
			{
				switch (status(u))
				{
				case UNDISCOVERED: // u尚未发现，意味着支撑树可在此扩展
					type(v, u) = TREE;parent(u) = v;S.push(u);break;
				case DISCOVERED: // u已被发现但尚未访问，应属被后代指向的祖先
					type(v, u) = BACKWORD;break;
				default: // u已被访问完毕(VISITED,有向图)则视其继承关系为前向边或跨边
					type(v, u) = (dTime(v) < dTime(u)) ? FORWORD : CROSS;break;
				}
			}
			status(v) = VISITED;fTime(v) = ++clock;S.pop(); // 至此，当前顶点v访问完毕
		} // S: O(n + e) T: O(n + e)
	}

	// （连通域）基于DFS的双向连通分量分解算法
#define hca(x) (fTime(x)) // 顶点v所能连通的最高祖先
	void BCC(int v, int& clock, Stack<int>& S)
	{
		// assert: 0 <= v < n
		hca(v) = dTime(v) = ++clock;status(v) = DISCOVERED;S.push(v); //v被发现并入栈
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) //
		{
			switch (status(u))
			{
			case UNDISCOVERED:
				parent(u) = v;BCC(u, clock, S); // 从顶点u深入
				if (hca(u) < dTime(v)) // 遍历返回后，若发现u（通过后向边）可以指向v的真祖先
					hca(v) = min(hca(v), hca(u)); // 则v亦必如此
				else // 否则，以v为关节点（u以下即是一个BCC，且其中顶点正集中于栈S的顶部）
				{
					while (v != S.pop()); // 依次弹出当前BCC中的节点，亦可转存于其他结构
					S.push(v); // 最后一个顶点（关节点）重新入栈--分摊不足一次
				}
				break;
			case DISCOVERED:
				if (u != parent(v))hca(v) = min(hca(v), dTime(u)); // 更新hca[v]
				break;
			default:
				break;
			}
		}
		status(v) = VISITED; // 对v的访问结束
	}
#undef hca

	// （单趟）基于DFS的拓扑排序算法
	bool TSort(int v, Stack<Tv>* S)
	{
		// assert: 0 <= v < n
		status(v) = DISCOVERED; // 发现顶点v
		for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
		{
			if(status(u) == UNDISCOVERED)
			{
				parent(u) = v;
				if (!TSort(u,  S))
					return false;
			}
		}
		status(v) = VISITED;S->push(vertex(v)); //
		return true;
	}

	bool TSort_1(int v, int& clock, Stack<Tv>* S)
	{
		for (int i = 0; i < n; ++i)
			if (inDegree(i) == 0)
				S->push(vertex(i));
		Queue<Tv> Q;
		while (!S->empty())
		{
			Q.enqueue(v = S->pop());
			for (int u = firstNbr(v);-1 < u;u = nextNbr(v,u))
			{
				if (inDegree(u) < 2)
					S->push(vertex(u));
			}
			remove(v);
		}
		return n == 0 ? true : false;
	}

	// (连通域）优先级搜索框架
	template <typename PU>
	void PFS(int s,PU prioUpdater)
	{
		priority(s) = 0;status(s) = VISITED;parent(s) = -1; // 初始化，起点s加入PFS数中
		while(true) // 将下一节点和边加入PFS树中
		{
			for (int w = firstNbr(s);-1 < w;w = nextNbr(s, w)) // 枚举s的所有邻居
				prioUpdater(this, s, w); // 更新顶点w的优先级及其父节点
			for(int shortest = INT_MAX,w = 0;w < n;w++) // 遍历每一个节点
				if(UNDISCOVERED == status(w)) // 从尚未加入遍历树的顶点中
					if(shortest > priority(w)) // 选出下一个
					{
						shortest = priority(w);s = w; // 优先级最高的顶点s
					} 
			if (VISITED == status(s))break; // 直至所有顶点均以加入
			status(s) = VISITED;type(parent(s), s) = TREE; // 将s及其父节点的联边加入遍历树
		}
	} // 通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能

public:
	virtual ~Graph() = default;
	// 顶点
	int n; // 顶点总数
	virtual int insert(Tv const&) = 0; // 插入顶点，返回编号
	virtual Tv remove(int) = 0; // 删除顶点及其关联边，返回顶点信息
	virtual Tv& vertex(int) = 0; // 顶点v的数据（该顶点的确存在）
	virtual int inDegree(int) = 0; // 顶点的入度（该顶点的确存在）
	virtual int outDegree(int) = 0; // 顶点的出度（该顶点的确存在）
	virtual int firstNbr(int) = 0; // 顶点v的首个邻接顶点
	virtual int nextNbr(int, int) = 0; // 顶点v的（相对于顶点j的）下一个邻接顶点
	virtual VStatus& status(int) = 0; // 顶点v的状态
	virtual int& dTime(int) = 0; // 顶点v的时间标签dTime
	virtual int& fTime(int) = 0; // 顶点v的时间标签fTime
	virtual int& parent(int) = 0; // 顶点v在遍历树中的父亲
	virtual int& priority(int) = 0; // 顶点v在遍历树中的优先级数
// 边：这里约定，无向边均转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
	int e; // 边总数
	virtual bool exists(int, int) = 0; // 边(v,u)是否存在
	virtual void insert(Te const&, int, int, int) = 0; // 在顶点v和u之间插入权重为w的边e
	virtual Te remove(int, int) = 0; // 删除顶点v和顶点u之间的边e，返回该边信息
	virtual EType& type(int, int) = 0; // 边（v，u）的类型
	virtual Te& edge(int, int) = 0; // 边（v，u）的数据（该边确实存在）
	virtual int& weight(int, int) = 0; // 边（v，u）的权重
// 算法
	void bfs(int s) // 广度优先搜索算法(全图）
	{
		// assert:0 <= s < n
		reset();int clock = 0;int v = s; //初始化
		do
			if (UNDISCOVERED == status(v)) // 一旦遇到尚未发现的顶点
				BFS(v, clock); // 即从该点出发启动一次BFS
		while (s != (v = (++v % n))); // 循环一遍再倒回来时结束
	}
	void dfs(int s) // 深度优先搜索算法(全图）
	{
		// assert:0 <= s < n
		reset();int clock = 0;int v = s; //初始化
		do
			if (UNDISCOVERED == status(v)) // 一旦遇到尚未发现的顶点
				DFS(v, clock); // 即从该点出发启动一次DFS
		while (s != (v = (++v % n))); // 循环一遍再倒回来时结束
	}
	void bcc(int s) // 基于DFS的双连通分量分解算法
	{
		reset();int clock = 0;int v = s;Stack<int> S; // 栈S用以记录访问过的顶点
		do
			if (UNDISCOVERED == status(v)) // 一旦发现还未发现的点（新连通分量）
			{
				BCC(v, clock, S); // 即从该顶点出发启动一次BCC
				S.pop(); // 遍历返回后，弹出栈中最后一个顶点--当前连通域的起点
			}
		while (s != (v = (++v % n)));
	}
	Stack<Tv>* tSort(int s) // 基于DFS的拓扑排序算法
	{
		// assert: 0 <= s < n
		reset();int clock = 0;int v = s;
		Stack<Tv> S = new Stack<Tv>; // 用栈记录排序顶点
		do
		{
			if (UNDISCOVERED == status(v))
				if (!TSort(v, clock, S)) // clock并非必须
				{
					while (!S.empty()) // 任一连通域（亦即整图）非DGA
						S.pop();break; // 则不必继续，直接返回
				}
		} while (s != (v = (++v % n)));
		return S;
	}
	void prim(int s) // 最小支撑树prim算法
	{
		pfs<PrimPU>(s, PrimPU<Tv, Te>());
	}
	void dijkstra(int s) // 最短路径Dijkstra算法
	{
		pfs<DijkstraPU>(s, DijkstraPU<Tv, Te>());
	}
	template <typename PU> void pfs(int s, PU prioUpdater) // 优先级搜索框架
	{
		// assert: 0 <= s < n
		reset();int v = s; // 初始化
		do
			if (UNDISCOVERED == status(v))
				PFS(v, prioUpdater);
		while (s != (v = (++v % n))); //
	}

// 图的特例，树的算法 习题[6-10]

	Stack<int> DIA() // 直径（即相隔最远的两个顶点的通路）
	{
		Stack<int> Dia;
		int clock = 0;
		int b;
		int v = b = BFS(0, clock);
		reset();
		v = BFS(v, clock);
		Dia.push(v);
		while (Dia.top() != b)
		{
			Dia.push(parent(Dia.top()));
		}
		return Dia;
	}

// 欧拉环路 习题[6-11]

	bool eulerCircle(List<int> & euler,int v = 0)
	{
		status(v) = DISCOVERED; // 发现当前顶点v
		euler.insertAsLast(v);
		for (int u = firstNbr(v);-1 < u;u = nextNbr(v, u)) // 枚举v的所有邻居u
		{
			if (inDegree(u) != outDegree(u)) // 一旦发现入度与出度不相等的点，则没有欧拉环路
				return false;
			if(status(u) == UNDISCOVERED) 
			{   // 记录沿途各边
				euler.insertAsLast(u);
				remove(u, v); // 并随即删除
				if (inDegree(u) || outDegree(u)) // 一旦有顶点度数为零
					remove(u);
				if (inDegree(v) || outDegree(v)) // 则随即将其删除
					remove(v);
			}
		}
		status(v) = VISITED; // 至此，当前顶点v访问完毕
	}

	bool EulerCircle(List<int> Euler)
	{
		int s;
		reset();int v = s  = 0; //初始化
		do
		{
			if (UNDISCOVERED == status(v)) // 一旦遇到尚未发现的顶点
			{
				List<int> euler;
				if (!eulerCircle(euler, v))
					return false;
				ListNodePosi(int) p = Euler.find(euler.first()->data);
				if (p != nullptr)
				{
					for (int i = euler.size() - 1;i >= 0 ;--i)
					{
						Euler.insertBefore(p, euler[i]);
					}
				}
				else
				{
					for (int i = 0;i < euler.size();++i)
					{
						Euler.insertAsLast(euler[i]);
					}
				}
			}
		}while (s != (v = (++v % n))); // 循环一遍再倒回来时结束
		return true;
	}
};
