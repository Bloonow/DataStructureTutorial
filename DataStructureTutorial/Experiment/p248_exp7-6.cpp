// Author：Akame Qisixi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_7_TREE_BINARY_TREE_H
#include "dst_7_tree_binary_tree.h"
#endif // DST_7_TREE_BINARY_TREE_H

// 上机实验题7
// P248 实验题6：求二叉树中的结点个数、叶子结点个数、某结点层次和二叉树宽度
// 目的：掌握二叉树遍历算法的应用，熟悉使用先序、中序、后序3种递归遍历算法和层次遍历算法进行二叉树问题的求解
// 内容：编写一个程序exp7-6.cpp实现以下功能，并对图7.33所示的二叉树进行验证
// (1)、输出二叉树b的结点个数
// (2)、输出二叉树b的叶子结点个数
// (3)、求二叉树b中指定结点值（假设所有结点的值不同）的结点的层次
// (4)、利用层次遍历求二叉树b的宽度
// 最后修改：2019-12-03
namespace experiment_7_6 {

	using dst::_7_3::_7_3_2::BTNode;
	using dst::_7_3::_7_3_2::ElemType;

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

	// 二叉树采用二叉链存储，求所有结点个数
	int Nodes(BTNode* b) {
		if (b == NULL) {
			return 0;
		} else {
			return Nodes(b->lchild) + Nodes(b->rchild) + 1;
		}
	}

	// 二叉树采用二叉链存储，输出所有叶子结点
	int LeafNodes(BTNode* b) {
		if (b != NULL) {
			if (b->lchild == NULL && b->rchild == NULL) {
				return 1;
			}
			return LeafNodes(b->lchild) + LeafNodes(b->rchild);
		}
		return 0;
	}

	// 二叉树采用二叉链存储，求值为x的结点在树中的层次
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

	// 层次遍历较为简单
	// 先将根结点进队，队不为空时循环，若有左孩子则进队，有右孩子则进队，如此操作直到队空
	int LevelOrderForWidth(BTNode* b) {
		typedef struct {
		BTNode* bt;
		int level;
		} QuNode;  // 队列中元素的类型，为确定树中结点的层次，在其中加入了 level 域
		int curLevel = 1;
		int curLevelWidth = 0;
		int maxLevelWidth = 0;
		QuNode* sub;
		QuNode* p = (QuNode*)malloc(sizeof(QuNode));
		p->bt = b;
		p->level = curLevel;
		dep::Queue<QuNode*>* qu;
		InitQueue(qu);
		enQueue(qu, p);
		while (!QueueEmpty(qu)) {
			deQueue(qu, p);
			// 若当前层次已经改变，更新相应数据
			if (p->level != curLevel) {
				curLevel = p->level;
				if (maxLevelWidth < curLevelWidth) {
					maxLevelWidth = curLevelWidth;
				}
				curLevelWidth = 1;
			} else {
				// 当前结点与上一结点在同一层次，当前层次宽度增1
				++curLevelWidth;
			}
			if (p->bt->lchild != NULL) {
				sub = (QuNode*)malloc(sizeof(QuNode));
				sub->bt = p->bt->lchild;
				sub->level = p->level + 1;
				enQueue(qu, sub);
			}
			if (p->bt->rchild != NULL) {
				sub = (QuNode*)malloc(sizeof(QuNode));
				sub->bt = p->bt->rchild;
				sub->level = p->level + 1;
				enQueue(qu, sub);
			}
		}
		if (maxLevelWidth < curLevelWidth) {
					maxLevelWidth = curLevelWidth;
		}
		DestroyQueue(qu);
		return maxLevelWidth;
	}

	void exp7_6() {
		BTNode* bt;
		char* btStr = const_cast<char*>("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
		dst::_7_4::CreateBTree(bt, btStr);
		printf("二叉树如下：\n");
		dst::_7_4::DispBTree(bt);
		
		printf("\n(1)、输出二叉树b的结点个数: %d\n", Nodes(bt));
		printf("(2)、输出二叉树b的叶子结点个数: %d\n", LeafNodes(bt));
		printf("(3)、求二叉树b中指定结点值的结点的层次，如结点 %c 的层次为 %d \n", 'N', Level(bt, 'N', 1));
		printf("(4)、利用层次遍历求二叉树b的宽度: %d\n", LevelOrderForWidth(bt));

		dst::_7_4::DstroyBTree(bt);
	}

} // END namespace experiment_7_6