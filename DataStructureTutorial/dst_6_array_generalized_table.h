// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_6_ARRAY_GENERALIZED_TABLE_H
#define DST_6_ARRAY_GENERALIZED_TABLE_H

// 第六章：数组和广义表

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 6.1 数组（array）
	// 最后修改：2019-10-8
	namespace _6_1 {
		// 数组的抽象数据类型描述如下：
		/*
		ADT Array {
			数据对象:
				D = { aj1,j2,...,jd | ji = 1,...,bi, i = 1, 2,...,d }    // 第i维的长度为bi
			数据关系:
				R = { r1, r2,..., rd }
				ri = { <aj1...ji...jd, aj1...(ji+1)...jd> | 1 <= jk <= bk 且 k != i, 1 <= ji <= bi - 1, i = 2,...,d }
			基本运算:
				InitArray(&A);
				DestroyArray(&A);
				Value(A, index1, index2, ..., indexd);
				Assign(A, e, index1, index2, ..., indexd);
		}
		*/

		// 以下公式据采用逻辑序号，Loc表示取地址运算， 每个元素占用 k 各存储单元
		// 物理序号（C/C++中）等于逻辑序号减一，即将 i-1 换成 i 即表示物理序号
		/* 一维数组的存储结构：Loc(ai) = Loc(a1) + (i - 1) * k
		   二维数组(M x N)的按行优先存放：Loc(ai,j) = Loc(a1,1) + [ (i - 1) * n + (j - 1) ] * k
		   二维数组(M x N)的按列优先存放：Loc(ai,j) = Loc(a1,1) + [ (j - 1) * m + (i - 1) } * k
		*/

		// 特殊矩阵的压缩存储，对称矩阵，上下三角矩阵，对角矩阵
		// 用一个一维线性表（一维数组）B[0,1,...,k,...] 存储需要存储的二维矩阵中的元素
		/* 对称矩阵中 k 与 i j 的关系：
		k = i * (i + 1) / 2 + j, i >= j 下三角
		k = j * (j + 1) / 2 + i, i < j 上三角
		*/
		/* 上三角矩阵中 k 与 i j 的关系：
		k = i * (2n - i + 1) / 2 + j - i, i <= j 上三角中
		k = n * (n + 1) / 2, i > j
		*/
		/* 下三角矩阵中 k 与 i j 的关系：
		k = i * (i + 1) / 2 + j, i >= j 下三角
		k = n * (n + 1) / 2, i < j
		*/

	} // END namespace _6_1 数组

	// 6.2 稀疏矩阵（sparse matrix）
	// 非零元素的个数远小于元素总个数的矩阵
	// 元素类型：int
	// 最后修改：2019-10-10
	namespace _6_2 {
		// 稀疏矩阵的压缩，只存储其非零元素
		// 由于其非零元素分布没由规律，故还需存储非零元素的位置信息

		// 6.2.1 稀疏矩阵的三元组表示
		// 用一个三元组（3-tuples）来表示一个非零元素
		// 一个稀疏矩阵中所有的非零元素按线性关系存在一张线性表中
		// 三元组顺序表（list of 3-tuples）
		// 采用以行为主序排序
		// 最后修改：2019-10-10
		namespace _6_2_1 {
			// 元素类型
			typedef int ElemType;

			// 稀疏矩阵的行数和列数
			const int M = 20;
			const int N = 20;

			// 稀疏矩阵中非零元素最多的个数
			constexpr int MaxSize = int((M * N) / 10);

			// 三元组类型
			typedef struct {
				int r;    // 行号
				int c;    // 列号
				ElemType d;    // 元素值
			} TupNode;

			// 三元组顺序表类型
			typedef struct {
				int rows;    // 行数
				int cols;    // 列数
				int nums;    // 非零元素个数
				TupNode data[MaxSize];
			} TSMatrix;

			// 从一个二维稀疏矩阵创建其三元组表示
			void CreateMat(TSMatrix& t, ElemType A[M][N]) {
				t.rows = M; t.cols = N; t.nums = 0;
				for (int i = 0; i < M; ++i) {
					for (int j = 0; j < N; ++j) {
						// 只存储非零元素
						if (A[i][j] != 0) {
							t.data[t.nums].r = i;
							t.data[t.nums].c = j;
							t.data[t.nums].d = A[i][j];
							++t.nums;
						}
					}
				}
			}

			// 三元组元素的赋值 x != 0
			// 先在三元组顺序表中找到适当位置k，在顺序表中位置为k的元素是在 矩阵[i][j]（含） 之后的第一个在顺序表中的元素
			// 如果顺序表中k元素正好矩阵中[i][j]元素，对应一个非零元素，将其d数据域修改为x
			// 如果顺序表中k元素在[i][j]之后，表明[i][j]位置上为零，先赋值为x，再将顺序表中k之后元素后移一位，x插入到k位置
			bool SetValue(TSMatrix& t, ElemType x, int i, int j) {
				if (i >= t.rows || j >= t.cols) {
					return false;    // 参数 i j 越界错误，返回false
				}
				int k = 0;
				while (k < t.nums && t.data[k].r < i) {
					++k;    // 寻找大于等于i行的非零元素，在顺序表中的位置k
				}
				while (k < t.nums && t.data[k].c == i && t.data[k].c < j) {
					++k;    // 若第i行有非零元素，寻找大于等于第j行的非零元素，在顺序表中的位置k
				}
				if (t.data[k].r == i && t.data[k].c == j) {
					t.data[k].d = x;    // 若顺序表中位置k的元素正好就是 矩阵ij 对应的元素，赋值 
				} else {
					// ij 上为零元素，要在顺序表中插入，先移动后面的元素，再赋值
					for (int k1 = t.nums - 1; k1 >= k; --k1) {
						t.data[k1 + 1].r = t.data[k1].r;
						t.data[k1 + 1].c = t.data[k1].c;
						t.data[k1 + 1].d = t.data[k1].d;
					}
					t.data[k].r = i; t.data[k].c = j; t.data[k].d = x;
					++t.nums;    // 非零元素的计数器加一
				}
				return true;
			}

			// 将指定位置的元素赋给变量
			bool Assign(TSMatrix t, ElemType &x, int i, int j) {
				if (i >= t.rows || j >= t.cols) {
					return false;    // 参数 i j 越界错误，返回false
				}
				int k = 0;
				while (k < t.nums && t.data[k].r < i) {
					++k;    // 寻找大于等于i行的非零元素，在顺序表中的位置k
				}
				while (k < t.nums && t.data[k].c == i && t.data[k].c < j) {
					++k;    // 若第i行有非零元素，寻找大于等于第j行的非零元素，在顺序表中的位置k
				}
				if (t.data[k].r == i && t.data[k].c == j) {
					x = t.data[k].d;    // 若顺序表中位置k的元素正好就是 矩阵ij 对应的元素，赋值 
				} else {
					x = 0;    // 指定位置ij不在顺序表中，即为零元素
				}
				return true;
			}

			// 输出三元组顺序表
			void DispMat(TSMatrix t) {
				if (t.nums <= 0) {
					return;    // 没有非零元素，即顺序表为空
				}
				printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
				printf("\t----------------------------------\n");
				for (int k = 0; k < t.nums; ++k) {
					printf("\t%d\t%d\t%d\n", t.data[k].r, t.data[k].c, t.data[k].d);
				}
			}

			// 稀疏矩阵转置 O(t.cols X t.rows)
			// 用tb来存储转置矩阵B的三元组顺序表
			// 赋值重建tb
			void TranTat(TSMatrix t, TSMatrix& tb) {
				if (t.nums <= 0) {
					return;    // 没有非零元素，即顺序表为空
				}
				tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;
				int k1 = 0;    // k1记录目前tb中元素的个数
				// 按列遍历原矩阵
				for (int v = 0; v < t.cols; ++v) {
					// 依次遍历顺序表中的非零元素，判断其位置是否是第v列
					for (int k = 0; k < t.nums; ++k) {
						if (t.data[k].c == v) {
							tb.data[k1].r = t.data[k].c;
							tb.data[k1].c = t.data[k].r;
							tb.data[k1].d = t.data[k].d;
							++k1;
						}
					}
				}
			}

		} // END namespace _6_2_1 稀疏矩阵的三元组表示

		// 6.2.2 稀疏矩阵的十字链表示
		// 每行一个行头结点，每列一个列头结点，还有一个总头结点
		// 每个元素结点同时存储在行和列两个循环单链表中
		// 最后修改：2019-10-10
		namespace _6_2_2 {
			// 稀疏矩阵的行数列数
			const int M = 20;
			const int N = 20;
			constexpr int Max = M > N ? M : N;

			typedef int ElemType;

			// 数据结点组成：行、列、值、右指针域、下指针域
			// 行列结点组成：行、列、link域、右指针域、下指针域
			// 分析发现两个数据结构相似，故采用共用体
			typedef struct mtxn {
				int row;    // 行号或行数
				int col;    // 列号或列数
				struct mtxn *right, *down;    // 右、下指针
				union {
					ElemType value;
					struct mtxn* link;
				} tag;
			} MatNode;

			// 例6.2 双层集合
			/*
			typedef struct dnode {
				int data;
				struct dnode* next;
			} DType;

			typedef struct hnode {
				DType* next;
				struct hnode* link;
			} HType;
			*/

		} // END namespace _6_2_2 稀疏矩阵的十字链表示

	} // END namespace _6_2 稀疏矩阵

	// 6.3 广义表（generalized table）
	// 广义表是线性表的推广，是有限个元素的序列，括号表示法
	// 元素类型：原子（atom），子表（subgeneralized table）
	// 长度为最外层包含元素的个数，深度为嵌套的层数
	// 元素类型：char
	// 最后修改：2019-10-10
	namespace _6_3 {
		// 广义表的抽象数据类型定义如下：
		/*
		ADT GList {
			数据对象:
				D = { ei | 1 <= i <= n, n >= 0, ei ∈ AtomSet 或 ei ∈ GList, AtomSet为某个数据对象 }
			基本关系:
				R = { <e(i-1), ei> | e(i-1)、ei ∈ D, 2 <= i <= n }
			基本运算:
				CreateGL(s);
				DestroyGL(&g);
				GLLength(g);
				GLDepth(g);
				DispGL(g);
		*/

		typedef char ElemType;

		// 广义表的存储结构
		typedef struct lnode {
			int tag;    // 结点类型标识，0为原子结点，1为子表结点
			union {
				ElemType data;    // 存放原子值
				struct lnode* sublist;    // 指向子表的指针
			} val;
			struct lnode* link;    // 指向下一个元素
		} GLNode;    // 广义表的结点类型

		// 广义表的运算，为使算法方便，在广义表的逻辑表示中用“(#)”表示空表
		// 若元素为结点，则其是其子表的头结点

		// 求广义表的长度
		int GLLength(GLNode* g) {
			int n = 0;    // 累计元素个数，初始为0
			GLNode* g1 = g->val.sublist;    // g1指向广义表的第一个元素
			while (g1 != NULL) {
				++n;    // 元素个数加一
				g1 = g1->link;    // 扫描所有元素结点
			}
			return n;
		}

		// 求广义表的深度
		// 原子深度为0，空表深度为1，其他情况深度为 max{ f(subg) } + 1
		int GLDepth(GLNode* g) {
			if (g->tag == 0) {
				return 0;    // 原子类型，返回0
			}
			GLNode* g1 = g->val.sublist;
			if (g1 == NULL) {
				return 1;    // 空表，返回1
			}
			int maxd = 0;
			// 遍历表中的每个元素
			while (g1 != NULL) {
				// 当元素为子表的时候，判断目前最大深度，并更新
				if (g1->tag == 1) {
					int dep = GLDepth(g1);
					if (dep > maxd) {
						maxd = dep;
					}
				}
				g1 = g1->link;
			}
			return maxd + 1;
		}

		// 输出广义表
		void DispGL(GLNode* g) {
			if (g != NULL) {
				// 元素为原子类型
				if (g->tag == 0) {
					printf("%c", g->val.data);    
				} else {
					// 元素类型为子表
					printf("(");
					if (g->val.sublist == NULL) {
						printf("#");    // 为空表
					} else {
						DispGL(g->val.sublist);    // 非空表，递归输出子表
					}
					printf(")");
				}
				if (g->link != NULL) {
					printf(",");
					DispGL(g->link);
				}
				/*g = g->link;*/
			}
		}

		// 建立广义表的链式存储结构
		// 假设广义表的逻辑结构采用括号表示，每个原子的值被限定为单个英文字母
		GLNode* CreateGL(char*& s) {
			GLNode* g;
			char ch = *s++;    // 取一个字符
			// s未扫描完时
			if (ch != '\0') {
				g = (GLNode*)malloc(sizeof(GLNode));    // 创建一个新结点
				if (ch == '(') {
					g->tag = 1;    // 字符为 ( ，标志子表开头
					g->val.sublist = CreateGL(s);    // 递归构造子表，将其赋给当前结点的sublist，当前的结点作为子表的头结点
				} else if (ch == ')') {
					g = NULL;
				} else if (ch == '#') {
					g = NULL;
				} else {
					g->tag = 0;    // 元素为原子字符
					g->val.data = ch;
				}
			} else {
				g = NULL;    // 字符扫描完毕，g置为空
			}
			ch = *s++;    // 取下一个未处理的字符
			if (g != NULL) {
				if (ch == ',') {
					g->link = CreateGL(s);    // 构造兄弟结点
				} else {
					g->link = NULL;
				}
			}
			return g;
		}

		// 销毁广义表
		void DestroyGL(GLNode*& g) {
			GLNode *g1, *g2;
			g1 = g->val.sublist;    // g1指向广义表的第一个元素
			// 遍历所有元素
			while (g1 != NULL) {
				// 若为原子结点
				if (g1->tag == 0) {
					g2 = g1->link;    // g2临时保存兄弟结点
					free(g1);    // 释放g1所指的原子结点
					g1 = g2;    // g1指向后继兄弟结点
				} else {
					// 若为子表
					g2 = g1->link;
					DestroyGL(g1);    // 递归释放g1所指的子表空间
					g1 = g2;
				}
			}
			free(g);
		}

		// 例6.3 对于采用链式存储结构的广义表，设计一个算法求原子元素个数
		// 解法一：
		int Count1(GLNode* g) {
			GLNode* g1 = g->val.sublist;
			int count = 0;
			while (g1 != NULL) {
				if (g1->tag == 0) {
					++count;
				} else {
					count += Count1(g1);
				}
				g1 = g1->link;
			}
			return count;
		}

		// 例6.3 对于采用链式存储结构的广义表，设计一个算法求原子元素个数
		// 解法二：
		int Count2(GLNode* g) {
			int count = 0;
			if (g != NULL) {
				if (g->tag == 0) {
					++count;
				} else {
					count += Count2(g->val.sublist);
				}
				count += Count2(g->link);
			}
			return count;
		}

	} // END namespace _6_3 广义表

} // END namespace dst 数据结构教程

#endif // !DST_6_ARRAY_GENERALIZED_TABLE_H