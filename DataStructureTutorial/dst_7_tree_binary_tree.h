// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_7_TREE_BINARY_TREE_H
#define DST_7_TREE_BINARY_TREE_H

// 第七章：树和二叉树

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 7.1 树（tree）的基本概念
	// 最后修改：2019-10-15
	namespace _7_1 {
		// 7.1.1 树的定义
		// 根节点简称根（root）、子树（subtree）
		// 树的抽象数据类型描述如下：
		/*
		ADT Tree {
			数据对象:
				D = { ai | 1 <= i <= n, n >= 0, ai 为 ElemType 类型 }    // ElemType 是自定义类型标识符
			数据关系:
				R = { <ai,aj> | ai, aj ∈ D, 1 <= i, j <= n, 其中有且只有一个结点没有前驱结点，其余每个结点只有一个前驱结点，但可以有零个或多个后继结点 }
			基本运算:
			InitTree(&t);
			DestroyTree(&t);
			TreeHeight(t);
			Parent(t,p);
			Brother(t,p);
			Sons(t,p);
			...
		}
		*/

		// 7.1.2 树的逻辑表示法：
		// 树形表示法（tree representation）
		// 文氏图表示法（venn diagram representation）
		// 凹入表示法（concave representation）
		// 括号表示法（brakcket representation）

		// 7.1.3 树的基本术语：
		// 结点的度（degree of node）：某个结点的子树的个数
		// 树的度（degree of tree）：所有结点中最大值，度为m的树称为m次树（m-tree）
		// 分支结点（branch）：树中不为零的结点称为非终端结点，又叫分支结点
		// 叶子结点（leaf）：度数为零的结点,度数为1的结点称为单分支结点，度数为2的结点称为双分支结点，以此类推
		// 路径（path）：从结点ki到结点kj，每一个结点都是在序列中的前一个结点的后继结点，则称为一条路径
		// 路径长度（path length）：是该路径上所有线段的权重之和，在此处考虑简单情况，权重为1
		// 孩子结点（children）、双亲结点（parents）、兄弟结点（sibling）、子孙结点（descendant）、祖先结点（ancestor）
		// 结点层次（level）或结点深度（depth）
		// 树的高度（height of tree）或树的高度（depth of tree）
		// 有序树（ordered tree）：各结点的子树是按照一定的次序从左向右安排的，且相对次序是不能随意改变的，否则为无序树（unordered tree）
		// 森林（forest）：多个互不相交的树的集合称为森林

		// 7.1.4 树的性质：（证明时考虑边界极限情况）
		// 性质1：树中的结点数 = 所有结点度数之和 + 1
		// 性质2：度数为m的树中，第i层上最多有 m^(i-1) 次方个结点（i >= 1）
		// 性质3：高度为h的m次树最多有 (m^h - 1) / (m - 1) 个结点
		// 性质4：具有n个结点的m次树的最小高度为 ⌈log m( n(m-1) + 1)⌉

		// 7.1.5 树的基本运算：
		// 1.寻找特点结点 2.插入或删除某个结点 3.树的遍历（traversal）
		// 先根遍历（preorder traversal）、后根遍历（postorder traversal）、层次遍历（level traversal）

		// 7.1.6 树的存储结构
		// 元素类型：int
		// 最后修改：2019-10-15
		namespace _7_1_6 {

			typedef int ElemType;    // 数据类型

			// 1.双亲存储结构（parent storage structure）
			// 是一种顺序存储结构，用连续的空间存储所有点，每个结点中有个指向双亲结点在顺序表中位置的伪指针
			const int MaxSize = 50;
			typedef struct {
				ElemType data;    // 存放结点的值
				int parent;    // 存放双亲结点的位置
			} PTree[MaxSize];    // PTree 为双亲存储结构类型

			// 2.孩子链存储结构（child chain storage structure）
			// 每个结点不仅包括值，还有指向所有孩子的指针
			const int MaxSons = 3;
			typedef struct node {
				ElemType data;    // 存放结点的值
				struct node* sons[MaxSons];    // 指向孩子结点
			} TSonNode;    // 孩子链存储结构中的结点类型

			// 3.孩子兄弟链存储结构（child brother chain storage structure）
			// 每个结点三个域，数据元素域，第一个孩子指针域，该结点下一个兄弟指针域
			// 类似广义表
			typedef struct tnode {
				ElemType data;    // 结点的值
				struct tnode* hp;    // 指向兄弟，horizon
				struct tnode* vp;    // 指向孩子结点，vertical
			} TSBNode;

			// 例 7.3 以孩子链作为树的存储结构，设计一个递归算法求树t的高度
			// f(t) = 0, t == NULL
			// f(t) = Max { f(p) } + 1, 其他情况，p指向t的孩子
			int TreeHeight1(TSonNode* t) {
				if (t == NULL) {
					return 0;    // 空树返回高度0
				} else {
					TSonNode* p;
					int maxh = 0;
					for (int i = 0; i < MaxSons; ++i) {
						p = t->sons[i];    // p指向t的第i+1个孩子
						if (p != NULL) {
							int h = TreeHeight1(p);    // 递归求子树高
							if (maxh < h) {
								maxh = h;    // 更新当前树的最大高度
							}
						}
					}
					return maxh + 1;
				}
			}

			// 例 7.4 以孩子兄弟链作为树的存储结构，设计一个求树高度的递归算法
			int TreeHeight2(TSBNode* t) {
				if (t == NULL) {
					return 0;    // 空树返回高度0
				}
				int maxh = 0;
				TSBNode* p = t->vp;    // p指向第1个孩子结点
				while (p != NULL) {
					int h = TreeHeight2(p);    // 求p子树的高度
					if (maxh < h) {
						maxh = h;
					}
					p = p->hp;    // 扫描处理t的其他子树
				}
				return maxh + 1;
			}


		} // END namespace _7_1_6 树的存储结构

	} // END namespace _7_1 树的基本概念

	// 7.2 二叉树（binary tree）的概念和性质
	// 最后修改：2019-10-17
	namespace _7_2 {
		// 7.2.1 二叉树的定义
		// 左子树（left subtree）、右子树（right subtree）
		// 满二叉树（full binary tree）：所有层都铺满结点
		// 完全二叉树（complete binary tree）：只有最下层最右侧（从右到左）可以却，其他均铺满
		// 满二叉树是完全二叉树的特殊情况
		// 层序编号（level coding）：从1开始，对完全二叉树，按层数从小到大，同一层从左到右依次排号

		// 7.2.2 二叉树的性质：
		// 性质1：叶子结点数 = 双分支结点数 + 1，n0 = n2 + 1，证明用：结点总数 n = n0 + n1 + n2，度之和 = n - 1 = n1 + 2 * n2
		// 性质2：第i层上最多有 2^(i-1) 次方 个结点（i >= 1）
		// 性质3：高度为h的二叉树最多有 2^h - 1 个结点（h >= 1）
		// 性质4：完全二叉树中的层序编号为 i 的结点（1 <= i <= n, n >= 1, n为结点个数）有以下性质：
		// 4.1：若 i <= ⌊n/2⌋，则i为分支结点，否则为叶子结点
		// 4.2：若 n 为奇数，则每个分支结点都有左右两个孩子；若 n 为偶数，则有且仅有一个编号为 ⌊n/2⌋ 的分支结点只有左孩子结点
		// 4.3：如果有的话，编号为 i 的结点，左孩子是 2i，右孩子是 2i + 1
		// 4.4：除根结点外，i 的双亲结点为 ⌊n/2⌋
		// 性质5：有 n 个结点的完全二叉树高度为 ⌈log2 (n + 1)⌉ 或 ⌊log2 n⌋ + 1

		// 7.2.3 二叉树与数，森林之间的转换
		/* 森林、树转换为二叉树
		（1）树中所有兄弟结点连一条线（森林中不同树的根结点可看成兄弟关系）
		（2）对树中的每个结点只保留它与长子（最左侧儿子）的连线，删除与其他孩子之间的连线
		（3）调整角度，让树的结构层次分明
		*/
		// 得到的二叉树的左分支是原来的孩子关系，右分支是兄弟关系，即：左孩子右兄弟
		/* 二叉树还原为树、森林
		（1）对于每个双亲结点，跟其左孩子结点的，所有的右孩子、右孩子的右孩子，依次都连接起来
		（2）删除原来所有双亲结点的右孩子、右孩子的右孩子的之间的连线
		（3）调整角度，让树的结构层次分明
		*/

	} // END namespace _7_2 二叉树的概念和性质

	// 7.3 二叉树的存储结构
	// 最后修改：2019-10-17
	namespace _7_3 {
		// 7.3.1 二叉树的顺序存储结构
		// 借助完全二叉树的层次编号来实现，以方便寻找孩子结点和双亲结点
		// 为与逻辑编号对应，不使用数组中索引为0的位置，置为空标识
		// 对于非完全二叉树，借用空元素将其补成完全二叉树，空用 # 标识
		// 元素类型：char
		// 最后修改：2019-10-17
		namespace _7_3_1 {
			// 二叉树顺序存储结构的类型声明如下：
			/*const int MaxSize = 50;
			typedef ElemType SqBinTree[MaxSize];*/
		} // END namespace _7_3_1 二叉树的顺序存储结构

		// 7.3.2 二叉树的链式存储结构
		// 一个结点： lchild  data  rchild
		// 通常检查为二叉链（binary linked list）
		// 二叉链中通过根结点指针 b 来唯一标识整个存储结构，称为二叉树b
		// 元素类型：char
		// 最后修改：2019-10-17
		namespace _7_3_2 {

			typedef char ElemType;

			// 二叉链中结点类型BTNode的声明如下：
			typedef struct node {
				ElemType data;    // 数据元素
				struct node* lchild;    // 指向左孩子结点
				struct node* rchild;    // 指向右孩子结点
			} BTNode;

		} // END namespace _7_3_2 二叉树的链式存储结构

	} // END namespace _7_3 二叉树的存储结构

	// 7.4 二叉树的基本运算及其实现
	// 元素类型：char
	// 最后修改：2019-10-31
	namespace _7_4 {
		// 7.4.1 二叉树的基本运算概述
		/*
		CreateBTree(b,str);
		DestroyBTree(&b);
		FindNode(b,x);
		LchildNode(p);
		RchildNode(p);
		BTHeight(b);
		DispBTree(b);
		*/

		// 7.4.2 二叉树基本运算算法实现

		// 引用二叉树的链式存储结构
		using _7_3::_7_3_2::BTNode;
		using _7_3::_7_3_2::ElemType;

		// dependence 依赖
		namespace dep {
			// 泛型栈
			template<typename T, size_t MaxSize = 50>
			struct Stack {
				T* data;
				int top;
				Stack() {
					data = new T[MaxSize];
				}
				~Stack() {
					delete[] data;
				}
			};

			template<typename T, size_t MaxSize>
			void InitStack(Stack<T, MaxSize>*& st) {
				st = new Stack<T, MaxSize>();
				st->top = -1;
			}

			template<typename T, size_t MaxSize>
			void DestroyStack(Stack<T, MaxSize>*& st) {
				delete st;
			}

			template<typename T, size_t MaxSize>
			bool StackEmpty(Stack<T, MaxSize>* st) {
				return st->top == -1;
			}

			template<typename T, size_t MaxSize>
			bool Push(Stack<T, MaxSize>*& st, T e) {
				if (st->top == MaxSize - 1) {
					return false;
				}
				++st->top;
				st->data[st->top] = e;
				return true;
			}

			template<typename T, size_t MaxSize>
			bool Pop(Stack<T, MaxSize>*& st, T& e) {
				if (st->top == -1) {
					return false;
				}
				e = st->data[st->top];
				--st->top;
				return true;
			}

			template<typename T, size_t MaxSize>
			bool Pop(Stack<T, MaxSize>*& st) {
				if (st->top == -1) {
					return false;
				}
				--st->top;
				return true;
			}

			template<typename T, size_t MaxSize>
			bool GetTop(Stack<T, MaxSize>* st, T& e) {
				if (st->top == -1) {
					return false;
				}
				e = st->data[st->top];
				return true;
			}
		} // END namespace dep 依赖

		// 创建二叉树 CreateBTree(*b, *str) ，从括号表示法创建，如 "A(B(D(,G)),C(E,F))"
		// 采用栈协助，用ch遍历字符串str，用k代表当前结点与栈顶结点的关系（1为左孩子，2为右孩子），若：
		// ch 为 ( ：表示它前面刚创建的结点p存在孩子结点，将该双亲结点进栈，然后开始处理左孩子，置k为1
		// ch 为 , ：表示开始处理当前栈顶结点（双亲结点）的右孩子结点，置k为2
		// ch 为 ) ：表示以栈顶为根结点的子树创建完毕，将其退栈
		// 其他情况 ：只能是单个字符，创建一个结点p处理该值，然后根据k的值处理它与栈顶结点之间的关系
		void CreateBTree(BTNode*& b, char* str) {
			dep::Stack<BTNode*> *st;
			InitStack(st);
			BTNode* p = (BTNode*)malloc(sizeof(BTNode));
			b = NULL;    // 初始时将二叉链置为NULL
			int j = 0, k;
			char ch = str[j];
			// 循环扫描str中的每个字符
			while (ch != '\0') {
				switch (ch) {
				case '(':
					// 开始处理左孩子结点，当前双亲结点进栈
					Push(st, p);
					k = 1;
					break;
				case ',':
					// 开始处理右孩子结点
					k = 2;
					break;
				case ')':
					// 栈顶结点的子树处理完毕
					Pop(st);
					break;
				default:
					p = (BTNode*)malloc(sizeof(BTNode));    // 创建一个结点，由p指向它
					p->data = ch;    // 存放结点值
					p->lchild = p->rchild = NULL;    // 左右孩子置为空
					// 若b为空，则表示尚未建立根结点
					if (b == NULL) {
						b = p;    // p所指的结点作为根结点
					} else {
						// 已创建根结点
						BTNode* t;
						GetTop(st, t);    // 取栈顶结点所表示的双亲结点
						switch (k) {
						case 1:
							t->lchild = p;    // 新建结点p作为栈顶结点的左孩子
							break;
						case 2:
							t->rchild = p;    // 新建结点作为栈顶结点的右孩子
							break;
						}
					}
				}
				++j;    // 继续扫描str
				ch = str[j];
			}
		}

		// 创建二叉树 CreateBTree(*b, *str) ，从括号表示法创建，如 "A(B(D(,G)),C(E,F))"
		// 树中的结点类型为T
		template<typename T>
		void CreateBTree(T*& b, char* str) {
			dep::Stack<T*> *st;
			InitStack(st);
			T* p = (T*)malloc(sizeof(T));
			b = NULL;    // 初始时将二叉链置为NULL
			int j = 0, k;
			char ch = str[j];
			// 循环扫描str中的每个字符
			while (ch != '\0') {
				switch (ch) {
				case '(':
					// 开始处理左孩子结点，当前双亲结点进栈
					Push(st, p);
					k = 1;
					break;
				case ',':
					// 开始处理右孩子结点
					k = 2;
					break;
				case ')':
					// 栈顶结点的子树处理完毕
					Pop(st);
					break;
				default:
					p = (T*)malloc(sizeof(T));    // 创建一个结点，由p指向它
					p->data = ch;    // 存放结点值
					p->lchild = p->rchild = NULL;    // 左右孩子置为空
					// 若b为空，则表示尚未建立根结点
					if (b == NULL) {
						b = p;    // p所指的结点作为根结点
					} else {
						// 已创建根结点
						T* t;
						GetTop(st, t);    // 取栈顶结点所表示的双亲结点
						switch (k) {
						case 1:
							t->lchild = p;    // 新建结点p作为栈顶结点的左孩子
							break;
						case 2:
							t->rchild = p;    // 新建结点作为栈顶结点的右孩子
							break;
						}
					}
				}
				++j;    // 继续扫描str
				ch = str[j];
			}
		}


		// 销毁二叉树 DestroyBTree(&b)
		void DstroyBTree(BTNode*& b) {
			if (b != NULL) {
				DstroyBTree(b->lchild);
				DstroyBTree(b->rchild);
				free(b);
			}
		}

		// 查找结点 FindNode(b,x)
		BTNode* FindNode(BTNode* b, ElemType x) {
			if (b == NULL) {
				return NULL;
			} else if (b->data == x) {
				return b;
			} else {
				BTNode* p = FindNode(b->lchild, x);
				if (p != NULL) {
					return p;
				} else {
					return FindNode(b->rchild, x);
				}
			}
		}

		// 找左孩子结点 LchildNode(b)
		BTNode* LchildNode(BTNode* b) {
			return b->lchild;
		}

		// 找右孩子结点 RchildNode
		BTNode* RchildNode(BTNode* b) {
			return b->rchild;
		}

		// 求高度 BTHeight(b)
		int BTHeight(BTNode* b) {
			if (b == NULL) {
				return 0;
			} else {
				int left = BTHeight(b->lchild);
				int right = BTHeight(b->rchild);
				return left > right ? left + 1 : right + 1;
			}
		}

		// 输出二叉树 DispBTree(b)
		void DispBTree(BTNode* b) {
			if (b != NULL) {
				// 当前结点非空，输出其表示的值
				printf("%c", b->data);
				// 至少有一个孩子结点时
				if (b->lchild != NULL || b->rchild != NULL) {
					printf("(");
					DispBTree(b->lchild);    // 递归处理左子树
					if (b->rchild != NULL) {
						// 如果有右孩子结点，先输出 ,
						printf(",");
					}
					DispBTree(b->rchild);    // 递归处理右孩子结点
					printf(")");
				}
			}
		}

	} // END namespace _7_4_1 二叉树的基本运算及其实现

	// 7.5 二叉树的遍历
	// 元素类型：char
	// 最后修改：2019-10-24
	namespace _7_5 {
		// 规定子树的遍历方法总是先左后右，有：
		// 先序遍历（preorder traversal）、中序遍历（inorder traversal）、后序遍历（postorder traversal）
		// 又叫，先根遍历，中根遍历，后根遍历
		// 先序遍历：访问根结点 -> 先序遍历左子树 -> 先序遍历右子树
		// 中序遍历：中序遍历左子树 -> 访问根结点 -> 中序遍历右子树
		// 后序遍历：后序遍历左子树 -> 后序遍历右子树 -> 访问根节点
		// 还有一个层次遍历（level traversal）：非递归的，一层一层的访问所有结点

		// 7.5.2 先序、中序、后序遍历的递归算法
		// 最后修改：2019-10-24
		namespace _7_5_2 {
			// 引用二叉树类型
			using _7_3::_7_3_2::BTNode;
			using _7_3::_7_3_2::ElemType;

			// 先序遍历递归算法
			void PreOrder(BTNode* b) {
				if (b != NULL) {
					printf("%c", b->data);
					PreOrder(b->lchild);
					PreOrder(b->rchild);
				}
			}

			// 中序遍历递归算法
			void InOrder(BTNode* b) {
				if (b != NULL) {
					InOrder(b->lchild);
					printf("%c", b->data);
					InOrder(b->rchild);
				}
			}

			// 后序遍历递归算法
			void PostOrder(BTNode* b) {
				if (b != NULL) {
					PostOrder(b->lchild);
					PostOrder(b->rchild);
					printf("%c", b->data);
				}
			}

			// 例 7.11 二叉树采用二叉链存储，求所有结点个数
			int Nodes(BTNode* b) {
				if (b == NULL) {
					return 0;
				} else {
					return Nodes(b->lchild) + Nodes(b->rchild) + 1;
				}
			}

			// 例 7.12 二叉树采用二叉链存储，输出所有叶子结点
			void DispLeaf(BTNode* b) {
				if (b != NULL) {
					if (b->lchild == NULL && b->rchild == NULL) {
						printf("%c ", b->data);
					}
					DispLeaf(b->lchild);
					DispLeaf(b->rchild);
				}
			}

			// 例 7.13 二叉树采用二叉链存储，求值为x的结点在树中的深度
			// 调用时，h = 1
			int Level(BTNode* b, ElemType x, int h) {
				// h 表示 结点 b 在树中的第几层，从外部调用时初始值应置为1
				if (b == NULL) {
					return 0;
				} else if (b->data == x) {
					return h;
				} else {
					int lev = Level(b->lchild, x, h + 1);    // 在左子树中查找
					// lev不为零，表示在左子树中找到了
					if (lev != 0) {
						return lev;
					} else {
						// 没在左子树中找到，返回在右子树中查找的结果
						return Level(b->rchild, x, h + 1);
					}
				}
			}

			// 例 7.14 二叉树采用二叉链存储，求二叉树中第 k 层的结点的个数
			// h 表示 b 所指结点的层次（根结点为1），n为引用型参数，求第k层结点的个数
			void Lnodenum(BTNode* b, int h, int k, int& n) {
				if (b == NULL) {
					n = 0;
					return;    // 空树直接返回
				} else {
					if (h == k) {
						// 当前访问的结点正好在第k层，则第k层的结点个数加一
						++n;
					} else if (h < k) {
						Lnodenum(b->lchild, h + 1, k, n);
						Lnodenum(b->rchild, h + 1, k, n);
					}
				}
			}

			// 例 7.15 以二叉链存储的二叉树，判断两个二叉树是否相似
			// 都是空，或根、左子树、右子树都相似
			bool Like(BTNode* b1, BTNode* b2) {
				if (b1 == NULL && b2 == NULL) {
					return true;
				} else if (b1 == NULL || b2 == NULL) {
					return false;
				} else {
					return Like(b1->lchild, b2->lchild) && Like(b1->rchild, b2->rchild);
				}
			}

			// 例 7.16 二叉树采用二叉链存储，输出值为x的结点的所有祖先
			bool ancestor(BTNode* b, ElemType x) {
				if (b == NULL) {
					return false;
				} else if (b->lchild != NULL && b->lchild->data == x ||
						   b->rchild != NULL && b->rchild->data == x) {
					printf("%c ", b->data);
					return true;
				} else if (ancestor(b->lchild, x) || ancestor(b->rchild, x)) {
					printf("%c ", b->data);
					return true;
				} else {
					return false;
				}
			}

		} // END namespace _7_5_2 先序、中序、后序遍历的递归算法

		// 7.5.3 先序、中序、后序遍历的非递归算法
		// 进栈保存现场状态
		// 根据遍历顺序，来进栈以摆好顺序；还要注意是出栈时访问还是进栈时访问
		// 最后修改：2019-10-29
		namespace _7_5_3 {
			// 引用二叉树的链式存储结构
			using _7_3::_7_3_2::BTNode;
			using _7_3::_7_3_2::ElemType;

			// dependence 依赖
			namespace dep {
				// 泛型栈
				template<typename T, size_t MaxSize = 50>
				struct Stack {
					T* data;
					int top;
					Stack() {
						data = new T[MaxSize];
					}
					~Stack() {
						delete[] data;
					}
				};

				template<typename T, size_t MaxSize>
				void InitStack(Stack<T, MaxSize>*& st) {
					st = new Stack<T, MaxSize>();
					st->top = -1;
				}

				template<typename T, size_t MaxSize>
				void DestroyStack(Stack<T, MaxSize>*& st) {
					delete st;
				}

				template<typename T, size_t MaxSize>
				bool StackEmpty(Stack<T, MaxSize>* st) {
					return st->top == -1;
				}

				template<typename T, size_t MaxSize>
				bool Push(Stack<T, MaxSize>*& st, T e) {
					if (st->top == MaxSize - 1) {
						return false;
					}
					++st->top;
					st->data[st->top] = e;
					return true;
				}

				template<typename T, size_t MaxSize>
				bool Pop(Stack<T, MaxSize>*& st, T& e) {
					if (st->top == -1) {
						return false;
					}
					e = st->data[st->top];
					--st->top;
					return true;
				}

				template<typename T, size_t MaxSize>
				bool Pop(Stack<T, MaxSize>*& st) {
					if (st->top == -1) {
						return false;
					}
					--st->top;
					return true;
				}

				template<typename T, size_t MaxSize>
				bool GetTop(Stack<T, MaxSize>* st, T& e) {
					if (st->top == -1) {
						return false;
					}
					e = st->data[st->top];
					return true;
				}
			} // END namespace dep 依赖

			// 先序遍历的非递归算法1，此算法较为简单
			// 根据栈的先进后出特性，并结合根左右的遍历顺序，调整为 先访问，进右孩子，进左孩子
			void PreOrder1(BTNode* b) {
				// 根结点不为空
				if (b != NULL) {
					dep::Stack<BTNode*>* st;
					InitStack(st);
					BTNode* p;
					Push(st, b);
					while (!StackEmpty(st)) {
						Pop(st, p);
						printf("%c ", p->data);
						if (p->rchild != NULL) {
							Push(st, p->rchild);
						}
						if (p->lchild != NULL) {
							Push(st, p->lchild);
						}
					}
					DestroyStack(st);
				}
				printf("\n");
			}

			/* 先序遍历的非递归算法2，根，左，右
			先遍历根结点b及其所有左下结点（用栈保存访问过的结点，因为二叉链中无法用孩子找到双亲）
			直到栈顶结点没有左孩子，或左孩子已经遍历过
			之后转向右孩子右子树，处理方法如上述过程类似，伪代码如下：
			p = b;
			while (栈不为空 或 p != NULL) {
				while (p不为空) {
					访问p;
					将p进栈;
					p = p->lchild;
				}
				// 此时栈顶结点（已访问）没有左孩子，或左孩子已经遍历过
				if (栈不空) {
					出栈p;
					p = p->rchild;
				}
			}
			*/
			void PreOrder2(BTNode* b) {
				dep::Stack<BTNode*>* st;
				InitStack(st);
				BTNode* p = b;
				while (!StackEmpty(st) || p != NULL) {
					// 访问p结点及其所有左下结点并进栈
					while (p != NULL) {
						printf("%c ", p->data);
						Push(st, p);     // 结点p进栈，栈顶更新
						p = p->lchild;
					}
					if (!StackEmpty(st)) {
						Pop(st, p);     // 出栈栈顶，p转向原栈顶的右孩子
						p = p->rchild;    // 右孩子若为空，则上一个 while 直接跳过，再次退栈Pop
					}
				}
				printf("\n");
				DestroyStack(st);
			}

			/* 中序遍历的非递归算法
			由先序遍历的非递归算法2修改而来，将 进栈时遍历 改为 出栈时遍历
			p = b;
			while (栈不空 或 p != NULL) {
				while (结点p不为空) {
					将p进栈;
					p = p->lchild;
				}
				// 此时栈顶结点（未访问）没有左孩子，或左孩子以遍历完
				if (栈不空) {
					出栈p;
					访问p;
					p = p->rchild;
				}
			}
			*/
			void InOrder(BTNode* b) {
				dep::Stack<BTNode*>* st;
				InitStack(st);
				BTNode* p = b;
				while (!StackEmpty(st) || p != NULL) {
					while (p != NULL) {
						Push(st, p);
						p = p->lchild;
					}
					if (!StackEmpty(st)) {
						Pop(st, p);    // 出栈，栈顶更新
						printf("%c ", p->data);
						p = p->rchild;    // 处理原栈顶结点的右孩子
					}
				}
				printf("\n");
				DestroyStack(st);
			}

			/* 后序遍历的非递归算法
			由中序遍历的非递归算法修改而来，左子树为空或已遍历，再遍历完右子树，才能访问结点p
			伪代码如下：
			p = b;
			do {
				while (结点p不为空) {
					将结点p进栈;
					p = p->lchild;
				}
				p是栈顶 = true;    // p是栈顶表示处理到最左下的结点，否则代表刚转为右孩子结点
				r = NULL;    // 用r指向刚遍历的结点（初始为NULL），用以判断结点p的右孩子是否访问过或为空（p->rchild == r)
				// 此时栈顶结点（尚未访问）没有左孩子，或左孩子已经遍历过，该处理右孩子
				while (栈不为空 且 p是栈顶) {
					取栈顶结点为p（不退栈）;
					if (p->rchild == r) {
						// 右子树已遍历过
						访问节点p;
						Pop(st, r);    // 退栈，r更新为原栈顶结点（最后处理的结点）
					} else {
						p = p->rchild;
						p是栈顶 = false;
					}
				}
			} while (栈不空);
			该后序遍历的非递归算法，当访问某个结点时，栈中保存的正好是该结点的所有祖先结点
			*/
			void PostOrder(BTNode* b) {
				dep::Stack<BTNode*>* st;
				InitStack(st);
				BTNode* p = b;
				bool isHandlingTop;
				BTNode* r;    // 表示最后访问的结点
				do {
					while (p != NULL) {
						Push(st, p);
						p = p->lchild;
					}
					isHandlingTop = true;
					r = NULL;
					while (!StackEmpty(st) && isHandlingTop) {
						GetTop(st, p);
						// 右孩子已遍历，或为空
						if (p->rchild == r) {
							// 访问当前栈顶，退栈，更新最后遍历结点
							printf("%c ", p->data);
							Pop(st, r);
						} else {
							// 此分支p的右孩子不为空，故一定会执行前一个while，找其左下
							p = p->rchild;
							isHandlingTop = false;
						}
					}

				} while (!StackEmpty(st));
				printf("\n");
				DestroyStack(st);
			}

			// 例7.17 二叉树采用二叉链存储，输出每个叶子结点到根结点的路径，采用后序遍历的非递归算法实现
			void AllPath1(BTNode* b) {
				dep::Stack<BTNode*>* st;
				InitStack(st);
				BTNode* p = b;
				bool isHandlingTop;
				BTNode* r;
				do {
					while (p != NULL) {
						Push(st, p);
						p = p->lchild;
					}
					isHandlingTop = true;
					r = NULL;
					while (!StackEmpty(st) && isHandlingTop) {
						GetTop(st, p);
						if (p->rchild == r) {
							// 访问结点p，即若为叶子结点，输出路径
							if (p->lchild == NULL && p->rchild == NULL) {
								dep::Stack<BTNode*>* stTemp;
								InitStack(stTemp);
								BTNode* nodeTemp;
								Pop(st, nodeTemp);
								printf("%c", nodeTemp->data);
								Push(stTemp, nodeTemp);
								while (!StackEmpty(st)) {
									Pop(st, nodeTemp);
									printf("->%c", nodeTemp->data);
									Push(stTemp, nodeTemp);
								}
								printf("\n");
								while (!StackEmpty(stTemp)) {
									Pop(stTemp, nodeTemp);
									Push(st, nodeTemp);
								}
							}
							// 访问完成
							Pop(st, r);
						} else {
							p = p->rchild;
							isHandlingTop = false;
						}
					}

				} while (!StackEmpty(st));
			}

		} // END namespace _7_5_3 先序、中序、后序遍历的非递归算法

		// 7.5.4 层次遍历算法
		// 最后修改：2019-10-29
		namespace _7_5_4 {
			using dst::_7_3::_7_3_2::BTNode;    // 引用二叉链

			// dependency 依赖
			namespace dep {
				// 泛型队列
				template<typename T, size_t MaxSize = 50>
				struct Queue {
					T* data;
					int front;
					int rear;
					Queue() {
						data = new T[MaxSize];
					}
					~Queue() {
						delete[] data;
					}
				};

				template<typename T, size_t MaxSize>
				void InitQueue(Queue<T, MaxSize>*& q) {
					q = new Queue<T, MaxSize>();
					q->front = q->rear = -1;
				}

				template<typename T, size_t MaxSize>
				void DestroyQueue(Queue<T, MaxSize>*& q) {
					delete q;
				}

				template<typename T, size_t MaxSize>
				bool QueueEmpty(Queue<T, MaxSize>* q) {
					return q->rear == q->front;
				}

				template<typename T, size_t MaxSize>
				bool enQueue(Queue<T, MaxSize>*& q, T e) {
					if (q->rear == MaxSize - 1) {
						return false;
					}
					++q->rear;
					q->data[q->rear] = e;
					return true;
				}

				template<typename T, size_t MaxSize>
				bool deQueue(Queue<T, MaxSize>*& q, T& e) {
					if (q->front == q->rear) {
						return false;
					}
					++q->front;
					e = q->data[q->front];
					return true;
				}
			} // END namespace dep 依赖

			// 层次遍历较为简单
			// 先将根结点进队，队不为空时循环，若有左孩子则进队，有右孩子则进队，如此操作直到队空
			void LevelOrder(BTNode* b) {
				dep::Queue<BTNode*>* qu;
				InitQueue(qu);
				enQueue(qu, b);
				BTNode* p;
				while (!QueueEmpty(qu)) {
					deQueue(qu, p);
					printf("%c ", p->data);
					if (p->lchild != NULL) {
						enQueue(qu, p->lchild);
					}
					if (p->rchild != NULL) {
						enQueue(qu, p->rchild);
					}
				}
				printf("\n");
				DestroyQueue(qu);
			}

			// 例 7.18 采用层次遍历法设计例7.17的算法
			void AllPath2(BTNode* b) {
				typedef struct snode {
					BTNode* pt;    // 存放树中当前结点的指针
					int parent;    // 存放双亲结点在队列中的位置
				} NodeType;    // （非环形）队列中结点的元素类型

				BTNode* p;    // 树中的结点
				dep::Queue<NodeType>* qu;    // 队列
				InitQueue(qu);
				NodeType qelem;    // 队列中的结点
				qelem.pt = b;    // 创建根结点对应的队列元素
				qelem.parent = -1;    // 根结点的双亲位置标为-1
				enQueue(qu, qelem);
				while (!QueueEmpty(qu)) {
					deQueue(qu, qelem);
					// 访问
					p = qelem.pt;
					if (p->lchild == NULL && p->rchild == NULL) {
						// p为叶子结点，输出其到根结点的路径
						int k = qu->front;
						while (qu->data[k].parent != -1) {
							printf("%c->", qu->data[k].pt->data);
							k = qu->data[k].parent;
						}
						printf("%c\n", qu->data[k].pt->data);
					}
					// 访问结束
					// 判断左右孩子是否为空，将其进队
					if (p->lchild != NULL) {
						qelem.pt = p->lchild;
						qelem.parent = qu->front;
						enQueue(qu, qelem);
					}
					if (p->rchild != NULL) {
						qelem.pt = p->rchild;
						qelem.parent = qu->front;
						enQueue(qu, qelem);
					}
				}
				DestroyQueue(qu);
			}

		} // END namespace _7_5_4 层次遍历算法

	} // END namespace _7_5 二叉树的遍历

	// 7.6 二叉树的构造
	// 有n个结点的二叉树有 C(n)(2n) / (n+1) 种
	// 假设每个结点值为单个字符，且所有结点的值均不相同
	// 由中序序列 和 先序序列 或 后序序列 可唯一确定一二叉树（先序和后序不能唯一确定）
	// 元素类型：char
	// 最后修改：2019-10-31
	namespace _7_6 {
		using dst::_7_3::_7_3_2::BTNode;    // 引用二叉链
		
		// 定理7.1：任何n(n>=0)个不同结点的二叉树，都可由它的中序序列和先序序列唯一确定
		// 根据先序序列确定二叉树的根结点（第一个），在中序序列中找到这个根结点，则中序序列中其左边的为左子树，右边的为右子树
		// 进而可以确定左右子树的序列（左子树和右子树分别多少个结点 l，r），再从先序序列和中序序列中找到l，r个结点，递归构造左右子树
		// @param pre存放先序序列，in存放中序序列，n为二叉树的结点树
		// @return 构造的二叉树的根结点指针
		BTNode* CreateBTreeWithPreInOrder(char* pre, char* in, int n) {
			if (n <= 0) {
				return NULL;
			}
			BTNode* b = (BTNode*)malloc(sizeof(BTNode));
			b->data = *pre;
			char* p;
			for (p = in; p < in + n; ++p) {
				// 在中序序列中找到根结点的位置，用p指向
				if (*p == *pre) {
					break;
				}
			}
			int index = static_cast<int>(p - in);    // 确定根结点在中序序列中的物理下标
			// 递归构造左右子树，pre的第一个为根结点，已遍历过，故 +1 将之跳过
			b->lchild = CreateBTreeWithPreInOrder(pre + 1, in, index);    // 去掉在中序序列中的根结点，其左子树序列中正好index个结点
			b->rchild = CreateBTreeWithPreInOrder(pre + index + 1, p + 1, n - index - 1);
			return b;
		}

		// 定理7.2：任何n(n>0)个不同的二叉树都可由它的中序序列和后序序列唯一确定
		// 同理，利用后序序列来找到根结点（最后一个），其他操作同定理7.1
		// @param post存放后序序列，in存放中序序列，n为二叉树的结点树
		// @return 构造的二叉树的根结点指针
		BTNode* CreateBTreeWithPostInOrder(char* post, char* in, int n) {
			if (n <= 0) {
				return NULL;
			}
			char r = *(post + n - 1);    // 找到根结点的值
			BTNode* b = (BTNode*)malloc(sizeof(BTNode));
			b->data = r;
			char* p;
			for (p = in; p < in + n; ++p) {
				// p指向在中序序列中的根结点的位置
				if (*p == r) {
					break;
				}
			}
			int index = static_cast<int>(p - in);
			// 后序的第一个没用掉，故不用 post + 1
			b->lchild = CreateBTreeWithPostInOrder(post, in, index);
			b->rchild = CreateBTreeWithPostInOrder(post + index, in + index + 1, n - index - 1);     // in + index + 1 == p + 1
			return b;
		}


	} // END namespace _7_6

	// 7.7 线索二叉树（threaded binary-tree）
	// 当某结点的左右指针为空时，根据遍历方式，将其空结点分别指向前驱和后继结点，这些指针称为线索（thread）
	// 遍历二叉树的结果是一个结点的线性序列，线索化以提高遍历效率
	// 最后修改：2019-10-31
	namespace _7_7 {
		// 为线索化，给结点加两个成员，ltag和rtag，0表示指向孩子，1表示指向线索
		typedef char ElemType;
		typedef struct node {
			ElemType data;
			int ltag, rtag;
			struct node* lchild;
			struct node* rchild;
		} TBTNode;    // 线索二叉树中的结点类型

		// 在某遍历方式中：若开始结点p无左孩子，则左指针线索化，左指针仍为空
		// 若最后结点q没有右孩子，则右指针线索化，右指针仍为空
		// 其他结点r，若无左孩子，左指针线索化指向前驱结点；若无右孩子，则右指针线索化指向后继结点

		// 为使线索化简单，在线索二叉树中再增加一个头结点head，其data域为空
		// lchild指向无线索化时的根结点，ltag = 0，若二叉树为空，lchild指向自身
		// rchild指向按某种方式遍历的最后一个结点，rtag = 1

		// 线索化，用pre表示p的前驱结点，p表示pre的后继结点
		// 若p的左指针为空，则线索化指向pre；若pre的右指针为空，则线索化指向p
		// 处理结束后，p指向NULL，pre指向最后一个结点

		// 中序线索化
		void InThread(TBTNode*& p, TBTNode*& pre) {
			if (p != NULL) {
				InThread(p->lchild, pre);    // 左子树线索化
				// 线索化p结点
				if (p->lchild == NULL) {
					p->lchild = pre;    // 左孩子不存在，进行前驱结点线索化，建立当前结点的前驱线索结点
					p->ltag = 1;
				} else {
					p->ltag = 0;    // p的左孩子存在
				}
				if (pre->rchild == NULL) {
					pre->rchild = p;
					pre->rtag = 1;
				} else {
					p->rtag = 0;
				}
				pre = p;    // p结点线索化完毕，更新pre前驱结点
				InThread(p->rchild, pre);
			}
		}
		
		// 建立中序线索化二叉树
		// 参数为根结点，返回头结点
		TBTNode* CreateInThreadBTree(TBTNode* b) {
			TBTNode* head = (TBTNode*)malloc(sizeof(TBTNode));
			head->ltag = 0;
			head->rtag = 1;
			head->rchild = b;
			if (b == NULL) {
				head->lchild = head;
			} else {
				head->lchild = b;
				TBTNode* pre = head;
				InThread(b, pre);
				pre->rchild = head;    // 最后处理的结点的右孩子指向头结点
				pre->rtag = 1;
				head->rchild = pre;    // 头结点右线索化
			}
			return head;
		}

		/* 遍历线索二叉树：从开始结点出发，反复访问后继结点（没有有线索则转向右孩子）直到头结点
		算法的伪代码：
		p指向根结点;
		while (p != head) {
			找到开始结点p;
			访问结点p;
			while(p有右线索) {
				一直访问下去;
			}
			p转向右孩子结点;
		}
		其找到开始结点：中序遍历的开始结点时最左下结点，while(p->ltag == 0) { p = p->lchile; }
		*/
		void ThInOrder(TBTNode* head) {
			TBTNode* p = head->lchild;    // p指向根结点
			while (p != head) {
				while (p->ltag == 0) {
					p = p->lchild;    // 找开始结点
				}
				printf("%c ", p->data);
				while (p->rtag == 1 && p->rchild != head) {
					p = p->rchild;
					printf("%c ", p->data);
				}
				p = p->rchild;
			}
			printf("\n");
		}


	} // END namespace _7_7 线索二叉树

	// 7.8 哈夫曼树（Huffman tree）
	// 最后修改:2019-11-5
	namespace _7_8 {
		// 将树的每个结点赋予一个权，从根结点到该点之间的路径长度与该结点权的乘积为带权路径长度（Weighted Path Length, WPL）
		// 在n个叶子结点构成的所有二叉树中，WPL最小的二叉树称为哈夫曼树或最优二叉树
		// 定理7.3：对于有 n 个叶子结点的哈夫曼树，共有 2n - 1 个结点

		// 哈夫曼树构造算法
		// 1. n个带权叶子节点，看成n个只有根结点的树，构成集合F（森林）
		// 2. 在 F 中取最小和次小权值的两颗树，做左孩子和右孩子，构造一棵新树，根结点为二者之和
		// 3. 将新树放入 F 中，并删除原来的两棵树
		// 4. 重复 2 和 3，直到 F 中只含一颗树

		typedef struct {
			char data;
			double weight;    // 权重
			int parent;    // 伪指针，采用顺序存储
			int lchild;
			int rchild;
		} HTNode;    // 哈夫曼树中的结点类型

		// 构造哈夫曼树，采用顺序存储 ht[0...2n-1)
		// ht[0...n-1] 表示叶子结点，ht[n...2n-2]表示非叶子结点
		// 所有结点的 parent lchild rchild 初始值置为 -1
		// 遍历所有 2n - 1 个结点
		void CreatHT(HTNode ht[], int n) {
			int leftIndex, rightIndex, index;
			double minWeight1, minWeight2;
			for (int i = 0; i < 2 * n - 1; ++i) {
				ht[i].parent = ht[i].lchild = ht[i].rchild = -1;    // 所有结点的parent lchild rchild置为 -1
			}
			// 构造剩下的 [n...2n-2] 的结点
			for (int i = n; i < 2 * n - 1; ++i) {
				minWeight1 = minWeight2 = ht[0].weight;
				leftIndex = rightIndex = -1;
				// 在已有的 i 个结点中找到最小和次小
				for (index = 0; index < i; ++index) {
					// 只在未构造的结点中查找，即parent 为 -1 的
					if (ht[index].parent == -1) {
						if (ht[index].weight < minWeight1) {
							minWeight2 = minWeight1;
							rightIndex = leftIndex;
							minWeight1 = ht[index].weight;
							leftIndex = index;
						} else if (ht[index].weight < minWeight2) {
							minWeight2 = ht[index].weight;
							leftIndex = index;
						}
					}
				}
				ht[i].weight = ht[leftIndex].weight + ht[rightIndex].weight;
				ht[i].lchild = leftIndex;
				ht[i].rchild = rightIndex;
				ht[leftIndex].parent = ht[rightIndex].parent = i;
			}
		}

		// 哈夫曼编码（huffman coding），规定哈夫曼树中左子树为0，右子树为1
		// 则从根结点到叶子结点所经历的0和1组成的序列即为哈夫曼编码

		typedef struct {
			const static int N = 8;    // 哈夫曼编码的最大长度，为哈夫曼树的最大深度
			char cd[N];
			int start;    // 方便从右向左赋值
		} HCode;

		void CreateHCode(HTNode ht[], HCode hcd[], int n) {
			int parentIndex, curIndex;
			HCode hc;
			for (int i = 0; i < n; ++i) {
				hc.start = HCode::N - 1;
				curIndex = i;
				parentIndex = ht[curIndex].parent;
				while (parentIndex != -1) {
					if (ht[parentIndex].lchild == curIndex) {
						hc.cd[hc.start--] = '0';
					} else {
						hc.cd[hc.start--] = '1';
					}
					curIndex = parentIndex;
					parentIndex = ht[parentIndex].parent;
				}
				++hc.start;
				hcd[i] = hc;
			}
		}

	} // END namespace _7_8 哈夫曼树

	// 7.9 用并查集（disjoint-set）求解等价问题
	// 最后修改：2019-11-22
	namespace _7_9 {
		// 对于集合 S 中的关系 R，若其具有自反、对称和传递性，则 R 是一个等价关系
		// 由等价关系可以产生集合 S 的等价类

		// 7.9.1 什么叫并查集
		// 并查集支持 查找一个元素所属的集合 以及 两个元素各自所属的集合的合并 等运算
		// 对于两个元素 a b，需要快速合并 a 和 b 所在的集合时，这期间需要反复“查找”某元素所在的集合，“并”“查”“集”由此而来
		// 在这种数据类型中，n 个不同的元素被分为若干组，每组是一个集合，叫分离集合，称之为 并查集（disjoint-set）
		// 并查集的数据记录代表了一组分离的动态集合 S = { S1, S2, ..., Sk }，每个动态集合 Si 通过自身的一个任意的元素加以“代表”
		// 对于给定的编号为 1~n 的 n 个元素，x 表示其中的一个元素，设并查集为 S，并查集的实现需要支持如下运算：
		// (1)、MAKE_SET(S, n)：初始化并查集S，即 S = { S1, S2, ..., Sn }，每个动态集合 Si（i <= i <= n）仅仅包含一个编号为 i 的元素，并为Si的代表
		// (2)、FIND_SET(S, x)：返回并查集 S 中 x 元素所在集合的代表
		// (3)、UNION(S, x, y)：在并查集 S 中将 x 和 y 两个元素所在的动态集合合并为一个新的集合，并更新代表（通常以 Sx 或 Sy 的代表作为新集合的代表）

		// 7.9.2 并查集的算法实现
		// 并查集必须借助某种数据结构来实现，使用比较多的有 数组实现、链表实现 和 树实现，这里主要介绍 树实现 方法
		// 用一棵有根树表示一个集合，树中的每个结点包含集合的一个元素，树根作为集合的代表；多个集合形成一个森林
		// 树中的每个结点都有一个指向双亲结点的指针，根结点的双亲结点指向自身
		// 在同一棵树中的结点属于同一个集合，虽然它们在树中存在父子结点关系，但并不意味着他们之间存在从属关系
		// 显然在一颗高度较低的树中查找根结点的编号（即该集合的代表）所花的时间较少，故当两棵分离集合树 A 和 B 合并时，
		// 总是将高度较小的分离集合树作为子树，如 hA > hB，得到分离集合树 C 的高度 hC = MAX{ hA, hB + 1 }
		// 为此给每个结点增加一个 秩（rank）域，为一个近似子树高度的正整数，同时也是该结点高度的一个上限
		
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

	} // END namespace _7_9 用并查集求解等价问题

} // END namespace dst 数据结构教程

#endif // !DST_7_TREE_BINARY_TREE_H