// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_8_GRAPH_H
#define DST_8_GRAPH_H

// 第八章：图

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 8.1 图（graph）的基本概念
	// 最后修改：2019-11-7
	namespace _8_1 {
		// 8.1.1 图的定义
		// 图（graph）G由两个集合V（vertex）和E（edge）组成，记G=(V,E)，
		// 其中V是顶点的有限集合，记为V(G)；E是连接V中两个不同顶点（顶点对）的边的有限集合，记为E(G)
		// 如果表示边的顶点对（或序偶）是有序的，则图G为有向图（digraph），<i,j> 和 <j,i>是两条不同的边
		// 如果表示边的顶点对是无序的，则图G为无向图（undirgraph），(i,j) 和 (j,i) 是同一条边

		/* 图的抽象数据类型定义如下：
		ADT Graph {
			数据对象:
				D = { ai | 1 <= i <= n, n >= 0, ai 为ElemType类型 }    // ElemType 是自定义类型标识符
			数据关系:
				R = { <ai, aj> | ai、aj ∈ D, 1 <= i,j <= n, 其中每个元素可以有零或多个前驱元素，可以有零或多个后继元素 }
			基本运算:
				CreateGraph(&g);
				DestroyGraph(&g);
				DispGraph(g);
				DFS(g,v);    // 从顶点v出发深度优先遍历图g，Depth First Search
				BFS(g,v);    // 从顶点v出发广度优先遍历图g，Breadth First Search
				...
		}
		*/

		// 图的基本术语
		// 1、端点（endpoint）和邻接点（adjacent）；有向图中还分起始端点（简称起点）、终止端点（简称终点）、出边邻接点、入边邻接点
		// 2、顶点的度（degree）：一个顶点所关联的边的数目；有向图中还分入度（indegree）和出度（outdegree），之和为有向图顶点的度
		// 3、完全图（completed graph）：每两个顶点之间都存在着一条边，即任意两点之间课直接一次到达；无向图边数为n(n-1)/2，有向图边数为n(n-1)
		// 4、稠密图（dense graph）：当一个图接近完全图时（如e < n·log2(n))，稀疏图（sparse graph）
		// 5、子图（subgraph）：G'=(V',E') 其中V'是V的子集，E'是E的子集，则G'是G的子集；G的子图一定是个图，并非任意V和E的子集都能构成图
		// 6、路径（path）和路径长度（path length）：从i到j的路径是一个顶点序列；路径长度是一条路径上经过边的数目；
		//    若除了起点和终点外，不重走任一中间点的路径为简单路径（simple path）
		// 7、回路或环（cycle）：开始点与结束点为同一个顶点的路径；若还是简单路径，则为简单回路或简单环（simple cycle）
		// 8、连通、连通图（connected graph（无向图中）：从i到j有路径则称为连通；图G中任意两点都连通则称为连通图，否则是非连通图；
		//	  连通分量（connected component）：无向图G中极大连通子图称为G的连通分量，显然连通图的连通分量只有一个为自身，非连通图有多个连通分量
		// 9、强连通图（strongly connected graph）和强连通分量（strongly connected graph）：有向图中定义类似无向图中，需要求i到j和j到i都有连通
		// 10、权（weight）和网（net）：每一个边都可以附有一个对应的数值，称为权，这样的图为带权图（weighted graph），也称作网（net）

		// 例8.1 n (n > 2) 个顶点的强连通图边的取值范围： n <= e <= n(n-1)

	} // namespace _8_1 图的基本概念

	// 8.2 图的存储结构和基本运算算法
	// n各顶点物理编号：[0...n-1]
	// 图的存储需要存储各个顶点本身的信息，还要同时存储顶点与顶点之间的所有关系（边的信息）
	// 最后修改：2019-11-14
	namespace _8_2 {
		// 8.2.1 邻接矩阵（adjacency matrix）存储方法
		// 顶点的信息类型：char
		// 最后修改：2019-11-7
		namespace _8_2_1 {
			// 用n阶方阵的位置[i][j]表示i到j之间是否连接
			// 不带权的用1表示连通，0表示不连通；带权的用w表示权，0表示对角线位置，∞表示不连通

			const int MAXV = 50;    // 最大顶点个数
			const int INF = INT_MAX;    // 定义∞

			typedef char InfoType;    // 表示顶点的其他信息类型，此处为char

			typedef struct {
				int no;    // 顶点的编号
				InfoType info;
			} VertexType;    // 定点类型

			typedef struct {
				int edges[MAXV][MAXV];    // 邻接矩阵，[i][j]表示 i->j 的边
				int n, e;    // n表示顶点数，e表示边数
				VertexType vexs[MAXV];    // 存放顶点信息
			} MatGraph;    // 完整的图的邻接矩阵类型

		} // END namespace _8_2_1 邻接矩阵存储方法

		// 8.2.2 邻接表（adjacency list）存储方法
		// 顶点中存储的信息类型：char
		// 最后修改：2019-11-7
		namespace _8_2_2 {
			// 对于含n各顶点（从0到n-1编号）的图，用长度为n的数值存储头结点（有值域data和指向相邻顶点的指针firstarc），其中组数下标即顶点编号
			// 对于边结点，需存储它的顶点编号adjvex，下一个边结点的指针nextarc，和其边的权值weight
			// 注：边结点顺序可任意，故邻接表存储方法不唯一；有向图默认连接的是顶点的出边
			// 逆邻接表（inverse adjacency list）：在有向图的邻接表中对每个顶点连接的的是指向该顶点的边（入边），以方便找指向某顶点的边

			typedef struct Anode {
				int adjvexNo;    // 该边的邻接点编号
				struct Anode* nextArc;    // 指向下一个边结点的指针
				int weight;    // 该边的相关信息，如权重
			} ArcNode;    // 边结点类型

			typedef int InfoType;

			typedef struct Vnode {
				InfoType info;    // 顶点的其他信息
				ArcNode* firstArc;    // 指向第一个边结点
			} VNode;    // 邻接表的头结点类型

			const int MAXV = 50;

			typedef struct {
				VNode adjList[MAXV];    // 邻接表的头结点数组
				int n, e;    // n表示顶点数，e表示边数
			} AdjGraph;    // 完整的图的邻接表类型

		} // END namespace _8_2_2 邻接表存储方法

		// 8.2.3 图基本运算算法设计
		// 讨论的是邻接表的相关算法设计
		// 最后修改：2019-11-14
		namespace _8_2_3 {
			// 引用图的邻接矩阵、邻接表存储方式
			using dst::_8_2::_8_2_1::MatGraph;
			using dst::_8_2::_8_2_1::INF;
			using dst::_8_2::_8_2_1::MAXV;
			using dst::_8_2::_8_2_2::ArcNode;
			using dst::_8_2::_8_2_2::AdjGraph;

			// 创建图的运算算法
			// 根据邻接矩阵数组A，顶点个数n和边数e来建立图的邻接表G
			// 扫描数组A查找不为0和∞的元素
			void CreateAdj(AdjGraph*& G, int** edges, int n, int e) {
				ArcNode* p;
				G = (AdjGraph*)malloc(sizeof(AdjGraph));
				for (int i = 0; i < n; G->adjList[i++].firstArc = NULL);    // 给邻接表中的所有头结点的指针域置初值
				for (int i = 0; i < n; ++i) {
					for (int j = n - 1; j >= 0; --j) {
						// 检查邻接矩阵中的每个元素
						if (edges[i][j] != 0 && edges[i][j] < INF) {
							p = (ArcNode*)malloc(sizeof(ArcNode));    // 创建一个结点p
							p->adjvexNo = j;    // 邻接结点编号
							p->weight = edges[i][j];    // 存放权
							p->nextArc = G->adjList[i].firstArc;    // 采用头插法插入结点p
							G->adjList[i].firstArc = p;    // 采用头插法插入结点p
						}
					}
				}
				G->n = n;
				G->e = e;
			}

			// 输出图的运算算法
			void DispAdj(AdjGraph* G) {
				ArcNode* p;
				for (int i = 0; i < G->n; ++i) {
					printf("%d：", i);    // 输出结点编号
					p = G->adjList[i].firstArc;
					while (p != NULL) {
						printf("=%d=>%d ", p->weight, p->adjvexNo);
						p = p->nextArc;
					}
					printf("\n");
				}
			}

			// 销毁图的运算算法
			void DestroyAdj(AdjGraph*& G) {
				ArcNode *pre, *p;
				for (int i = 0; i < G->n; ++i) {
					pre = G->adjList[i].firstArc;
					if (pre != NULL) {
						p = pre->nextArc;
						while (p != NULL) {
							free(pre);
							pre = p;
							p = pre->nextArc;
						}
						free(pre);
					}
				}
				free(G);
			}

			// 例8.2 对于具有n个顶点的图G
			// (1)、设计一个将邻接矩阵转换为邻接表的算法
			// (2)、设计一个将邻接表转换为邻接矩阵的算法
			// (3)、分析上述连个算法的时间复杂度 O(n^2) O(n + e)

			// 例8.2 (1)、设计一个将邻接矩阵转换为邻接表的算法
			// 在图的邻接矩阵中查找不为0和∞的元素，类似Create算法
			void MatToList(MatGraph g, AdjGraph*& G) {
				ArcNode* p;
				G = (AdjGraph*)malloc(sizeof(AdjGraph));
				for (int i = 0; i < g.n; G->adjList[i++].firstArc = NULL);    // 给邻接表中的所有头结点的指针域置初值
				for (int i = 0; i < g.n; ++i) {
					for (int j = g.n - 1; j >= 0; --j) {
						// 检查邻接矩阵中的每个元素
						if (g.edges[i][j] != 0 && g.edges[i][j] < INF) {
							p = (ArcNode*)malloc(sizeof(ArcNode));
							p->adjvexNo = j;    // 顶点编号
							p->weight = g.edges[i][j];
							p->nextArc = G->adjList[i].firstArc;
							G->adjList[i].firstArc = p;    // 头插
						}
					}
				}
				G->n = g.n;
				G->e = g.e;
			}

			// 例8.2 (2)、设计一个将邻接表转换为邻接矩阵的算法
			void ListToMat(AdjGraph* G, MatGraph& g) {
				ArcNode* p;
				g.n = G->n;
				g.e = G->e;
				for (int i = 0; i < g.n; ++i) {
					for (int j = 0; j < g.n; ++j) {
						g.edges[i][j] = i == j ? 0 : INF;    // 不连通权值即为 ∞
					}
				}
				// 扫描所有的单链表
				for (int i = 0; i < G->n; ++i) {
					p = G->adjList[i].firstArc;
					while (p != NULL) {
						// 边的信息
						g.edges[i][p->adjvexNo] = p->weight;
						p = p->nextArc;
					}
				}

			}

		} // END namespace _8_2_3 图基本运算算法设计

		// 8.2.4 其他存储方法
		// 十字链表（orthogonal list） 和 邻接多重表（adjacency multi-list）

	} // namespace _8_2 图的存储结构和基本运算算法

	// 8.3 图的遍历
	// 为了避免同一个顶点被重复访问，用一个visited数组存储是否被访问过的信息
	// 深度优先遍历（Depth First Search，DFS）
	// 广度优先遍历（Breadth First Search，BFS）
	// 最后修改：2019-11-19
	namespace _8_3 {
		using dst::_8_2::_8_2_2::AdjGraph;    // 引用邻接表存储结构
		using dst::_8_2::_8_2_2::MAXV;
		using dst::_8_2::_8_2_2::ArcNode;

		// 基础算法，请勿显式调用
		struct _8_3_Base {
			// 深度优先遍历，基本算法，若显式调用请查阅文档
			static void base_DFS(AdjGraph* G, int v, bool* visited) {
				ArcNode* p;
				visited[v] = true;
				printf("%d ", v);    // 输出被访问的顶点编号
				p = G->adjList[v].firstArc;    // p指向顶点v的第一个邻接结点
				while (p != NULL) {
					// 若邻接结点未被访问，访问之
					if (visited[p->adjvexNo] == false) {
						base_DFS(G, p->adjvexNo, visited);
					}
					p = p->nextArc;    // p指向v的下一个邻接点
				}
			}

			// 广度优先遍历，基本算法，若显式调用请查阅文档
			static void base_BFS(AdjGraph* G, int v, bool* visited) {
				int queue[MAXV];    // 存放结点编号的队列，实现基于环形队列
				int front = 0, rear = 0;
				int frontNode;
				ArcNode* p;
				// 输出被访问的开始顶点的编号
				printf("%d ", v);
				visited[v] = true;
				queue[rear++] = v;    // 进队操作
				// 队不为空循环
				while (front != rear) {
					frontNode = queue[front++];    // 出队一个顶点
					p = G->adjList[frontNode].firstArc;
					// 查找p的所有邻接顶点
					while (p != NULL) {
						if (visited[p->adjvexNo] == false) {
							printf("%d ", p->adjvexNo);
							visited[p->adjvexNo] = true;    // 设为已访问
							queue[rear++] = p->adjvexNo;    // 进队 
						}
						p = p->nextArc;
					}
				}
			}

		};

		// 深度优先遍历：从初始点v出发，首先访问初始点v，然后选择一个与顶点v相邻且没有被访问过的顶点w
		// 再以w为初始点进行深度优先遍历，直到顶点v的所有都被访问过为止
		void DFS(AdjGraph* G, int v) {
			bool* visited = new bool[MAXV];
			memset(visited, false, MAXV * sizeof(bool));
			_8_3_Base::base_DFS(G, v, visited);
			printf("\n");
		}

		// 广度优先遍历：首先访问初始顶点v，接着访问顶点v的所有未被访问的邻接点v1，v2...，
		// 然后按照次序依次广度优先遍历v1，v2...，直到v的所有邻接点都被遍历过
		void BFS(AdjGraph* G, int v) {
			bool* visited = new bool[MAXV];    // 是否访问标志数组
			memset(visited, false, MAXV * sizeof(bool));
			_8_3_Base::base_BFS(G, v, visited);
			printf("\n");
		}

		// 非连通图的遍历，深度优先遍历
		void DFS_Non_Connected(AdjGraph* G) {
			bool* visited = new bool[MAXV];
			memset(visited, false, MAXV * sizeof(bool));
			for (int i = 0; i < G->n; ++i) {
				if (visited[i] == false) {
					printf("[ ");
					_8_3_Base::base_DFS(G, i, visited);
					printf("] ");
				}
			}
			printf("\n");
		}

		// 非连通图的遍历，广度优先遍历
		void BFS_Non_Connected(AdjGraph* G) {
			bool* visited = new bool[MAXV];
			memset(visited, false, MAXV * sizeof(bool));
			for (int i = 0; i < G->n; ++i) {
				if (visited[i] == false) {
					printf("[ ");
					_8_3_Base::base_BFS(G, i, visited);
					printf("] ");
				}
			}
			printf("\n");
		}

		// 例8.3 假设图G采用邻接表存储，判断G是否连通
		bool Connect(AdjGraph* G) {
			bool* visited = new bool[MAXV];
			memset(visited, false, MAXV * sizeof(bool));
			_8_3_Base::base_DFS(G, 0, visited);     // 对图进行遍历，此处选DFS，然后根据visited数组是否已经全部访问，判断图是否连通
			for (int i = 0; i < G->n; ++i) {
				if (visited[i] == false) {
					return false;
				}
			}
			return true;
		}

		/// 8.3.5 图的遍历算法的应用

		// 8.3.5.1 基于深度优先遍历算法的应用
		// 最后修改：2019-11-14
		namespace _8_3_5_1 {
			// 为消除全局visited数组变量，使用*&传递visited数组
			// 为所有需要全局visited数组算法提供基本算法 base_xxx( , ,..., visited)

			// 基础算法，请勿显式调用
			struct _8_3_5_1_Base {
				// 例8.4 base
				static void base_8_4(AdjGraph* G, int u, int v, bool& has, bool* visited) {
					visited[u] = true;    // u已访问
					if (u == v) {
						has = true;    // 找到了一条路径
						return;
					}
					int w;    // 表示顶点u的相邻顶点
					ArcNode* p = G->adjList[u].firstArc;
					while (p != NULL) {
						w = p->adjvexNo;    // w为邻接点的编号
						if (visited[w] == false) {
							base_8_4(G, w, v, has, visited);
						}
						p = p->nextArc;
					}
				}

				// 例8.5 base
				// path不是用的引用，每次递归的所用的函数的path都不同，d表示路径中顶点的个数
				static void base_8_5(AdjGraph* G, int u, int v, int path[], int d, bool* visited) {
					visited[u] = true;
					path[d++] = u;    // 路径长度增1，顶点u加入到路径中
					if (u == v) {
						// 找到路径，输出
						for (int i = 0; i < d - 1; ++i) {
							printf("%d => ", path[i]);
						}
						printf("%d\n", path[d - 1]);
						return;
					}
					int w;
					ArcNode* p = G->adjList[u].firstArc;
					// 依次遍历u的邻接点
					while (p != NULL) {
						w = p->adjvexNo;
						if (visited[w] == false) {
							base_8_5(G, w, v, path, d, visited);
						}
						p = p->nextArc;
					}
				}

				// 例8.6 base
				static void base_8_6(AdjGraph* G, int u, int v, int path[], int d, bool* visited) {
					visited[u] = true;
					path[d++] = u;    // 路径长度增1，顶点u加入到路径中
					if (u == v && d > 0) {
						// 找到路径，输出
						for (int i = 0; i < d - 1; ++i) {
							printf("%d => ", path[i]);
						}
						printf("%d\n", path[d - 1]);
					}
					int w;
					ArcNode* p = G->adjList[u].firstArc;
					// 依次遍历u的邻接点
					while (p != NULL) {
						w = p->adjvexNo;
						if (visited[w] == false) {
							base_8_6(G, w, v, path, d, visited);
						}
						p = p->nextArc;
					}
					visited[u] = false;
					// 调用结束后退栈，恢复至上一状态，因调用者中的 d 天然比被调用函数中的 d 小1，故不用d--
				}

				// 例8.7 base
				static void base_8_7(AdjGraph* G, int u, int v, int l, int path[], int d, bool* visited) {
					visited[u] = true;
					path[d++] = u;    // 路径长度增1，顶点u加入到路径中
					if (u == v && d - 1 == l) {
						// 找到路径，输出，其中d为路径中顶点的个数，路径长度为d - 1
						for (int i = 0; i < d - 1; ++i) {
							printf("%d => ", path[i]);
						}
						printf("%d\n", path[d - 1]);
					}
					int w;
					ArcNode* p = G->adjList[u].firstArc;
					// 依次遍历u的邻接点
					while (p != NULL) {
						w = p->adjvexNo;
						if (visited[w] == false) {
							base_8_7(G, w, v, l, path, d, visited);
						}
						p = p->nextArc;
					}
					visited[u] = false;    // 恢复环境，使该顶点可在不同路径中重复使用
					// 调用结束后退栈，恢复至上一状态，因调用者中的 d 天然比被调用函数中的 d 小1，故不用d--
				}

				// 例8.8 base 根据教材，此处命名为 DFSPath(...)
				static void DFSPath(AdjGraph* G, int u, int v, int path[], int d, bool* visited) {
					visited[u] = true;
					path[d++] = u;
					ArcNode* p = G->adjList[u].firstArc;
					int w;
					while (p != NULL) {
						w = p->adjvexNo;
						// 判断能够构成回路
						if (w == v && d >= 3) {
							for (int i = 0; i < d; ++i) {
								printf("%d => ", path[i]);
							}
							printf("%d\n", v);
						}
						if (visited[w] == false) {
							DFSPath(G, w, v, path, d, visited);
						}
						p = p->nextArc;    // u的下一个邻接顶点
					}
					visited[u] = false;    // 恢复环境，使该顶点在其他路径中可重复使用
					// 调用结束后退栈，恢复至上一状态，因调用者中的 d 天然比被调用函数中的 d 小1，故不用d--
				}
			};

			// 例8.4 采用邻接表存储的图G，判断G中从顶点u到v是否存在简单路径
			// 采用深度优先遍历，判断当前顶点是否为终点，若是则置true并返回
			// has 表示 u 到 v 是否有路径，初始值为false
			void ExistPath(AdjGraph* G, int u, int v, bool& has) {
				bool* visited = new bool[MAXV];    // 是否访问标志数组
				memset(visited, false, MAXV * sizeof(bool));
				_8_3_5_1_Base::base_8_4(G, u, v, has, visited);
			}

			// 例8.5 采用邻接表的图G，输出一条从顶点 u 到 v 的简单路径（假设存在）
			// 采用深度优先遍历，判断当前顶点是否为终点，若是则输出路径并结束
			void FindAPath(AdjGraph* G, int u, int v) {
				bool* visited = new bool[MAXV];    // 是否访问标志数组
				memset(visited, false, MAXV * sizeof(bool));
				int path[MAXV];
				_8_3_5_1_Base::base_8_5(G, u, v, path, 0, visited);
			}

			// 例8.6 采用邻接表的图G，假设从 u 到 v 存在路径，输出所有简单路径
			// 思路同例8.5，只不过找到终点输出路径后，不结束算法，而是继续回溯寻找
			// 因此要在函数的最后恢复环境使visited[u] = false
			void FindAllPath(AdjGraph* G, int u, int v) {
				bool* visited = new bool[MAXV];    // 是否访问标志数组
				memset(visited, false, MAXV * sizeof(bool));
				int path[MAXV];
				_8_3_5_1_Base::base_8_6(G, u, v, path, 0, visited);
			}

			// 例8.7 采用邻接表的图G，假设从 u 到 v 存在路径，输出所有长度为 l 的简单路径
			void PathLenAll(AdjGraph* G, int u, int v, int l) {
				bool* visited = new bool[MAXV];    // 是否访问标志数组
				memset(visited, false, MAXV * sizeof(bool));
				int path[MAXV];
				_8_3_5_1_Base::base_8_7(G, u, v, l, path, 0, visited);
			}

			// 例8.8 采用邻接表存储的有向图G，求图中通过某顶点 k 的所有简单回路（若存在）
			// 简单回路即路径上顶点不重复，且第一个顶点与最后一个顶点相同的回路
			// 利用回溯的深度优先搜索从u开始，若其相邻顶点w等于v，且路径长度大于1（路径上顶点数多于或等于3），则构成回路
			// 经过某顶点k，则可以转换为求从 k 到 k 的路径
			void FindCyclePath(AdjGraph* G, int k) {
				bool* visited = new bool[MAXV];    // 是否访问标志数组
				memset(visited, false, MAXV * sizeof(bool));
				int path[MAXV];
				_8_3_5_1_Base::DFSPath(G, k, k, path, 0, visited);
			}

		} // END namespace _8_3_5_1 基于深度优先遍历算法的应用

		// 8.5.3.2 基于广度优先遍历算法的应用
		// 最后修改：2019-11-19
		namespace _8_3_5_2 {
			// 例8.9 所用的队列结构
			typedef struct {
				int data;    // 顶点编号
				int parent;    // 前一个顶点在队列中的位置
			} QUEUE;    // 非环形队列类型

			// 例8.9 采用邻接表存储的图G，求不带权的无向连通图G中从顶点u到v的一条最短路径
			// 广度优先遍历的访问过程是一层一层的，采用非环形队列来输出路径（逆序）
			void ShortPath(AdjGraph* G, int u, int v) {
				QUEUE qu[MAXV];    // 非环形队列
				int front = -1, rear = 0;
				bool* visited = new bool[MAXV];    // 标识是否访问过
				memset(visited, false, MAXV * sizeof(bool));
				qu[rear].data = u;    // 顶点u进队
				qu[rear++].parent = -1;
				visited[u] = true;
				ArcNode* p;
				int top;
				// 队不为空，循环
				while (front != rear) {
					top = qu[++front].data;
					if (top == v) {
						// 找到v时输出
						int i = front;
						while (qu[i].parent != -1) {
							printf("%d ", qu[i].data);
							i = qu[i].parent;
						}
						printf("%d\n", qu[i].data);
						return;
					}
					p = G->adjList[top].firstArc;
					// 遍历队首结点的所有相邻结点
					while (p != NULL) {
						if (visited[p->adjvexNo] == false) {
							visited[p->adjvexNo] = true;
							qu[rear].data = p->adjvexNo;
							qu[rear++].parent = front;
						}
						p = p->nextArc;
					}
				}
			}

			// 例8.10 采用邻接表存储的图G，求不带权的无向连通图G中举例顶点v最远的一个顶点，返回其顶点编号
			// 采用广度优先遍历，则最后遍历到的一个顶点即为最远的一个，因不需要输出路径，故可以采用环形队列
			int MaxDist(AdjGraph* G, int v) {
				int Qu[MAXV];    // 用一维数组表示环形队列
				int front = 0, rear = 0;
				bool* visited = new bool[MAXV];
				memset(visited, false, MAXV * sizeof(bool));
				Qu[rear] = v;    // 顶点v进队
				rear = (rear + 1) % MAXV;
				visited[v] = true;
				ArcNode* p;
				int k, j;    // k表示队首结点，j表示其相邻结点
				while (front != rear) {
					k = Qu[front];    //  顶点k出队
					front = (front + 1) % MAXV;
					p = G->adjList[k].firstArc;
					while (p != NULL) {
						j = p->adjvexNo;
						if (visited[j] == false) {
							visited[j] = true;
							Qu[rear] = j;    // 顶点j置为访问，且进队
							rear = (rear + 1) % MAXV;
						}
						p = p->nextArc;
					}
				}
				return k;    // 由广度优先遍历所遍历的最后一个结点即为距离v最远的结点
			}

		} // END namespace _8_3_5_2 基于广度优先遍历算法的应用

		// 8.3.5.3 用图遍历方法求解迷宫问题

		// 8.3.5.4 深度优先遍历和广度优先遍历求解路径问题上的差异

	} // END namespace _8_3 图的遍历

	// 8.4 生成树（spanning tree）和最小生成树（minimal spanning tree）
	// 无向图
	// 最后修改：2019-11-21
	namespace _8_4 {
		// 8.4.1 生成树的概念
		// 一个连通图的 生成树 是一个含有 全部顶点 和 (n-1)个边 的极小连通子图（连通无回路）
		// 生成树边上权值之和最小的为最小生成树（minimal spanning tree）（不一定唯一）
		// 最小生成树的准则有以下3条：
		// (1)、必须使用图中的边来构造最小生成树
		// (2)、必须使用且仅使用（n-1）条边来连接图中的n个顶点
		// (3)、不能使用产生回路的边
		// 求图的最小生成树的经典算法为 普里姆算法（Prim） 和 克鲁斯卡尔算法（Kruskal）

		// 8.4.2 无向图的连通分量和生成树
		// 设 G = (V,E) 为连通图，则从图中任一点出发遍历图时必定将 E(G) 分成两个集合 T 和 B，
		// 其中 T 是遍历过程中走过的边的集合，B是剩余边的集合：T ∩ B = 空集，T ∪ B = E(G)
		// 显然，G' = (V, T) 是 G 的极小连通子图，即 G' 是 G 的一棵生成树
		// 由深度优先遍历得到的生成树称为深度优先生成树（DFS tree），由广度优先遍历得到的生成树称为广度优先生成树（BFS tree）
		// 对于非连通图，每个连通分量中的顶点集和遍历时走过的边一起构成一个生成树，各个连通分量的生成树组成生成森林（spanning forest）

		// 8.4.3 普里姆（Prim）算法
		// 最后修改：2019-11-21
		namespace _8_4_3 {
			// 普里姆算法（无向连通图），采用邻接矩阵（由于需要频繁访问权值）
			// O(n^2)，执行时间与图的边数e无关，适合 稠密图
			// 由 G 构造从起始点 v 出发的最小生成树 T 的步骤如下：
			// (1)、初始化 U = { v }，以 v 到其他顶点的所有 邻接的边 作为 U <--> V-U 的侯选边
			// (2)、重复以下步骤 n-1 此，使得其他的 n-1 个顶点被加入到 U 中
			//  ①、从 侯选边 中挑选出权值最小的边加入到 TE，设该边所连的在 V-U 中的顶点是 k，将 k 加入到 U 中；
			//  ②、调整剩余顶点集 V-U 中每个顶点 j <--> U 的侯选边，若 (k,j) 边的权小于原来和顶点 j 关联的侯选边，则用 (k,j) 作为 j 的侯选边

			/* 普里姆算法是一种增量的构造性算法，根据最小权的侯选边从 剩余 V 中选择顶点加入到 U 中
			假设 G = (V,E) 为具有 n 个顶点的带权连通图，T = (U,TE) 是 G 的最小生成树
			U：生成树的顶点集，TE：生成树的边集，V-U：图中剩余顶点集，侯选边：为了求 U <--> V-U 权值最小的边
			Ⅰ、由于是无向图，故可以只需考虑 V-U 剩余顶点的集合，对于 V-U 中编号为 j 的顶点，用两个数组
			closestNode[j]：表示距离 顶点j 的最近顶点编号，lowestWeight[j]：表示 顶点j 所有相邻边的 最小权值
			故 顶点j 的最小边为 (closestNode[j], j)，对应的权为 lowestWeight[j]
			Ⅱ、为确顶一个 顶点i 是属于 U 集合 还是 V-U集合，规定：
			用 lowestWeight[i] = 0 表示 顶点i 属于 生成树顶点集合U，lowestWeight[i] != 0 表示 顶点i 属于 剩余顶点集合V-U
			Ⅲ、初始时，U 中只有一个顶点 v，对于其他所有顶点 i，这时 (v,i) 就是 顶点i 到 U 的最小边，置 lowestWeight[i] = g.edges[v][i]，closestNode[i] = v
			扫描剩下的 V-U集合 中的所有顶点，根据最小的 lowestWeight[k] 求出顶点 k，那么 (closestNode[k], k) 即最小边，输出之（访问操作）
			将 k 加入到 生成树顶点集U 中，即置 lowestWeight[k] = 0
			调整，即修改在 V-U集合 中的所有（需要修改的）顶点 j <--> U 的侯选边，因为 U 的变化仅仅时因为多了刚刚加入的 k，
			所以只需要比较 lowestWeight[j] 与 g.edges[k][j]，判断 最小权lowestWeight[j] 和 最近顶点closestNode[j] 是否需要修改
			*/

			// 引用图的邻接矩阵存储
			using dst::_8_2::_8_2_1::MatGraph;
			using dst::_8_2::_8_2_1::INF;
			using dst::_8_2::_8_2_1::MAXV;

			void Prim_text(MatGraph g, int v) {
				int lowcost[MAXV];
				int MIN;
				int closest[MAXV], i, j, k;
				for (int i = 0; i < g.n; i++) {
					lowcost[i] = g.edges[v][i];
					closest[i] = v;
				}
				for (i = 1; i < g.n; i++) {
					MIN = INF;
					for (j = 0; j < g.n; j++)
						if (lowcost[j] != 0 && lowcost[j] < MIN) {
							MIN = lowcost[j];
							k = j;
						}
					printf(" 边(%d,%d)权为：%d\n", closest[k], k, MIN);
					lowcost[k] = 0;
					for (j = 0; j < g.n; j++) {
						if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j]) {
							lowcost[j] = g.edges[k][j];
							closest[j] = k;
						}
					}
				}
			}

			// 普里姆算法（无向连通图），采用邻接矩阵（由于需要频繁访问权值）
			// O(n^2)，执行时间与图的边数e无关，适用于 稠密图
			// 由 G 构造从起始点 v 出发的最小生成树 T 的步骤如下：
			// (1)、初始化 U = { v }，以 v 到其他顶点的所有 邻接的边 作为 U <--> V-U 的侯选边
			// (2)、重复以下步骤 n-1 此，使得其他的 n-1 个顶点被加入到 U 中
			//  ①、从 侯选边 中挑选出权值最小的边加入到 TE，设该边所连的在 V-U 中的顶点是 k，将 k 加入到 U 中；
			//  ②、调整剩余顶点集 V-U 中每个顶点 j <--> U 的侯选边，若 (k,j) 边的权小于原来和顶点 j 关联的侯选边，则用 (k,j) 作为 j 的侯选边
			void Prim(const MatGraph& g, int v) {
				int closestNode[MAXV];    // 顶点的最近相邻顶点编号
				int lowestWeight[MAXV];    // 顶点的最小权值
				int minWeight;    // 最小权值
				int k;    // 当前处理中的最近顶点
				// 为 lowestWeight 和 closestNode 数组置初值
				for (int i = 0; i < g.n; ++i) {
					lowestWeight[i] = g.edges[v][i];
					closestNode[i] = v;
				}
				// n-1 次循环用于将剩下的 n-1 个顶点加入到 生成树顶点集U 中
				for (int iter = 1; iter < g.n; ++iter) {
					minWeight = INF;
					// 在 V-U 中找出离 U 最近的顶点 k
					for (int i = 0; i < g.n; ++i) {
						if (lowestWeight[i] != 0 && minWeight > lowestWeight[i]) {
							minWeight = lowestWeight[i];
							k = i;
						}
					}
					printf("[ (%d,%d) : %d ]\n", closestNode[k], k, minWeight);    // 输出最小生成树的一条边的信息
					lowestWeight[k] = 0;    // 标记 k 已经加入到 U 当中
					// 调整剩下的 V-U 中顶点的 侯选边 和 最近相邻顶点
					for (int j = 0; j < g.n; ++j) {
						if (lowestWeight[j] != 0 && lowestWeight[j] > g.edges[k][j]) {
							lowestWeight[j] = g.edges[k][j];
							closestNode[j] = k;
						}
					}
				}
			}

		} // END namespace _8_4_3 普利姆算法

		// 8.4.4 克鲁斯卡尔（Kruskal）算法
		// 最后修改：2019-11-22
		namespace _8_4_4 {
			// 克鲁斯卡尔算法，采用邻接矩阵（需要频繁的访问一条边的权值）
			// 由 G 构造最小生成树 T 的步骤如下：
			// (1)、置 U 的初值为 V，（即包含有 G 中的全部顶点），TE 的初值为空集（即 生成树T 中的每个顶点都构成一个分量）
			// (2)、将 图G 中的边按权值从小到大的顺序依次选取，若选取的边未使 生成树T 形成回路，则加入 TE，否则舍弃，直到 TE 中包含 n-1 条边为止

			/* 克鲁斯卡尔算法是一种按权值的递增次序选择合适的边来构造最小生成树的方法
			假设 G = (V,E) 为具有 n 个顶点的带权连通图，T = (U,TE) 是 G 的最小生成树
			U：生成树的顶点集，TE：生成树的边集
			Ⅰ、如何判断选取的一条边 (i,j) 加入到 T 中是否出现回路，可以通过判断顶点 i、j 是否属于同一个连通分量的方法来解决
			设置一个辅组数组 vest[0...n-1]，用 vest[i] 表示一个顶点 i 所在的连通分量的编号
			初始时，每个顶点构成一个连通分量，令 vest[i] = i（所有顶点的连通分量的编号等于该顶点的编号）
			若选中的边 (i,j) 的 vest[i] != vest[j] 时表示不会形成回路，可以加入到生成树 T 中
			然后将这两个顶点所在的连通分量中所有顶点的连通分量编号改为相同（vest[i] 或 vest[j]均可）
			*/

			// 用一个数组 E[] 存放 图G 中的所有边，要求他们是按权值从小到大的顺序排序
			typedef struct {
				int startNo;    // 边的起始节点编号
				int endNo;    // 边的终止顶点编号
				int weight;    // 边的权值
			} Edge;    // 边类型

			// dependence 依赖
			// 最后修改：2019-11-22
			namespace dep {
				// 直接插入排序，键值类型为边的权值
				void InsertSort(Edge E[], int n) {
					Edge tmp;
					int j;    // 用来从后向前遍历 有序区R[0...i-1]
					// n-1 趟
					for (int i = 1; i < n; ++i) {
						// 若 i 比 i - 1 位置小，即不符合递增，应对其排序
						if (E[i].weight < E[i - 1].weight) {
							tmp = E[i];
							j = i - 1;
							// 寻找 R[i] 的插入位置
							do {
								E[j + 1] = E[j];    // 将关键字大于 R[i].key 的记录后移
								--j;
							} while (j >= 0 && E[j].weight > tmp.weight);
							E[j + 1] = tmp;    // 在 j+1 处插入 R[i]
						}
					}
				}

				// 为了方便，采用顺序方法存储森林，其中结点的类型声明如下：
				typedef struct {
					int data;    // 结点对应元素的编号
					int rank;    // 结点对应的秩
					int parent;    // 结点对应双亲在结点数组中的下标
				} UFSTree;

				// 并查集树的初始化
				// 建立一个存放并查集树的数组t，每个结点对应一个元素，data值即为该元素的编号，rank值初始值为0，parent值设置为自己
				void MAKE_SET(UFSTree t[], int n) {
					for (int i = 0; i < n; ++i) {
						t[i].data = i;    // 数据为该元素的编号
						t[i].rank = 0;    // 秩初始化为0
						t[i].parent = i;    // 双亲初始化指向自己
					}
				}

				// 查找一个元素所属的集合
				// 用分离集合树表示一个集合，故就是查找该元素所在的分离集合树，故就是查找分离集合树的代表，即树的根结点
				int FIND_SET(UFSTree t[], int x) {
					return x != t[x].parent ? FIND_SET(t, t[x].parent) : x;    // 双亲不是自己 ? 递归在双亲中找x : 返回x
				}

				// 两个元素各自所属的集合的合并
				// 只需要让具有较小秩的根指向具有较大秩的根；如果两根的秩相等，只需要使其中一个根指向另一个，同时秩增加1
				void UNION(UFSTree t[], int x, int y) {
					x = FIND_SET(t, x);    // 分别查找x和y所在集合代表的编号
					y = FIND_SET(t, y);
					if (t[x].rank > t[y].rank) {
						t[y].parent = x;    // 将较小秩的根结点 y 连接到较大秩的根结点 x
					} else {
						t[x].parent = y;    // x 连接到 y
						if (t[x].rank == t[y].rank) {
							++t[y].rank;    // 若x和y的秩相同，增加已连接到的 y 的秩
						}
					}
				}

				// 堆排序筛法，大根堆
				void sift(Edge E[], int lowIndex, int highIndex) {
					int i = lowIndex, j = 2 * i + 1;    // R[j] 是 R[i] 的左孩子
					Edge tmp = E[i];
					while (j <= highIndex) {
						// 若右孩子关键字较大，把 j 指向右孩子
						if (j < highIndex && E[j].weight < E[j + 1].weight) {
							++j;
						}
						// 此处 j 指向最大孩子，若根结点小于最大孩子，交换之，并修复下一级的堆
						if (tmp.weight < E[j].weight) {
							E[i] = E[j];    // 将 最大孩子R[j] 调整到当前处理的 双亲结点R[i] 的位置上
							i = j;    // 修改 i 和 j 的值，指向下一级，以便继续向下筛选
							j = 2 * i + 1;
						} else {
							break;    // 若根结点大于等于最大孩子，筛选结束
						}
					}
					E[i] = tmp;    // 被筛的结点放到适合的最终位置上
				}

				// 堆排序（递增排序）
				void HeapSort(Edge E[], int n) {
					Edge tmp;
					// 循环建立初始堆，调用 sift 算法 ⌊n/2⌋ 次
					for (int i = n / 2 - 1; i >= 0; sift(E, i--, n - 1));
					// 进行 n-1 趟完成堆排序，每一趟堆中元素个数减1
					for (int i = n - 1; i > 0; --i) {
						// 将最后一个元素与根 R[0] 交换
						tmp = E[0];
						E[0] = E[i];
						E[i] = tmp;
						sift(E, 0, i - 1);    // 对 R[0...n-2] 进行筛选，得到 i-1 个结点的堆
					}
				}

			} // END namespace dep 依赖库

			// 引用图的邻接矩阵存储
			using dst::_8_2::_8_2_1::MatGraph;
			using dst::_8_2::_8_2_1::INF;
			using dst::_8_2::_8_2_1::MAXV;
			const int MaxEdgeSize = MAXV * MAXV;    // 最大边的个数

			// 克鲁斯卡尔算法（标准版），采用邻接矩阵（需要频繁的访问一条边的权值）
			// O(e^2)，适合于 稀疏图
			// 由 G 构造最小生成树 T 的步骤如下：
			// (1)、置 U 的初值为 V，（即包含有 G 中的全部顶点），TE 的初值为空集（即 生成树T 中的每个顶点都构成一个分量）
			// (2)、将 图G 中的边按权值从小到大的顺序依次选取，若选取的边未使 生成树T 形成回路，则加入 TE，否则舍弃，直到 TE 中包含 n-1 条边为止
			void Kruskal_standard(const MatGraph& g) {
				int edgeNo = 0;    // 可以表示当前处理的边在边数组中的索引，也表示已经加入到TE中的边的个数
				int startNo, endNo, startSetNo, endSetNo, iter = 0;    // 初始、终止顶点编号，初始、终止顶点所在连通分量编号，遍历用变量
				int vest[MAXV];    // vest 表示顶点所在连通分量的编号
				Edge E[MaxEdgeSize];    // 边的数组

				// 初始化 vest 数组
				for (int i = 0; i < g.n; ++i) {
					vest[i] = i;
				}
				// 初始化边的数组 E[]
				for (int i = 0; i < g.n; ++i) {
					for (int j = 0; j <= i; ++j) {
						if (g.edges[i][j] != 0 && g.edges[i][j] < INF) {
							E[edgeNo].weight = g.edges[i][j];
							E[edgeNo].startNo = i;
							E[edgeNo].endNo = j;
							++edgeNo;
						}
					}
				}
				dep::InsertSort(E, g.e);
				edgeNo = 0;    // 初始 TE 中边数为 0 个，每加入一个增1，直到 n-1 条边
				iter = 0;
				while (edgeNo < g.n - 1) {
					startNo = E[iter].startNo;    // 取 iter 边的信息
					endNo = E[iter].endNo;
					startSetNo = vest[startNo];
					endSetNo = vest[endNo];
					// 如果两个顶点属于不同的连通分量，表示他们的边可以加入到 TE 中
					if (startSetNo != endSetNo) {
						printf("[ (%d,%d) : %d ]\n", startNo, endNo, E[iter].weight);    // 输出最小生成树的一条边的信息
						++edgeNo;
						// 将两个顶点所在的集合合并，即统一编号
						for (int i = 0; i < g.n; ++i) {
							if (vest[i] == endSetNo) {
								vest[i] = startSetNo;    // 将编号为 endSetNo 的改为 startSetNo
							}
						}
					}
					++iter;    // 扫描下一条边
				}
			}

			// 克鲁斯卡尔算法（改进版），采用邻接矩阵（需要频繁的访问一条边的权值）
			// 优化：采用并查集进行连通分量的合并，采用堆排序代替直接插入排序初始化边的数组
			// O(elog2(n))，适合于 稀疏图
			// 由 G 构造最小生成树 T 的步骤如下：
			// (1)、置 U 的初值为 V，（即包含有 G 中的全部顶点），TE 的初值为空集（即 生成树T 中的每个顶点都构成一个分量）
			// (2)、将 图G 中的边按权值从小到大的顺序依次选取，若选取的边未使 生成树T 形成回路，则加入 TE，否则舍弃，直到 TE 中包含 n-1 条边为止
			void Kruskal(const MatGraph& g) {
				dep::UFSTree t[MaxEdgeSize];    // 并查集，用于判断某顶点所在的集合
				Edge E[MaxEdgeSize];    // 边的数组
				int edgeNo = 0;
				int startNo, endNo, startSetNo, endSetNo, iter = 0;
				// 初始化边的数组
				for (int i = 0; i < g.n; ++i) {
					for (int j = 0; j <= i; ++j) {
						if (i != j && g.edges[i][j] < INF) {
							E[edgeNo].weight = g.edges[i][j];
							E[edgeNo].startNo = i;
							E[edgeNo].endNo = j;
							++edgeNo;
						}
					}
				}

				// 并查集的元素类型为 int 型（从0开始），而图中顶点的编号也是从0开始的int型（两者一一对应，不需额外的映射）
				// 故并查集中的元素为顶点的编号，而顶点的编号标识唯一的顶点
				dep::MAKE_SET(t, g.n);    // 初始化并查集
				dep::HeapSort(E, g.e);    // 对边的数组递增排序

				edgeNo = 0;
				// 构造剩下的 n-1 条边
				while (edgeNo < g.n - 1) {
					startNo = E[iter].startNo;
					endNo = E[iter].endNo;
					startSetNo = dep::FIND_SET(t, startNo);
					endSetNo = dep::FIND_SET(t, endNo);
					if (startSetNo != endSetNo) {
						printf("[ (%d,%d) : %d ]\n", startNo, endNo, E[iter].weight);    // 输出最小生成树的一条边的信息
						++edgeNo;
						dep::UNION(t, startNo, endNo);
					}
					++iter;
				}
			}

		} // END namespace _8_4_4 克鲁斯卡尔算法

		// test.c for 8.4
		namespace _8_4_test {
			void test() {
				int** mat = new int*[7];
				for (int i = 0; i < 7; ++i) {
					mat[i] = new int[7];
					for (int j = 0; j < 7; ++j) {
						mat[i][j] = i == j ? 0 : _8_2::_8_2_1::INF;
					}
				}
				mat[0][1] = mat[1][0] = 28;
				mat[1][2] = mat[2][1] = 16;
				mat[2][3] = mat[3][2] = 12;
				mat[1][6] = mat[6][1] = 14;
				mat[3][6] = mat[6][3] = 18;
				mat[6][4] = mat[4][6] = 24;
				mat[3][4] = mat[4][3] = 22;
				mat[4][5] = mat[5][4] = 25;
				mat[0][5] = mat[5][0] = 10;

				_8_2::_8_2_2::AdjGraph* adjG;
				_8_2::_8_2_3::CreateAdj(adjG, mat, 7, 9);
				printf("Graph:\n");
				_8_2::_8_2_3::DispAdj(adjG);

				_8_2::_8_2_1::MatGraph g;
				_8_2::_8_2_3::ListToMat(adjG, g);

				printf("Prim(g, 0):\n");
				_8_4_3::Prim(g, 0);

				printf("Kruskal_standard(g):\n");
				_8_4_4::Kruskal_standard(g);

				printf("Kruskal(g):\n");
				_8_4_4::Kruskal(g);

				_8_2::_8_2_3::DestroyAdj(adjG);
			}

		} // END namespace _8_4_test

	} // END namespace _8_4 生成树和最小生成树

	// 8.5 最短路径（有向图）
	// 最后修改：2019-11-26
	namespace _8_5 {
		// 8.5.1 路径的概念
		// 路径长度：把一条路径上所经边的权之和定义为该路径的路径长度
		// 最短路径：从源点到终点的路径可能不止一条路径，把路径长度最小的那条路径称为最短路径，其路径长度（权之和）称为最短路径长度
		// 求图的最短路径问题有两个方面：某一顶点到其余各顶点的最短路径 和 求图中每一对顶点之间的最短路径

		// 8.5.2 从一个顶点到其余各顶点的最短路径
		// 最后修改：2019-11-23
		namespace _8_5_2 {
			// 给定一个带权有向图 G 与源点 v，求从源点 v 到 G 中其他顶点的最短路径，并限定各边上的权值大于0
			// 狄克斯特拉（Dijkstra）算法基本思想如下：
			// 设 G = (V,E) 是一个带权有向图，集合 V 分为两部分：S（已求出最短路径的顶点集合，初始时只有一个源点），U（其余未确定最短路径的顶点集合）
			// 按路径长度的递增次序把 U 中的顶点 u 加入到 S 中，每求得一条最短路径 v, ...,u，就将顶点 u 加入到集合 S 中，直到全部顶点都加入到S
			// Dijkstra 算法（采用图的邻接矩阵存储方法，需要频繁访问权值）的具体步骤如下：
			// (1)、初始时 S 只包含源点，即 S = { v }，源点 v 到自己的距离为 0，U 包含除源点 v 以外的其他顶点，源点 v 到 U 中任一顶点 i 最短路径的长度为边 <v,i> 上的权
			// (2)、从 U 中选取一个顶点 u，使源点 v --> u 的最短路径长度为最小，然后把顶点 u 加入到 S 中
			// (3)、以顶点 u 为新考虑的中间点，修改源点 v 到 U 中所有顶点的最短路径长度，即路径调整：v --> j = MIN { Cvu + Wuj, Cvj }
			// (4)、重复步骤 (2) 和 (3)，直到 S 中包含所有的顶点

			/* 狄克斯特拉（Dijkstra）算法
			Ⅰ、用一个一维数组 dist[j] 表示从源点 v --> j 的最短路径长度；inS[j] 表示顶点 j 是否在集合 S 中
				preNode[j] 表示 v --> j 最短路径上顶点 j 的前一个顶点编号，没有通路时暂置为-1
			Ⅱ、在执行中，一个顶点一旦加入到 S 中后，其最短路径长度不再改变，故Dijkstra算法不适合含有负权值的带权图求单源最短路劲
			Ⅲ、按顶点进入 S 的先后顺序最短路径长度越来越长
			*/

			// 引用图的邻接矩阵存储
			using dst::_8_2::_8_2_1::MatGraph;
			using dst::_8_2::_8_2_1::INF;
			using dst::_8_2::_8_2_1::MAXV;

			// 输出单源最短路径
			void DisPath(bool inS[], int dist[], int preNode[], int n, int v) {
				int path[MAXV];    // 存储源点 v 到某一顶点 i 的最短路径
				int index;    // 路径中顶点的索引
				int preNodeInPath;
				// 循环输出源点 v 到顶点 i 的最短路径
				for (int i = 0; i < n; ++i) {
					// 当顶点 i 在 S 中（与源点 v 能连通）且 i 不为源点 v 时处理
					if (inS[i] == true && i != v) {
						printf("[ %d =%d=> %d ]: ", v, dist[i], i);
						index = 0;
						path[index] = i;    // 添加终点，逆序
						preNodeInPath = preNode[i];
						if (preNodeInPath == -1) {
							printf("null\n");    // 没有通路，即无路径的情况
						} else {
							while (preNodeInPath != v) {
								path[++index] = preNodeInPath;    // 当路径上前一个点不为起点时，依次添加到 path[]
								preNodeInPath = preNode[preNodeInPath];
							}
							path[++index] = v;    // 添加起点
							while (index > 0) {
								printf("%d --> ", path[index--]);
							}
							printf("%d\n", path[index]);
						}
					}
				}
			}

			// Dijkstra 算法（采用图的邻接矩阵存储方法，需要频繁访问权值）
			// O(n^2)（不考虑路径的输出）
			// (1)、初始时 S 只包含源点，即 S = { v }，源点 v 到自己的距离为 0，U 包含除源点 v 以外的其他顶点，源点 v 到 U 中任一顶点 i 最短路径的长度为边 <v,i> 上的权
			// (2)、从 U 中选取一个顶点 u，使源点 v --> u 的最短路径长度为最小，然后把顶点 u 加入到 S 中
			// (3)、以顶点 u 为新考虑的中间点，修改源点 v 到 U 中所有顶点的最短路径长度，即路径调整：v --> j = MIN { Cvu + Wuj, Cvj }
			// (4)、重复步骤 (2) 和 (3)，直到 S 中包含所有的顶点
			void Dijkstra(const MatGraph& g, int v) {
				bool inS[MAXV];    // 标识顶点 i 是否在集合 S 当中
				int dist[MAXV];    // 表示顶点 i 到源点 v 的最短距离
				int preNode[MAXV];    // 表示 v --> j 最短路径上的 j 的前一个顶点
				int minPathLength, u;    // 当前最短路径长度 和 当前处理的顶点 u

				// 初始化各种信息
				for (int i = 0; i < g.n; ++i) {
					inS[i] = false;
					dist[i] = g.edges[v][i];
					preNode[i] = g.edges[v][i] < INF ? v : -1;    // -1 表示暂时不连通
				}
				inS[v] = true;    // 初始化源点的信息
				//preNode[v] = v;    // different with text: v <==> 0

				// 循环 n-1 次，将剩下的 n-1 各顶点加入到 S 中
				for (int iter = 0; iter < g.n - 1; ++iter) {
					minPathLength = INF;
					for (int i = 0; i < g.n; ++i) {
						// 选取不在 S 中（即在 U 中）且具有最小最短路径长度的顶点 u
						if (inS[i] == false && minPathLength > dist[i]) {
							minPathLength = dist[i];
							u = i;
						}
					}
					inS[u] = true;    // 顶点 u 加入到 S 中
					for (int i = 0; i < g.n; ++i) {
						// 修改不在 S 中（即在 U 中）的顶点的最短路径
						if (inS[i] == false && g.edges[u][i] < INF && dist[u] + g.edges[u][i] < dist[i]) {
							dist[i] = dist[u] + g.edges[u][i];
							preNode[i] = u;
						}
					}
				}

				DisPath(inS, dist, preNode, g.n, v);    // 输出源点到各点的最短路径
			}

		} // END namespace _8_5_2 从一个顶点到其余各顶点的最短路径

		// 8.5.3 每对顶点之间的最短路径
			// 最后修改：2019-11-26
		namespace _8_5_3 {
			// 对于一个各边权值均大于零的有向图，对每一对顶点 i != j，求出顶点 i --> j 之间的最短路径和最短路径长度
			// 可循环 n 次使用狄克斯特拉算法；也可以用弗洛伊德（Floyd）算法：从全局考虑，不用从局部考虑 + 调整
			// 弗洛伊德算法基本思想：
			// 用一个二维数组 A[][] 存放当前顶点之间的最短路径长度，分量 A[i][j] 表示当前 i --> j 的最短路径长度
			// 递推产生一个矩阵序列 A0, A1, ..., A(n-1)， 其中 Ak[i][j] 表示 i --> j 的路径上所经过的顶点编号不大于 k 的最短路径长度

			/*	弗洛伊德算法：
			初始时有 A(-1)[i][j] = g.edges[i][j]；有数学归纳法，若 A(k-1)[i][j] 已求出，
			现在考查顶点 k，求 i --> j 上所有经过的顶点编号不大于 k 的最短路径长度 Ak[i][j]，此时 i --> j 路径有两条：
			即上一次迭代出的不考虑顶点 k 的最短路径长度 A(k-1)[i][j] 和考虑 k 之后的长度 Ak[i][k] + Ak[k][j]，更新 Ak[i][j] 使之最短
			即：Ak[i][j] = MIN { A(k-1)[i][j], Ak[i][k] + Ak[k][j] } : 0 <= k <= n-1
			上式是一个迭代表达式，每迭代一次，i --> j 的最短路径上就多考虑了一个顶点，经过 n 次迭代后所得的 A(n-1)[i][j] 值就是所求最终解
			另外用一个二维数组 preNode[i][j] 来保存当前 i --> j 最短路径上的顶点 j 之前的顶点编号（若考查k，则 Ak[i][j] = A(k-1)[k][j]），用 -1 表示无路径
			*/

			// 引用图的邻接矩阵存储
			using dst::_8_2::_8_2_1::MatGraph;
			using dst::_8_2::_8_2_1::INF;
			using dst::_8_2::_8_2_1::MAXV;

			// 输出最短路径
			void DisPath(const MatGraph& g, int** A, int** preNode) {
				int path[MAXV];    // 存放一条最短路径中的顶点编号（逆向）
				int index;    // 路径中顶点的索引
				int preNodeInPath;
				// 遍历矩阵输出最短路径
				for (int i = 0; i < g.n; ++i) {
					for (int j = 0; j < g.n; ++j) {
						if (A[i][j] < INF && i != j) {
							// 若 i --> j 之间存在路径
							printf("[ %d =%d=> %d ]: ", i, A[i][j], j);
							index = 0;
							path[index] = j;    // 终点
							preNodeInPath = preNode[i][j];    // 最短路径上 j 的前一个顶点
							while (preNodeInPath != -1 && preNodeInPath != i) {
								path[++index] = preNodeInPath;
								preNodeInPath = preNode[i][preNodeInPath];
							}
							path[++index] = i;    // 起点
							for (int k = index; k > 0; printf("%d --> ", path[k--]));
							printf("%d\n", path[0]);
						}
					}
				}
			}

			// 弗洛伊德（Floyd）算法：
			// O(n^3)（不考虑路径输出）
			// 用一个二维数组 A[][] 存放当前顶点之间的最短路径长度，分量 A[i][j] 表示当前 i --> j 的最短路径长度
			// 递推产生一个矩阵序列 A0, A1, ..., A(n-1)， 其中 Ak[i][j] 表示 i --> j 的路径上所经过的顶点编号不大于 k 的最短路径长度
			void Floyd(const MatGraph& g) {
				const int N = g.n;    // 顶点数量（编号为 0...n-1）
				// 数组 A[][] 和 preNode[][]
				int** A = new int*[N];
				int** preNode = new int*[N];
				// 初始化数组信息
				for (int i = 0; i < N; ++i) {
					A[i] = new int[N];
					preNode[i] = new int[N];
					for (int j = 0; j < N; ++j) {
						A[i][j] = g.edges[i][j];
						preNode[i][j] = (i != j && g.edges[i][j] < INF) ? i : -1;    // i --> j 直接有边时 和 无直接边时
					}
				}
				// 依次考查所有顶点 k，迭代矩阵
				for (int k = 0; k < N; ++k) {
					// i j 遍历矩阵
					for (int i = 0; i < N; ++i) {
						for (int j = 0; j < N; ++j) {
							// 考查顶点 k，注意检查溢出
							if (/*A[i][k] / 2 + A[k][j] / 2 < INF*/(A[i][k] < INF && A[k][j] < INF) && A[i][k] + A[k][j] < A[i][j]) {
								A[i][j] = A[i][k] + A[k][j];    // 修改最短路径长度 和 最短路径上前一个顶点
								preNode[i][j] = preNode[k][j];
							}
						}
					}
				}

				DisPath(g, A, preNode);    // 输出最短路径
			}

		} // END namespace _8_5_3 每对顶点之间的最短路径

		// test.c for 8.5
		namespace _8_5_test {
			void test() {
				int** mat = new int*[7];
				for (int i = 0; i < 7; ++i) {
					mat[i] = new int[7];
					for (int j = 0; j < 7; ++j) {
						mat[i][j] = i == j ? 0 : _8_2::_8_2_1::INF;
					}
				}
				mat[0][1] = 4; mat[0][2] = 6; mat[0][3] = 6;
				mat[1][2] = 1; mat[1][4] = 7;
				mat[2][4] = 6; mat[2][5] = 4;
				mat[3][2] = 2; mat[3][5] = 5;
				mat[4][6] = 6;
				mat[5][4] = 1; mat[5][6] = 8;

				_8_2::_8_2_2::AdjGraph* adjG;
				_8_2::_8_2_3::CreateAdj(adjG, mat, 7, 12);
				printf("Graph for Dijkstra:\n");
				_8_2::_8_2_3::DispAdj(adjG);

				_8_2::_8_2_1::MatGraph g;
				_8_2::_8_2_3::ListToMat(adjG, g);

				printf("Dijkstra(g, 0):\n");
				_8_5_2::Dijkstra(g, 0);

				_8_2::_8_2_3::DestroyAdj(adjG);

				int** m = new int*[4];
				for (int i = 0; i < 4; ++i) {
					m[i] = new int[4];
					for (int j = 0; j < 4; ++j) {
						m[i][j] = i == j ? 0 : _8_2::_8_2_1::INF;
					}
				}
				m[0][1] = 5; m[0][3] = 7;
				m[1][2] = 4; m[1][3] = 2;
				m[2][0] = 3; m[2][1] = 3; m[2][3] = 2;
				m[3][2] = 1;

				_8_2::_8_2_2::AdjGraph* adjFG;
				_8_2::_8_2_3::CreateAdj(adjFG, m, 4, 8);
				printf("\nGraph for Floyd:\n");
				_8_2::_8_2_3::DispAdj(adjFG);

				_8_2::_8_2_1::MatGraph fg;
				_8_2::_8_2_3::ListToMat(adjFG, fg);

				printf("Floyd(fg):\n");
				_8_5_3::Floyd(fg);

				_8_2::_8_2_3::DestroyAdj(adjFG);

			}

		} // END namespace _8_5_test

	} // END namespace _8_5 最短路径

	// 8.6 拓扑排序（topological sort）
	// 最后修改：2019-11-26
	namespace _8_6 {
		// 设 G = (V,E) 是一个具有 n 个顶点的有向图，V 中的顶点序列 v1, v2, ..., vn 称为一个拓扑序列（topological sequence）
		// 若 <vi,vj> 是图中的一条边或路径，则在该序列中顶点 vi 必须排在顶点 vj 之前
		// 在一个有向图中找一个拓扑序列的过程称为拓扑排序（topological sort）
		// 用顶点表示活动，用有向边表示活动之间优先关系的有向图称为顶点表示活动的网（activity on vertex newtork，AOV网）

		// 采用邻接表作为存储结构
		using _8_2::_8_2_2::AdjGraph;    // 采用 AdjGraph->adjList[i].info 表示顶点的入度
		using _8_2::_8_2_2::MAXV;
		using _8_2::_8_2_2::ArcNode;

		// 对AOV网进行拓扑排序的方法如下：
		// (1)、从有向图中选择一个没有前驱（即入度为0）的顶点并输出
		// (2)、从图中删去该顶点，并且删除从该顶点出发的全部的有向边（将所有后继顶点的入度减1）
		// (3)、重复上述两步，直到剩余的图中不再存在没有前驱的结点为止
		// 结果有两种：顶点全部输出，部分顶点输出（图中存在回路）（可用于检查图中是否存在回路）
		void TopoSort(AdjGraph* G) {
			int St[MAXV];    // 栈存储入度为零的顶点
			int top = -1;
			int nodeNo;
			ArcNode* p;
			for (int i = 0; i < G->n; G->adjList[i++].info = 0);     // 入度初始值为 0
			// 求所有顶点的入度
			for (int i = 0; i < G->n; ++i) {
				p = G->adjList[i].firstArc;
				while (p != NULL) {
					++G->adjList[p->adjvexNo].info;
					p = p->nextArc;
				}
			}
			// 将入度为零的顶点进栈
			for (int i = 0; i < G->n; ++i) {
				if (G->adjList[i].info == 0) {
					St[++top] = i;
				}
			}
			// 栈不空循环
			while (top > -1) {
				nodeNo = St[top--];    // 出栈一个顶点 nodeNo
				printf("%d", nodeNo);
				p = G->adjList[nodeNo].firstArc;
				while (p != NULL) {
					// 将顶点 nodeNo 的所有出边邻接点的入度减1，若入度为零则进栈
					if ((--G->adjList[p->adjvexNo].info) == 0) {
						St[++top] = p->adjvexNo;
					}
					p = p->nextArc;
				}
				top == -1 ? printf("\n") : printf(" --> ");
			}
		}

		// test.c for _8_6
		namespace _8_6_test {
			void test() {
				int** m = new int*[7];
				for (int i = 0; i < 7; ++i) {
					m[i] = new int[7];
					for (int j = 0; j < 7; ++j) {
						m[i][j] = i == j ? 0 : _8_2::_8_2_1::INF;
					}
				}
				m[0][2] = 1;
				m[1][3] = m[1][6] = m[1][4] = 1;
				m[2][3] = 1;
				m[3][4] = m[3][5] = 1;
				m[6][5] = 1;

				AdjGraph* adjG;
				_8_2::_8_2_3::CreateAdj(adjG, m, 7, 8);
				printf("Graph for topological sort:\n");
				_8_2::_8_2_3::DispAdj(adjG);

				printf("TopoSort(g), a topological sort sequence:\n");
				TopoSort(adjG);

				_8_2::_8_2_3::DestroyAdj(adjG);
			}

		} // END namespace _8_6_test

	} // END namespace _8_6 拓扑排序

	// 8.7 AOE网与关键路径
	// 最后修改：2019-11-28
	namespace _8_7 {
		// 8.7.1 相关概念
		// Ⅰ、用有向无环图（directed acycline graph，DAG）描述工程的预计进度，以顶点表示事件，边e的权c(e)表示完成活动e所需的时间或持续时间
		// 图中入度为0的顶点表示工程的 开始事件，出度为0的顶点表示工程的 结束事件，这样的有向图为 边表示活动的网（activity on egde network，AOE网）
		// 表示工程的AOE网只有一个入度为0的顶点，称为源点（source），若存在多个入度为0的顶点，可加一个虚拟源点，其到原入度为0的点都有一条长度为0的边
		// 出度为0的顶点同理，称为汇点（converge）
		// Ⅱ、在AOE网中，若存在两条首尾相接的边 ai = <v,w> 和 aj = <w,z>，则称活动 ai 是活动 aj 的前驱活动，aj 是 ai 的后继活动
		// 显然，只有当活动 aj 的所有前驱活动都完成后，事件 w 才发生（这里 w 是 边aj 的头），且活动 aj 才开始
		// 当 w 的所有入边表示的事件完成时，事件 w 就发生了，活动 aj 就可以开始了，故称 事件w 为 活动aj 的触发事件
		// Ⅲ、在AOE网中，从源点到汇点的所有路径中具有最大路径长度的路径称为关键路径（critical path），可能存在多条，但他们的长度是相同的
		// 关键路径上的活动称为关键活动（key activity），关键活动不存在富余时间，非关键活动存在富余时间
		// 只要找出AOE网中的所有关键活动也就找到了全部的关键路径
		// Ⅳ、假设 事件x 是源点，事件y 是汇点，并规定事件 x 的发生时间为0，定义图中任一 事件v 的最早（event early）开始时间ve(v) 等于 x到v 的最长路径的长度
		// 即：ve(v) = MAX { c(<x..v>) }，其中 c<x..v> 表示 x ==> v 的路径长度
		// 完成整个工程所需的事件的最少时间等于汇点y的最早开始时间 ve(y)
		// 为不影响工程进度，使 事件v 尽可能早的开始，在 x ==> v 的最长路径上的活动必须一刻不停的进行，一旦触发事件发生，便立即开始；
		// 而不在最长路径上的活动，即使稍微推迟一些时间发生也不影响工程进度
		// 定义在不影响整个工程进度的前提下，事件v 必须开始的时间称为 v 的最迟（event late）开始时间，记作 vl(v)
		// 那么 vl(v) 应等于 整个工程时间 - v到汇点结束的最长路径，即：vl(v) = ve(y) - MAX { c<v..y> }
		// 显然，ve(x) = vl(x) = 0，ve(y) = vl(y)
		// Ⅴ、只要计算出各顶点 ve() 和 vl() 值，就有办法找出所有的关键活动，为便于计算，引入下面两个递推式：
		// 对于 x ===> vi --ai--> wi ===> y，其中 vi 和 wi 为连个相连的事件，ai为其之间的活动
		// ve(x) = 0；ve(w) = MAX { ve(vi) + c(<vi,w>) }（ w != x） 递推式8.4
		// vl(y) = ve(y)；vl(v) = MIN { vl(wi) - c(<v,wi>) }（v != y） 递推式8.5
		// 只要从 源点x 起按照顶点的拓扑序列次序重复运用 递推式8.4，即可求出 各个顶点w 的 ve(w) 值
		// 只要从 汇点y 起按照顶点的拓扑序列的逆序重复运用 递推式8.5，即可求出 各个顶点v 的 vl(v) 值
		// Ⅵ、对于任何 x ==> v --ai--> w ==> y 应有：x --> v 最长路径 + c(<v,w>) <=（早完成于）w的最迟开始时间
		// 即：ve(v) + c(ai) <= vl(w) 式8.3
		// 若上式取等号：ve(v) + c(ai) = vl(w)，表示 w 最迟就应该在 事件v 和 活动ai 完成后开始（不能等，没有富余时间），即活动 ai 为关键活动
		// 用 式8.3 判断各活动是否为关键活动

		/* 8.7.2 求AOE网的关键活动  x ==> v --ai--> w ==> y
		(1)、对于源点 x，置 ve(x) = 0
		(2)、对AOE网进行拓扑排序，如发现回路，工程无法进行，退出
		(3)、按拓扑次序重复用 式8.4 依次求其余各顶点 v 的 ve(v) 值
		(4)、对于汇点 y，置 vl(y) = ve(y)
		(5)、按拓扑次序的逆序重复用 式8.5 依次求其余各顶点 v 的 vl(v) 值（ vl(x) = 0 ）
		(6)、设 e(ai) 表示 活动ai 的最早开始时间，定义为该活动起点的最早开始时间，即 e(ai) = ve(v)
		(7)、设 l(ai) 表示 活动ai 的最迟开始时间，定义为该活动终点的最迟开始时间 前推 该活动所需时间，即 l(ai) = vl(w) - c(ai)
		(8)、设 d(ai) 表示 活动ai 的时间余量（在不增加整个工程完工所需总时间的情况下活动 ai 可以拖延的时间）
			 定义为最迟开始时间 减去 最早开始时间，即 d(ai) = l(ai) - e(ai)
		(9)、当一个活动的时间余量为零时，说明该活动必须立即完成，否则就会拖延完成整个工程的进度，故 d(ai) = 0，即 e(ai) = l(ai) 表示活动 ai 为关键活动
		*/

	} // END namespace _8_7 AOE网与关键路径

} // END namespace dst 数据结构教程

#endif // !DST_8_GRAPH_H