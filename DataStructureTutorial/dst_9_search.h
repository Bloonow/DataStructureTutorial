// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_9SEARCH_H
#define DST_9SEARCH_H

// 第九章：查找

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 9.1 查找（search）的基本概念
	// 最后修改：2019-12-03
	namespace _9_1 {
		// 被查找的对象是由一组元素（或记录）组成的表或文件，每个元素由若干数据项组成，其中指定一个数据项为关键字（key）（取值唯一）
		// 查找（search）就是给定一个元素 e 或值 k，在含有 n 个元素的表中找出关键字等于 e.key 或 k 的元素
		// 若在查找的同时对表做修改操作（如插入或删除）则称为 动态查找表（dynamic search table）；反之为 静态查找表（static search table）
		// 若整个查找过程都在内存中进行，则称为 内查找（internal search）；若需访问外存，则称为 外查找（external search）
		// 在查找中时间主要花费在关键字比较上，把平均需要和给定值进行比较的关键字次数称为平均查找长度（Average Search Length，ASL）
		// ASL = ∑[i=1..n](pi * ci)
		// 其中，n 是查找元素的个数；其中 pi 是查找第 i 个元素的概率，通常假设每个元素查找的概率相等为 1/n；其中 ci 是找到第 i 个元素所需的关键字比较次数
		// ASL 分为查找成功情况下的 ASL(ok) 和查找不成功（失败）情况下的 ASL(fault)

	} // END namespace _9_1 查找的基本概念

	// 9.2 线性表的查找
	// 顺序查找（sequential search）、折半查找（binary search）、分块查找（block search）
	// 最后修改：2019-12-03
	namespace _9_2 {
		// 查找与数据的存储结构有关，线性表有顺序表和链式两种存储结构，这里只介绍以顺序表作为存储结构的算法，顺序表属于静态查找表
		// 查找成功返回找到的元素的逻辑序号，失败时返回 0
		// 为了算法通用，用于查找运算的顺序表采用数组表示，该数组元素的类型声明如下：
		typedef int KeyType;    // 关键字类型
		//typedef int InfoTyoe;    // 其他数据项类型
		typedef struct {
			KeyType key;
			//InfoTyoe data;
		} RecType;    // 查找元素的类型

		// 9.2.1 顺序查找（sequential search）
		// 最后修改：2019-12-03
		namespace _9_2_1 {
			//顺序查找
			// O(n)，ASL = (n + 1) / 2
			int SeqSearch(RecType R[], int n, KeyType k) {
				int i;
				for (i = 0; i < n && R[i].key != k; ++i);    // 从表头往后找
				return i >= n ? 0 : i + 1;    // 未找到返回0，找到返回逻辑序号
			}

			// 因为是顺序的，所以第 i 个元素需要比较 i 次，即 ci = i
			// ASL = ∑[i=1..n](pi * ci) = (1/n) * ∑[i=1..n](i) = (1/n) * n(n+1) / 2 = (n+1) / 2

			// 顺序查找，在 R 的末尾增加一个关键字为 k 的记录，称之为哨兵，这样查找过程不再需要判断 i 是否越界，从而提高查找速度
			int SeqSearch1(RecType R[], int n, KeyType k) {
				R[n].key = k;
				int i;
				for (i = 0; R[i].key != k; ++i);
				return i == n ? 0 : i + 1;
			}

		} // END namespace _9_2_1 顺序查找

		// 9.2.2 折半查找（binary search）
		// 最后修改:2019-12-03
		namespace _9_2_2 {
			// 折半查找又称为二分查找，要求表为有序表，此处假设有序表是递增有序的
			// 基本思路：设 R[lowIndex...highIndex] 是当前查找区间，确定中间位置 mid = ⌊(lowIndex+highIndex) / 2⌋，比较 k 和 R[mid].key
			// 若 k == R[mid].key，则说明查找成功，返回该元素逻辑序号
			// 若 k < R[mid].key，说明要查找元素还在mid左侧，故令 highIndex = mid - 1，更新当前查找区间
			// 若 k > R[mid].key，说明要查找元素还在mid右侧，故令 lowIndex = mid + 1，更新当前查找区间
			// O(log2(n))，ASL = log2(n + 1) - 1
			int BinSearch(RecType R[], int n, KeyType k) {
				int lowIndex = 0, highIndex = n - 1, mid;
				// 当前区间存在元素时循环
				while (lowIndex <= highIndex) {
					mid = (lowIndex + highIndex) / 2;
					if (k == R[mid].key) {
						return mid + 1;    // 查找成功返回逻辑序号
					} else if (k < R[mid].key) {
						highIndex = mid - 1;
					} else {
						lowIndex = mid + 1;
					}
				}
				return 0;
			}

			// 折半查找的过程可用二叉树来描述，把当前查找区间的中间位置上的元素作为根，有左子表和右子表构造的的二叉树分别作为根的左子树和右子树
			// 由此得到的二叉树称为描述折半查找过程的判定树（decision tree）或比较树（comparsion tree）
			// 判定树中查找成功对应的结点称为内部结点，而查找失败对应的结点称为外部结点
			// 折半查找判定树的形态只与表元素个数 n 相关，而与输入实例中的 key 取值无关
			// 判定树高度近似为 h = log2(n+1)，树中第 i 层上的结点个数为 2^(i-1)，查找该层上的每个结点恰好需要进行 i 次比较
			// ASL = ∑[i=1..n](pi * ci) = (1/n) * ∑[i=1..h](2^(i-1) * i) = ((n+1) / n) * log2(n+1) - 1 ≈ log2(n+1) - 1

		} // END namespace _9_2_2 折半查找

		// 9.2.3 索引存储结构和分块查找
		// 最后修改:2019-12-03
		namespace _9_2_3 {
			// 9.2.3.1 索引存储结构（index storage structure）是在存储数据的同时还建立附加的索引表
			// 索引表的每一项称为索引项，其一般形式为（关键字，地址）
			// 其中，关键字唯一标识一个结点，地址作为指向该关键字对应结点的指针（也可以是相对地址，如数组下标）
			// 索引存储结构可以提高关键字查找元素的效率，其缺点是需要建立索引表而增加时间和空间的开销

			// 9.2.3.2 分块查找（bolck search）要求按如下索引的方式来存储线性表：
			// 将表 R[0...n-1] 均分为 b 块，每块元素个数为s = ⌈n/b⌉，最后一块可能不足 s 个元素
			// 每一块中的关键字不一定有序，但整个表应该是“分块有序”的（前一块中的最大 应小于 后一块中的最小）
			// 抽取各块中最大的关键字及该块的起始位置构成一个索引表 IDX[0...b-1]
			// IDX[i]（0 <= i <= b-1）存放着第 i+1 块的最大关键字 和 该块在R中的起始位置

			typedef struct {
				KeyType key;    // 关键字类型
				int pointIndex;    // 指向对应块的起始下标
			} IdxType;    // 索引表元素的类型

			// 分块查找：先查找索引表，因为索引表是有序表，故可采用折半查找或顺序查找，以确定待查找元素在哪一块，然后在已确定的块中顺序查找
			// 采用折半查找索引表的分块查找算法如下（索引表 I 的长度为 b）
			// ASL = log2(b+1) + s/2
			int IdxSearch(IdxType I[], int b, RecType R[], int n, KeyType k) {
				int s = (n - 1 + b) / b;    // s 为每块中的元素的个数，应为 ⌈n/b⌉
				int LI = 0, HI = b - 1, mid, index;
				while (LI <= HI) {
					mid = (LI + HI) / 2;
					if (k <= I[mid].key) {
						HI = mid - 1;
					} else {
						LI = mid + 1;
					}
				}
				index = I[HI + 1].pointIndex;    // 首先在索引表的 HI + 1 块中查找，再在主数据表中进行顺序查找
				while (index <= I[HI + 1].pointIndex + s - 1 && R[index].key != k) ++index;
				return index <= I[HI + 1].pointIndex + s - 1 ? index + 1 : 0;    // 查找成功返回逻辑序号
			}

			// 采用折半查找来确定元素所在的块：（当 s 越小时，ASL越小）
			// ASL(blk) = ASL(bn) + ASL(sq) = log2(b+1) - 1 + (s+1) / 2 = log2(b+1) + s/2
			// 采用顺序查找来确定元素所找的块：（当 s = n^(1/2)时，ASL最小为 n^(1/2) + 1)
			// ASL(blk)' = ASL(bn) + ASL(sq) = (b+1) / 2 + (s+1) / 2 = (b+s)/2 + 1

		} // END namespace _9_2_3 索引存储结构和分块查找

	} // END namespace _9_2 线性表的查找

	// 9.3 树表（tree table）的查找
	// 最后修改:2019-12-16
	namespace _9_3 {
		// 由于折半查找要求表中元素有序，且不适合链式存储的结构，因此当表的插入或删除频繁时，为维护表的有序性，需要移动大量元素，其额外的时间开销会抵消其优点
		// 若要对动态查找表进行高效率的查找，可采用特殊的二叉树/树作为表的组织形式，统称为树表（tree table）

		// 9.3.1 二叉排序树（binary search tree）
		// 最后修改：2019-12-05
		namespace _9_3_1 {
			// 二叉排序树（binary search tree，BST）又称二叉查找树或二叉搜索树，其定义为二叉搜索树或空树，或是满足以下性质（BST性质）的二叉树：
			// (1)、若根结点的左子树非空，则左子树上的所有结点的关键字均小于根结点关键字
			// (2)、若根结点的右子树非空，则右子树上的所有结点的关键字均大于根结点关键字
			// (3)、根结点的左右子树本身又各自是一个二叉搜索树
			// 按中序遍历该树得到的中序序列是一个递增有序序列
			// 注：其中关键字是唯一的，但在实际应用中，不能保证关键字的唯一性，故可将(1)修改为小于等于或将(2)修改为大于等于

			typedef int KeyType;
			typedef int InfoType;

			// 二叉搜索树的结点类型声明如下：
			typedef struct node {
				KeyType key;
				InfoType data;
				struct node *lchild, *rchild;
			} BSTNode;

			// 9.3.1.1 二叉搜索树的插入和创建

			// 二叉搜索树的插入
			// 任何结点插入到二叉搜索树中都是作为叶子结点插入的
			// 在数bt中，插入一个关键字为k的元素，若bt为空，则创建作为根结点；否则判断 bt->key 与 k，递归调用
			bool InsertBST(BSTNode*& bt, KeyType k) {
				if (bt == NULL) {
					bt = (BSTNode*)malloc(sizeof(BSTNode));
					bt->key = k;     // 创建新结点（作为叶子结点）
					bt->lchild = bt->rchild = NULL;
					return true;
				} else if (k < bt->key) {
					return InsertBST(bt->lchild, k);    // 插入到左子树中
				} else if (k > bt->key) {
					return InsertBST(bt->rchild, k);    // 插入到右子树中
				} else {
					return false;    // k == bt->key 树中存在相同关键字的结点，返回false
				}
			}

			// 创建二叉搜索树
			// 关键字序列顺序不同，生成的二叉搜索树的树形可能不同；二叉树高度越小，查找效率越高（ 接近O(log2(n)) ）
			// 从关键字数组 a[0...n-1] 生成二叉搜索树，依次调用插入算法即可
			BSTNode* CreateBST(KeyType a[], int n) {
				BSTNode* bt = NULL;
				for (int i = 0; i < n; InsertBST(bt, a[i++]));
				return bt;    // 返回创建的指向树根的二叉搜索树的指针，若数组有零个元素返回NULL
			}

			// 输出二叉搜索树（的关键字）
			void DispBSTree(BSTNode* bt) {
				if (bt != NULL) {
					// 当前结点非空，输出其表示的值
					printf("%d", bt->key);
					// 至少有一个孩子结点时
					if (bt->lchild != NULL || bt->rchild != NULL) {
						printf("(");
						DispBSTree(bt->lchild);    // 递归处理左子树
						if (bt->rchild != NULL) {
							// 如果有右孩子结点，先输出 ,
							printf(",");
						}
						DispBSTree(bt->rchild);    // 递归处理右孩子结点
						printf(")");
					}
				}
			}

			// 销毁二叉搜索树
			void DestoryBSTree(BSTNode* bt) {
				if (bt != NULL) {
					DestoryBSTree(bt->lchild);
					DestoryBSTree(bt->rchild);
					free(bt);
				}
			}

			// 9.3.1.2 二叉搜索树的查找

			// 二叉搜索树的查找
			// 和折半查找类似，也是一个逐步缩小查找范围的过程，递归算法如下：
			BSTNode* SearchBST(BSTNode* bt, KeyType k) {
				if (bt == NULL || bt->key == k) {
					return bt;
				}
				return k < bt->key ? SearchBST(bt->lchild, k) : SearchBST(bt->rchild, k);
			}

			// 二叉搜索树的查找，非递归
			BSTNode* SearchBST_nonRecursion(BSTNode* bt, KeyType k) {
				while (bt != NULL) {
					if (k < bt->key) {
						bt = bt->lchild;
					} else if (k > bt->key) {
						bt = bt->rchild;
					} else {
						return bt;    // bt->key == k
					}
				}
				return bt;    // 未找到返回 NULL
			}

			// 若不仅要找到关键字为 k 的结点，还要找到其双亲结点
			// 返回所查找的结点，用parent引用实参返回其双亲结点，调用如 (bt, k, par, NULL)
			BSTNode* SearchBST_withParent(BSTNode* bt, KeyType k, BSTNode*& parent, BSTNode* p = NULL) {
				if (bt == NULL) {
					parent = NULL;    // 未找到返回 NULL
					return NULL;
				} else if (k < bt->key) {
					return SearchBST_withParent(bt->lchild, k, parent, bt);
				} else if (k > bt->key) {
					return SearchBST_withParent(bt->rchild, k, parent, bt);
				} else {
					// k == bt->key
					parent = p;
					return bt;
				}
			}

			// 例 9.4 设计一个算法，求出二叉搜索树的左子树中最大结点和右子树中最小结点
			// 根据定义，一颗二叉搜索树，最大结点为最右下结点，最小结点为最左下结点
			void maxMinNode(BSTNode* bt) {
				if (bt != NULL) {
					BSTNode* p = bt->lchild;
					if (bt->lchild != NULL) {
						while (p->rchild != NULL) p = p->rchild;
						printf("左子树的最大结点关键字为：%d\n", p->key);
					}
					p = bt->rchild;
					if (bt->rchild != NULL) {
						while (p->lchild != NULL) p = p->lchild;
						printf("右子树的最小结点关键字为：%d\n", p->key);
					}
				}
			}

			// 基础算法，请勿显式调用
			struct _9_3_1_Base {
				// 删除二叉搜索树中的结点 t （ t != NULL ）
				static void DeleteBSTNode(BSTNode*& t) {
					BSTNode* q;
					// t 只有左子树而无右子树
					if (t->rchild == NULL) {
						q = t;
						t = t->lchild;    // 用 t 的左孩子代替 t
						free(q);
					} else if (t->lchild == NULL) {
						// t 只有右子树而无左子树
						q = t;
						t = t->rchild;    // 用 t 的右孩子代替 t
						free(q);
					} else {
						// t 既有左子树又有右子树，此处选择用 t 的左子树的最大结点代替 t，并删除该最大结点
						BSTNode** lmax = &(t->lchild);    // 此处二级指针不能用 *&
						while ((*lmax)->rchild != NULL) lmax = &((*lmax)->rchild);    // 找到左子树的最大结点
						t->key = (*lmax)->key;
						// t->data = lmax->key;
						q = *lmax;    // 删除左子树最大结点，情况(2)
						*lmax = (*lmax)->lchild;
						free(q);
					}
				}
			};

			// 9.3.1.3 二叉树搜索树的删除
			// 不能直接把该结点为根的子树都删除，只能删除该结点本身，且还要保证删除后所得的二叉树仍满足BST性质
			// 即，在二叉搜索树中删除一个结点相当于删除有序序列（即该树的中序序列）中的一个元素
			// 删除操作必须先进行查找，假设在查找结束时，p 指向要删除的结点，分为以下几种情况:
			// (1)、p 是叶子结点，直接删除
			// (2)、p 仅有左子树而无右子树，直接用 p 的左孩子替换 p（p = p->lchild）
			// (3)、p 仅有右子树而无左子树，直接用 p 的右孩子替换 p（p = p->rchild）
			// (4)、p 既有左孩子又有右孩子，用左子树中最大的结点 lmax 替换 p，并删除 lmax（ lmax的删除操作符合(2) ），即用中序前驱代替被删除结点
			//		或可以用右子树中最小节点 rmin 替换 p，并删除 rmin（ rmin的删除操作符合(3) ），即用中序后继代替被删除结点
			// 删除二叉搜索树bt中关键字为k的结点
			bool DeleteBST(BSTNode*& bt, KeyType k) {
				if (bt == NULL) {
					return false;    // 空树删除失败，返回false
				}
				if (k < bt->key) {
					return DeleteBST(bt->lchild, k);    // 递归在左子树中删除关键字为 k 的结点
				} else if (k > bt->key) {
					return DeleteBST(bt->rchild, k);    // 递归在右子树中删除关键字为 k 的结点
				} else {
					// k == bt->key，找到要删除的结点，删除之
					_9_3_1_Base::DeleteBSTNode(bt);
					return true;
				}
			}

		} // END namespace _9_3_1 二叉排序树

		// 9.3.2 平衡二叉树（balance binary tree）
		// AVL平衡二叉树（Adel'son-Vel'sii 和 Landis）
		// 最后修改：2019-12-10
		namespace _9_3_2 {
			// 含有 n 个结点的二叉搜索树查找操作最坏情况为 O(n)，其与树形有关
			// 通过在往树中插入或删除的同时调整树的形态来保持树的平衡，使之既保持BST性质又保证树的高度在任何情况下均为 log2(n)，从而使查找操作的时间复杂度也为 O(log2(n))
			// 平衡的二叉搜索树有很多种，较为著名的有 AVL树
			// 若一颗二叉树中的每个结点的左右子树的高度最多相差 1，则称此二叉树为平衡二叉树（balance binary tree）
			// 在算法中，通过平衡因子（balance factor，bf）来具体实现上述平衡二叉树的定义，其定义为：左子树的高度 - 右子树的高度（或 右-左）
			// 从平衡因子的角度讲，若 bf 取值为 -1，1，0 则该结点是平衡的，否则是不平衡的；一颗平衡二叉树的所有结点都应该是平衡的
			// 这就要求在插入或删除中，一旦某些结点在操作后不平衡，就要进行调整
			// 加一个头结点 head 标识树，默认 head->lchild 为平衡二叉树的根结点（-1 表示左孩子，0 表示没孩子，1 表示右孩子）

			typedef int KeyType;
			//typedef int InfoType;

			typedef struct avl {
				int height;    // 平衡因子，balance factor，bf = lHeight - rHeight
				KeyType key;
				//InfoType data;
				struct avl *lchild, *rchild;
			} AVLTreeNode;    // AVL平衡二叉树结点类型

			// 基础算法，请勿显式调用
			struct _9_3_2_Base {
				// 更新结点高度
				static void reNodeHeight(AVLTreeNode* node) {
					int lHeight = node->lchild == NULL ? 0 : node->lchild->height;
					int rHeight = node->rchild == NULL ? 0 : node->rchild->height;
					node->height = 1 + (lHeight > rHeight ? lHeight : rHeight);
				}

				// 计算结点平衡因子
				static int getBalanceFactor(AVLTreeNode* node) {
					int lHeight = node->lchild == NULL ? 0 : node->lchild->height;
					int rHeight = node->rchild == NULL ? 0 : node->rchild->height;
					return lHeight - rHeight;
				}

				static void adjust_LL(AVLTreeNode* A, AVLTreeNode* parent, int whichChild) {
					AVLTreeNode* B = A->lchild;
					A->lchild = B->rchild; reNodeHeight(A);
					B->rchild = A; reNodeHeight(B);
					if (whichChild == -1) {
						parent->lchild = B;
					} else if (whichChild == 1) {
						parent->rchild = B;
					}
				}

				static void adjust_RR(AVLTreeNode* A, AVLTreeNode* parent, int whichChild) {
					AVLTreeNode* B = A->rchild;
					A->rchild = B->lchild; reNodeHeight(A);
					B->lchild = A; reNodeHeight(B);
					if (whichChild == -1) {
						parent->lchild = B;
					} else if (whichChild == 1) {
						parent->rchild = B;
					}
				}

				static void adjust_LR(AVLTreeNode* A, AVLTreeNode* parent, int whichChild) {
					AVLTreeNode* B = A->lchild;
					AVLTreeNode* C = B->rchild;
					B->rchild = C->lchild; reNodeHeight(B);
					A->lchild = C->rchild; reNodeHeight(A);
					C->lchild = B; C->rchild = A; reNodeHeight(C);
					if (whichChild == -1) {
						parent->lchild = C;
					} else if (whichChild == 1) {
						parent->rchild = C;
					}
				}

				static void adjust_RL(AVLTreeNode* A, AVLTreeNode* parent, int whichChild) {
					AVLTreeNode* B = A->rchild;
					AVLTreeNode* C = B->lchild;
					A->rchild = C->lchild; reNodeHeight(A);
					B->lchild = C->rchild; reNodeHeight(B);
					C->lchild = A; C->rchild = B; reNodeHeight(C);
					if (whichChild == -1) {
						parent->lchild = C;
					} else if (whichChild == 1) {
						parent->rchild = C;
					}
				}

				// 重新平衡，at 为其根结点，若为最小失衡树则调整平衡
				static void adjustToBalance(AVLTreeNode* at, AVLTreeNode* parent, int whichChild) {
					switch (getBalanceFactor(at)) {
					case 1: case 0: case -1: break;
					case 2:
						if (getBalanceFactor(at->lchild) == -1) {
							adjust_LR(at, parent, whichChild);
						} else {
							adjust_LL(at, parent, whichChild);    // == 0 || == 1
						}
						reNodeHeight(parent);
						break;
					case -2:
						if (getBalanceFactor(at->rchild) == 1) {
							adjust_RL(at, parent, whichChild);
						} else {
							adjust_RR(at, parent, whichChild);    // == 0 || == -1
						}
						reNodeHeight(parent);
						break;
					}
				}

				// insert_base
				static bool InsertBBT_AVL_base(AVLTreeNode*& at, KeyType k, AVLTreeNode* parent, int whichChild) {
					bool inserted = false;
					if (at == NULL) {
						at = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
						at->height = 1;    // 创建结点（根结点），插入关键字
						at->lchild = at->rchild = NULL;
						at->key = k;
						inserted = true;
					} else if (k < at->key) {
						inserted = InsertBBT_AVL_base(at->lchild, k, at, -1);
					} else if (k > at->key) {
						inserted = InsertBBT_AVL_base(at->rchild, k, at, 1);
					} // else k == at->key 已存在 inserted = false;
					// 递归调用 和 递归退出 时会逐层遍历检查树的结点是否平衡并调整
					reNodeHeight(parent);
					adjustToBalance(at, parent, whichChild);
					return inserted;
				}

				// dis base
				static void DispBBTree_AVL_base(AVLTreeNode* at) {
					if (at != NULL) {
						// 当前结点非空，输出其表示的值
						printf("%d", at->key);
						// 至少有一个孩子结点时
						if (at->lchild != NULL || at->rchild != NULL) {
							printf("(");
							DispBBTree_AVL_base(at->lchild);    // 递归处理左子树
							if (at->rchild != NULL) {
								// 如果有右孩子结点，先输出 ,
								printf(",");
							}
							DispBBTree_AVL_base(at->rchild);    // 递归处理右孩子结点
							printf(")");
						}
					}
				}

				// search
				static AVLTreeNode* SearchBBT_AVL_base(AVLTreeNode* at, KeyType k) {
					if (at == NULL || at->key == k) {
						return at;
					}
					return k < at->key ? SearchBBT_AVL_base(at->lchild, k) : SearchBBT_AVL_base(at->rchild, k);
				}

				// delete the max node of left child
				static void DeleteBBTreeNode_AVL_base_Helper(AVLTreeNode* toDeleteNode, AVLTreeNode* t, AVLTreeNode *parent, int whichChild) {
					if (t->rchild != NULL) {
						DeleteBBTreeNode_AVL_base_Helper(toDeleteNode, t->rchild, t, 1);
					} else {
						toDeleteNode->key = t->key;
						if (whichChild == 1) {
							parent->rchild = t->lchild;
						} else if (whichChild == -1) {
							parent->lchild = t->lchild;
						}
						free(t);
					}
					reNodeHeight(parent);
				}

				// delete node base
				static void DeleteBBTreeNode_AVL_base(AVLTreeNode* t, AVLTreeNode* parent, int whichChild) {
					if (t->rchild == NULL) {
						// t 只有左子树而无右子树
						// 用 t 的左孩子代替 t
						if (whichChild == -1) {
							parent->lchild = t->lchild;
						} else if (whichChild == 1) {
							parent->rchild = t->lchild;
						}
						free(t);
					} else if (t->lchild == NULL) {
						// t 只有右子树而无左子树
						// 用 t 的右孩子代替 t
						if (whichChild == -1) {
							parent->lchild = t->rchild;
						} else if (whichChild == 1) {
							parent->rchild = t->rchild;
						}
						free(t);
					} else {
						// t 既有左子树又有右子树，此处选择用 t 的左子树的最大结点代替 t，并删除该最大结点
						DeleteBBTreeNode_AVL_base_Helper(t, t->lchild, t, -1);
					}
					reNodeHeight(parent);
				}

				// delete_base
				static bool DeleteBBT_AVL_base(AVLTreeNode* at, KeyType k, AVLTreeNode* parent, int whichChild) {
					bool shouldAdjust = true;
					if (at == NULL) {
						shouldAdjust = false;    // 空树删除失败
					} else {
						if (k < at->key) {
							shouldAdjust = DeleteBBT_AVL_base(at->lchild, k, at, -1);    // 递归在左子树中删除关键字为 k 的结点
						} else if (k > at->key) {
							shouldAdjust = DeleteBBT_AVL_base(at->rchild, k, at, 1);    // 递归在右子树中删除关键字为 k 的结点
						} else {
							// k == bt->key，找到要删除的结点，删除之
							DeleteBBTreeNode_AVL_base(at, parent, whichChild);
							shouldAdjust = false;
						}
					}
					if (shouldAdjust) {
						reNodeHeight(parent);
						adjustToBalance(at, parent, whichChild);
					}
					return true;
				}

			};

			// 9.3.2.1 平衡二叉树中插入结点的过程
			// 若向平衡二叉树中插入一个新结点（总是作为叶子结点插入）后破坏了平衡性，应从该新结点向根结点的方向查找第一个失去平衡的 结点A
			// 刚刚查找过的与A相邻的 结点B，以 A 和 B 结点为根结的两棵子树，构成调整子树
			// 失衡的最小子树是指以离新结点最近的，且平衡因子绝对值大于1的结点为根结点的子树，即 A子树
			// 调整分为以下4种情况：LL型，RR型，LR型，RL型
			// (1)、LL型调整：
			// 因 A结点 的 左孩子B结点 的左子树上插入新结点，使得 A->bf 不平衡：1 => 2
			// 令 C 为 B->rchild，将 B 上升代替 A 称为根结点，A 作为 B 的右孩子，C 作为 A 的左孩子
			// (2)、RR型调整：
			// 因 A结点 的 右孩子B结点 的右子树上插入新结点，使得 A->bf 不平衡：-1 => -2
			// 令 C 为 B->lchild，将 B 上升代替 A 作为根结点，A 作为 B 的左孩子，C 作为 A 的右孩子
			// (3)、LR型调整：
			// 因 A结点 的 左孩子B结点 的右子树上插入新结点，使得 A->bf 不平衡：1 => 2
			// 令 C 为 B->rchild，将 C 上升代替 A 作为根结点，C->lchild 作为 B 的右孩子，C->rchild 作为 A 的左孩子，B 作为 C 的左孩子，A 作为 C 的右孩子
			// (4)、RL型调整：
			// 因 A结点 的 右孩子B结点 的左子树上插入新结点，使得 A->bf 不平衡：-1 => -2
			// 令 C 为 B->lchild，将 C 上升代替 A 作为根结点，C->lchild 作为 A 的右孩子，C->rchild 作为 B 的左孩子，A 作为 C 的左孩子，B 作为 C 的右孩子

			// 平衡二叉树的插入
			// 任何结点插入到平衡二叉树中都是作为叶子结点插入的
			// 在数bt中，插入一个关键字为k的元素，若bt为空，则创建作为根结点，并调整树形；否则判断 bt->key 与 k，递归调用
			void InsertBBT_AVL(AVLTreeNode* head, KeyType k) {
				_9_3_2_Base::InsertBBT_AVL_base(head->lchild, k, head, -1);    // 默认头结点的左孩子连接二叉树的根结点，右孩子为空
			}

			// 创建平衡二叉树
			AVLTreeNode* CreateBBT_AVL(KeyType K[], int n) {
				AVLTreeNode* head = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
				head->height = 0;
				head->lchild = head->rchild = NULL;
				for (int i = 0; i < n; ++i) {
					_9_3_2_Base::InsertBBT_AVL_base(head->lchild, K[i], head, -1);
				}
				return head;
			}

			// 输出平衡二叉树（的关键字）
			void DispBBTree_AVL(AVLTreeNode* head) {
				_9_3_2_Base::DispBBTree_AVL_base(head->lchild);
			}

			// 销毁平衡二叉树
			void DestoryBBTree_AVL(AVLTreeNode* head) {
				if (head != NULL) {
					DestoryBBTree_AVL(head->lchild);
					DestoryBBTree_AVL(head->rchild);
					free(head);
				}
			}

			// 9.3.2.2 平衡二叉树中删除结点的过程
			// 在平衡二叉树中删除一个结点与二叉搜索树中删除结点类似，只是增加了调整这一步，其过程如下：
			// (1)、查找，先在平衡二叉树中查找关键字为 k 的元素
			// (2)、删除 结点p，分为三种情况：
			//		1、叶子结点，直接删除
			//		2、单分支结点，用 p 的左孩子或右孩子代替结点 p
			//		3、双分支结点，用 p 的中序前驱（后中序后继）的结点 q 代替结点 p，再删除结点 q
			// (3)、调整，若被删除的是结点 p，则从结点 p 向根结点的方向查找第一个失衡结点：
			//		1、若所有结点都是平衡的，则无需调整
			//		2、若某个结点平衡因子为 -2（R）：右孩子平衡因子为 1（RL），否则可为 RR
			//		3、若某个结点平衡因子为 2（L）：左孩子平衡因子为 -1（LR），否则可为 LL
			bool DeleteBBT_AVL(AVLTreeNode* head, KeyType k) {
				return _9_3_2_Base::DeleteBBT_AVL_base(head->lchild, k, head, -1);
			}


			// 9.3.2.3 平衡二叉树的查找
			// 其过程和二叉搜索树的查找过程完全相同，而且由于其树形被约束，故平衡二叉树的最大高度 h 约等于 log2(n)
			// 则其平均查找长度为 AVL = log2(n)，算法时间复杂度为 O(log2(n))
			// 和折半查找类似，也是一个逐步缩小查找范围的过程，递归算法如下：
			AVLTreeNode* SearchBBT_AVL(AVLTreeNode* head, KeyType k) {
				return _9_3_2_Base::SearchBBT_AVL_base(head->lchild, k);
			}

			// 平衡二叉树的查找，非递归
			AVLTreeNode* SearchBBT_AVL_nonRecursion(AVLTreeNode* head, KeyType k) {
				AVLTreeNode* at = head->lchild;
				while (at != NULL) {
					if (k < at->key) {
						at = at->lchild;
					} else if (k > at->key) {
						at = at->rchild;
					} else {
						return at;    // bt->key == k
					}
				}
				return at;    // 未找到返回 NULL
			}
			
			// test.c for 9.3.2
			namespace _9_3_2_test {
				void test() {
					KeyType K[] = { 16,3,7,11,9,26,18,14,15 };
					//KeyType KK[] = { 9,7,8,10,12,13,17,18,19,15 };
					AVLTreeNode* head = CreateBBT_AVL(K, 9);
					printf("Balance Binary Tree instanced by AVL\n");
					DispBBTree_AVL(head);
					printf("\nDelete the nodes of 3 and 9\n");
					DeleteBBT_AVL(head, 3);
					DeleteBBT_AVL(head, 9);
					DeleteBBT_AVL(head, 9);
					DispBBTree_AVL(head);
					printf("\n");
				}
			} // END namespace _9_3_2_test

		} // END namespace _9_3_2 平衡二叉树

		// 9.3.3 B-树（B tree）
		// 仅参考，无法实际使用
		// 最后修改：2019-12-15
		namespace _9_3_3 {
			// 二叉排序树和平衡二叉树都是作用于内查找的数据结构，即被查找的数据集不大，可以存放在内存中
			// 此处和之后介绍的 B-树（又称为 B树） 和 B+树 是用作外查找的数据结构，其数据存放在外村中
			
			// B-树中所有结点的孩子结点个数的最大值称为B-树的阶，通常用 m 表示，从查找效率考虑，要求 m >= 3
			// 一棵树是B-树或是一棵空树，或者是满足下列要求的 m 叉树：
			// (1)、树中的每个结点最多有 m 棵子树（即最多含有 m-1 个关键字，设 MaxKeyNum = m - 1）
			// (2)、若根结点不是叶子结点，则根结点最少有两棵子树
			// (3)、除根结点外，所有非叶子结点最少有 ⌈m/2⌉ 棵子树（即最少含有 ⌈m/2⌉ - 1 个关键字，设 MinKeyNum = ⌈m/2⌉ - 1
			// (4)、每个结点（含有n个关键字，n+1个子树）的结构为：| n | c0 | k1 | c1 | k2 | c2 | ... | kn | cn |
			//		其中，除根结点外，所有其它结点的关键字个数 n 满足：⌈m/2⌉ - 1 <= n <= m - 1，即 MinKeyNum <= n <= MaxKeyNum
			//		ki（1 <= i <= n）为该结点的关键字且满足：ki < k(i+1)；
			//		ci（0 <= i <= n）为该结点的孩子结点指针，满足：c0结点任意关键字 < k1 < c1所指孩子结点任意关键字 < ... < ki < AllValue(ci) < k(i+1) < ... < AllValue(cn)
			// (5)、所有的外部结点在同一层，并且不带信息（可以看作是查找失败的结点），通常在计算一个B-树的高度时也将外部结点计入一层
			//		显然，如果一颗B-树中共有n个关键字，则外部结点的个数为 n + 1

			const int MAXM = 10;    // 定义B-树的最大阶数
			// 在B-树的存储结构中，结点的声明类型如下：
			typedef int KeyType;
			typedef struct node {
				int keyNum;    // 结点当前拥有的关键字的个数 n
				KeyType keys[MAXM];    // keys[1...keyNum] 存放关键字，keys[0] 不用
				struct node* parent;    // 双亲结点指针
				struct node* childs[MAXM];    // 指向孩子结点指针的数组 childs[0...keyNum]
			} BTNode;    // B-树（B树）的结点类型

			// 此处教材采用了全局变量（就此只能同时存在一棵B-树），为防止污染全局空间，将其实现为 struct 作用域内变量，请勿显式修改
			struct _9_3_3_Base {
				static int m;    // B-树的阶
				static int MaxKeyNum;    // m 阶 B-树 中每个结点最多的关键字个数，MaxKeyNum = m - 1
				static int MinKeyNum;    // m 阶 B-树 中每个结点最少的关键字个数，MinKeyNum = ⌈m/2⌉ - 1
				static void set(int parM) {
					m = parM;
					MaxKeyNum = m - 1;
					MinKeyNum = ((m - 1) / 2 + 1) - 1;    // ⌈m/2⌉ - 1
				}
			};
			int _9_3_3_Base::m = MAXM;
			int _9_3_3_Base::MaxKeyNum = _9_3_3_Base::m - 1;
			int _9_3_3_Base::MinKeyNum = ((_9_3_3_Base::m - 1) / 2 + 1) - 1;

			// 9.3.3.1 B-树的查找
			// 在B-树中查找给定关键字的方法类似于二叉搜索树上的查找，不同的是在每个结点上的向下查找路径不一定是二路的，而是 n + 1 路的
			// 因为结点内的关键字序列 keys[1...n] 是有序的，故既可以采用顺序查找也可以采用折半查找
			// 在一棵B-树上查找关键字为 k 的方法为：将 k 与 根结点中的 keys[i]（1 <= i <= n）比较：
			// (1)、若 k < keys[1]，则沿着指针 childs[0] 所指的子树继续查找
			// (2)、若 k == keys[i]，则查找成功
			// (3)、若 keys[i] < k < keys[i+1]，则沿着指针 childs[i] 所指的子树继续查找
			// (4)、若 keys[n] < k，则沿着指针 childs[n] 所指的子树继续查找
			// 重复上述过程，直到找到含有关键字 k 的某个结点 或 一直比较到了某个外部结点表示查找失败
			// 在B-树中进行查找时，其查找时间主要花费在搜索结点上，即主要取决于B-树的高度，第 i 层的最少结点的个数 minNodeNum 为 ：
			// minNodeNum(0) = 1，minNodeNum(1) = 2，minNodeNum(3) = 2 * ⌈m/2⌉^1，...，minNodeNum(h+1) = 2 * ⌈m/2⌉^(h-1)
			// 假设 m 阶 B-树的高度为 h + 1（第h+1层为外部结点），而当前树中含有 n 个关键字，外部结点为 n + 1 个，由此推得：
			// n + 1 >= minNodeNum(h+1) = 2 * ⌈m/2⌉^(h-1)，所以 h <= log(⌈m/2⌉)((n+1) / 2) + 1
			// 因此在含 n 个关键字的B-树上进行查找需访问的结点个数不超过 h 个，即B-树的查找算法的时间复杂度为 O(log(m)(n))

			// 9.3.3.2 B-树的插入
			// (1)、利用前述的B-树查找算法找出关键字 k 的插入结点ci（B-树的插入结点一定是某个叶子结点）
			// (2)、在插入结点中插入关键字 k，判断插入结点是否还有空位置，即判断该结点的关键字个数是否小于等于 MaxKeyNum，分两种情况
			//	1、若该结点还有空位置（keyNum < MaxKeyNum），直接把关键字插入到该结点的合适位置上（即使插入后的关键字序列仍保持有序）
			//	2、若该结点无空位置（keyNum == MaxKeyNum），需要将该结点分裂，将原结点上的 keyNum 个关键字和 新关键字 k 合成一个新序列，并使之有序
			//	   将新序列从中间（在⌈m/2⌉处，且两部分都不包含⌈m/2⌉处的关键字）分为左右两部分，左为 1 ... ⌈m/2⌉-1 放入到旧结点中
			//	   右为 ⌈m/2⌉+1 ... m 放入到新生成的新结点中，将中间位置的关键字和新结点插入到双亲结点中
			//	   （放在该插入结点的右边，即|ki|ci|k(i+1)|c(i+1)|的i+1处，k(i+1) = 中间结点的关键字，c(i+1)指向新结点，注意序列后移一位）
			//	   如果双亲结点的关键字个数也超过MaxKeyNum，则需要再分裂双亲结点，再往上插，直到这个过程传递到根结点为止，如果根结点需要分裂，则树的高度增加一层
			// 一棵B-树的创建过程就是从一棵空树开始，逐个插入关键字而得到的

			// 9.3.3.3 B-树的删除
			// (1)、利用前述的B-树查找算法找出该关键字 k 所在的结点，称为删除结点 ci
			// (2)、删除结点分为两种情况，一种是属于叶子层的结点，另一种是属于非叶子结点层的结点
			// (3)、当删除结点是非叶子结点层的结点时，假设要删除某个非叶子结点的关键字 k = keys[i]，其删除过程是：
			//		用该结点的 childs[i-1] 所指子树中的最大关键字 Max(key) 来代替被删除关键字 keys[i]（注意childs[i-1]所指子树中的最大关键字 Max(key) 一定在叶子结点上）
			//		然后再删除 Max(key)，这样就把在非叶子结点上删除关键字 k 的问题转换成了 在叶子结点上删除关键字 Max(key) 的问题
			//		也可以用删除结点的 childs[i] 所指子树的最小关键字 Min(key) 来代替 keys[i]，然后再删除 Min(key)
			// (4)、在某个叶子结点中删除关键字 k，共有以下三种情况：
			//	1、若删除结点的关键字个数 KeyNum > MinKeyNum，说明删去该关键字后该结点仍满足B-树的定义，则可以直接删除该关键字
			//	2、若删除结点的关键字个数 KeyNum == MinKeyNum，先删除这个关键字，该结点不再满足B-树的定义
			//	   此时若该结点的左（或右）兄弟结点（如果存在）中的关键字个数 KeyNum_L_or_R > MinKeyNum，则把该结点的左（或右）兄弟结点中最大（或最小）的关键字上移到双亲结点中
			//	   同时把双亲结点中的大于（或小于）刚刚上移的关键字的那个关键字下移到删除结点中做关键字，即双亲结点中的原ki（或k(i+1)）下降，并用ci的兄弟结点中的相应关键字替换之
			//	3、若删除结点的关键字个数 KeyNum == MinKeyNum，先删除这个关键字，该结点不再满足B-树的定义
			//	   且该删除结点的兄弟结点（如果存在）中的关键字的个数均为MinKeyNum，这时需要将结点合并
			//	   把删除结点与其左（或右）兄弟结点以及双亲结点中分割二者的关键字合并成一个结点
			//	   如果因此使双亲结点中的关键字个数 KeyNum < MinKeyNum，则对双亲结点做同样的处理，以至于可能直到对根结点做这样的处理而使整个树减少一层

		} // END namespace _9_3_3 B-树

		// 9.3.4 B+树（B+ tree）
		// 最后修改：2019-12-16
		namespace _9_3_4 {
			// 在索引文件组织中经常使用B-树的一些变形，其中B+树是一种应用广泛的变形
			// 一棵 m 阶的 B+树 满足下列条件：
			// (1)、每个分支最多有 m 棵子树
			// (2)、根结点或者没有子树，或者最少有两颗子树
			// (3)、除根结点以外，其他每个分支结点最少有 ⌈m/2⌉ 棵子树
			// (4)、有 n 棵子树的结点有 n 个关键字
			// (5)、所有的叶子结点包含全部的关键字及指向相应记录的指针，而且叶子结点按关键字大小顺序链接（可以把每个叶子结点看成是一个基本索引块，
			//		它的指针不再指向另一级索引块，而是直接指向数据文件中的记录）
			// (6)、所有的分支结点（可以看成是索引的索引）中仅包含它的各个子结点（即下级索引的索引块）中的最大关键字及指向子结点的指针
			
			// 通常在B+树上有两个头指针，一个指向根结点（如root），另一个指向关键字最小的叶子结点（如sqt）
			// 注意：m 阶的 B+树 和 m 阶的 B-树 的主要差异如下：
			// (1)、在B+树中，具有 n 个关键字的结点含有 n 棵子树，即每个关键字对应一颗子树；
			//		而在B-树中，具有 n 个关键字的结点含有 (n+1) 棵子树
			// (2)、在B+树中，除根结点外，每个结点中的关键字的个数 n 的取值为 ⌈m/2⌉ <= n <= m，根结点 n 的取值为 2 <= n <= m；
			//		而在B-树中，除根结点外，所有非叶子结点的关键字个数 n 的取值为 ⌈m/2⌉ - 1 <= n <= m - 1，根结点 n 的取值为 1 <= n <= m-1
			// (3)、在B+树中，所有的叶子结点包含了全部的关键字，即其他非叶子结点中的关键字索引到叶子结点中的关键字
			//		而在B-树中，所有的关键字都是不重复的
			// (4)、在B+树中，所有的非叶子结点仅起到索引作用，即结点中的每个索引项只含有对应子树的最大关键字和指向该子树的指针，不含有该关键字对应的记录的存储地址
			//		而在B-树中，每个关键字都对应一个记录的存储地址
			// (5)、在B+树中，通常有两个头指针，一个指向根结点，另一个指向关键字中最小的叶子结点，所有的叶子结点链接成一个不定长的线性链表，故B+树可以进行随机和顺序查找
			//		而在B-树中，只能进行随即查找

			// 9.3.4.1 B+树的查找
			// 在B+树中可以采用两种方式查找，一种是直接从最小关键字开始进行顺序查找（通过sqt指针查找）
			// 另一种是从B+树的根结点进行随机查找（通过root指针查找），这种方式与B-树的查找方法相似，
			// 只是在分支结点上的关键字和查找值相等时查找并不结束，要继续查找到叶子节点为止，此时若查找成功，则按所给指针取出对应元素即可
			// 因此，在B+树中不管查找成功与否，每次查找都是经过了一条从根结点到叶子结点的路径

			// 9.3.4.2 B+树的插入
			// 与B-树的插入操作相似，B+树的插入也是在叶子结点中进行的
			// 当插入后结点中的关键字个数大于 m 时要分裂成两个结点，它们所含的关键字的个数分别为 ⌈(m+1)/2⌉ 和 ⌊(m+1)/2⌋
			// 同时要使得它们的双亲结点中包含有这两个结点的最大关键字索引和指向它们的指针
			// 若双亲结点的关键字个数大于 m，应继续分裂，以此类推

			// 9.3.4.3 B+树的删除
			// B+树的删除也是在叶子结点中进行的，当叶子结点中的最大关键字被删除时，分支结点中的值可以作为“分界关键字”存在（注意同步双亲结点中的关键字）
			// 若因删除操作使结点中的关键字个数少于 ⌈m/2⌉，则从兄弟节点中调剂关键字或和兄弟结点合并，其过程和B-树相似

		} // END namespace _9_3_4 B+树

	} // END namespace _9_3 树表的查找

	// 9.4 哈希表（hash table）的查找
	// 最后修改：2019-12-15
	namespace _9_4 {
		// 9.4.1 哈希表的概念
		// 哈希表（hash table）又称散列表，设要存储的元素个数为 n，设置一个长度为 m（m >= n）的连续内存空间，以每个关键字 ki（0 <= i <= n-1）为自变量
		// 通过一个称为哈希函数（hash function）的函数 h(ki) 把 ki 映射为内存单元的地址（或下标)，并把该元素存储在这个内存单元中
		// h(ki) 也成为哈希地址（hash address），如此构造的线性存储结构称为哈希表
		// 在构建过程中，若出现两个不相同的元素 ki != kj（i != j），但 ki == kj 的情况，称为哈希冲突（hash collisions），这两个元素通常称为同义词（synonym）
		// 通常的实际情况是关键字的取值区间远大于哈希地址的变化区间

		// 哈希查找的性能主要与3个因素有关：
		// (1)、装填因子（load factor）α ，即哈希表中已存入的元素数 n 与哈希地址空间大小 m 的比值，即 a = n / m
		//		α 越小，冲突的可能性越小，存储空间的利用率也越低，通常使最终的 α 控制在 0.6 ~ 0.9 之间
		// (2)、所采用的哈希函数
		// (3)、解决哈希冲突的方法

		// 9.4.2 哈希函数的构造方法
		// 哈希地址应尽可能均匀地分布在 m 个连续的内存单元上，同时使计算过程尽可能简单以达到尽可能高的时间效率
		// 此处讨论几处常用的整数类型关键字的哈希函数构造方法
		// 1、直接定址法：h(k) = k + C
		// 2、除留余数法：h(k) = k mod p（mod 为求余运算，p <= m），理论研究表明，p 取不大于 m 的素数时效果最好
		// 3、数字分析法：提取关键字中取值较平均的数字作为哈希地址
		// etc、平方取中法、折叠法

		// 9.4.3 哈希冲突的解决方法
		// (1)、开放定址法（open addressing）：在出现哈希冲突时在哈希表中找一个新的空闲位置存放元素
		//		1、线性探测法（linear probing）：从发生冲突的地址（设为d0）开始，依次探测 d0 的下一个地址（到表尾时转到表首），直到找到一个空闲单元为止（m >= n 时一定能找到）
		//		   数学递推描述公式：d0 = h(k)，di = ( d(i-1) + 1 ) mod m（1 <= i <= m-1），容易产生堆积问题
		//		2、平方探测法（square probing）：探测序列为 d0 + 1^2， d0 - 1^2，d0 + 2^2，d0 - 2^2，...
		//		   数学递推描述公式：d0 = h(k)，di = (d0 +- i^2) mod m（1 <= i <= m-1），避免出现堆积问题，不一定能探测到哈希表上的所有单元（但最少一半）
		//		etc、伪随机序列法、双哈希函数法
		// (2)、拉链法（chaining）：把所有的同义词用单链表链接起来，地址为 i 的单元是一个指向对应单链表首结点的指针
		//		在这种方法中，哈希表中的每个单元存放的不再是元素本身，而是相应同义词单链表的指向首结点的指针

		// 9.4.4 哈希表的运算算法
		// 哈希表的常见运算有插入及建表、删除和查找等（为了简便，算法中假设每个元素仅含有关键字）

		// 9.4.4.1 用开放地址法构造的哈希表运算算法
		// 哈希函数：除留余数法，解决冲突的方法：线性探测法
		// 仅参考，无法实际使用
		// 最后修改：2019-12-15
		namespace _9_4_4_1 {
			// 此处教材采用了全局变量（就此只能同时存在一个 hash 表），为防止污染全局空间，将其实现为 struct 作用域内变量，请勿显式修改
			struct _9_4_4_1_Base {
				static int m;    // 表示哈希表的容量
				static int p;    // 除留余数法中的被除数 p，最好为不大于 m 的最大素数
				static void set(int parM, int parP) {
					m = parM;
					p = parP;
				}
			};
			int _9_4_4_1_Base::m = 50;    // m 默认为 50
			int _9_4_4_1_Base::p = 47;    // 不大于 50 的最大素数

			const int NULLKEY = -1;    // 定义空关键字类型，由此可见关键字不为负数
			const int DELKEY = -2;    // 定义被删除的关键字值
			typedef int KeyType;    // 关键字类型
			typedef struct {
				KeyType key;    // 关键字
				int probeCount;    // 探测次数
			} HashTable;    // 哈希表单元类型，创建数组是务必保证长度大于 m

			// 插入算法
			// 求出关键字 k 的哈希地址 adr，若该位置可以直接放置（即 adr 位置的关键字为 NULLKEY 或 DELKEY），将其放入
			// 否则出现冲突，采用线性探测法在表中找到一个开放地址，将 k 插入
			void InsertHT(HashTable ha[], KeyType k) {
				int adr = k % _9_4_4_1_Base::p;    // 计算哈希地址，除留余数法
				if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY) {
					ha[adr].key = k;    // k 可以直接放在哈希表中
					ha[adr].probeCount = 1;
				} else {
					// 发生冲突时采用线性探测法解决冲突，用 count 记录发生冲突的次数，也是探测的次数
					int count = 1;
					do {
						adr = (adr + 1) % _9_4_4_1_Base::m;    // 线性探测
						++count;
					} while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);

					// 探测结束，插入 k
					ha[adr].key = k;
					ha[adr].probeCount = count;
				}
			}

			// 建表算法
			// 首先将表中各元素的关键字清空，使其地址为开放的，然后调用插入算法来插入 n 个关键字的序列
			// 务必保证 HashTable 数组长度大于等于 m
			void CreateHT(HashTable ha[], KeyType keys[], int n) {
				for (int i = 0; i < _9_4_4_1_Base::m; ++i) {
					ha[i].key = NULLKEY;    // 初始哈希表
					ha[i].probeCount = 0;
				}
				for (int i = 0; i < n; InsertHT(ha, keys[i++]));
			}

			// 删除算法
			// 不能简单地将被删除元素的空间置为空，否则将截断在它之后填入哈希表的同义词的查找路径
			// 因为在开放地址法中，空地址单元都是查找失败的条件，因此只能在被删除元素上做删除标记 DELKEY
			bool DeleteHT(HashTable ha[], KeyType k) {
				int adr = k % _9_4_4_1_Base::p;
				while (ha[adr].key != k && ha[adr].key != NULLKEY) adr = (adr + 1) % _9_4_4_1_Base::m;    // 线性探测
				if (ha[adr].key == k) {
					// 查找成功，删除关键字 k
					ha[adr].key = DELKEY;
					return true;
				}
				return false;    // 查找失败，返回 false
			}

			// 查找算法
			// 先计算出哈希地址，若地址上元素不为 k 且不为空，线性探测，直到某个地址为空（查找失败）或关键字比较相等（查找成功）
			void SearchHT(HashTable ha[], KeyType k) {
				int count = 1;    // 比较次数
				int adr = k % _9_4_4_1_Base::p;
				while (ha[adr].key != k && ha[adr].key != NULLKEY) {
					++count;    // 累计关键字的比较此数
					adr = (adr + 1) % _9_4_4_1_Base::m;    // 线性探测
				}
				if (ha[adr].key == k) {
					printf("Search Succeed. Key: %d , Comparsion count: %d\n", k, count);
				} else {
					printf("Search Failed. Key: %d , Comparsion count: %d\n", k, count);
				}
			}

			// 查找性能分析
			// 插入和删除的时间均取决于查找，故这里只分析查找运算的时间性能
			// 采用线性探测法时计算成功和不成功平均查找长度的算法如下
			void ASL(HashTable ha[]) {
				int succ = 0, unsucc = 0, n = 0;
				int adr, count;
				for (int i = 0; i < _9_4_4_1_Base::m; ++i) {
					if (ha[i].key != NULLKEY) {
						succ += ha[i].probeCount;    // 统计查找成功时总的关键字比较次数
						++n;    // 统计哈希表中关键字的个数
					}
				}
				printf("ASL of Success = %d / %d = %g\n", succ, n, succ * 1.0 / n);
				for (int i = 0; i < _9_4_4_1_Base::p; ++i) {
					count = 1;
					adr = i;
					while (ha[adr].key != NULLKEY) {
						++count;
						adr = (adr + 1) % _9_4_4_1_Base::m;
					}
					unsucc += count;     // 累计不成功时总的关键字比较次数
				}
				printf("ASL of Failed = %d / %d = %g\n", unsucc, _9_4_4_1_Base::p, unsucc * 1.0 / _9_4_4_1_Base::p);
			}

		} // END namespace _9_4_4_1 用开放地址法构造的哈希表运算算法

		// 9.4.4.2 用拉链法构造的哈希表的运算
		// 仅参考，无法实际使用
		// 最后修改：2019-12-15
		namespace _9_4_4_2 {
			// 此处教材采用了全局变量（就此只能同时存在一个 hash 表），为防止污染全局空间，将其实现为 struct 作用域内变量，请勿显式修改
			struct _9_4_4_2_Base {
				static int m;    // 表示哈希表的容量
				static int p;    // 除留余数法中的被除数 p，最好为不大于 m 的最大素数
				static void set(int parM, int parP) {
					m = parM;
					p = parP;
				}
			};
			int _9_4_4_2_Base::m = 50;    // m 默认为 50
			int _9_4_4_2_Base::p = 47;    // 不大于 50 的最大素数

			typedef int KeyType;
			typedef struct node {
				KeyType key;
				struct node* next;    // 下一个结点指针
			} NodeType;
			typedef struct {
				NodeType* firstNode;    // 首结点指针
			} HashTable;    // 哈希表单元类型，采用顺序和链式相结合的存储结构

			// 插入哈希表
			void InsertHT(HashTable ha[], KeyType k) {
				int adr = k % _9_4_4_2_Base::p;
				NodeType* q = (NodeType*)malloc(sizeof(NodeType));
				q->key = k;
				q->next = ha[adr].firstNode;    // 采用头插法将新关键字结点插入到哈希表中
				ha[adr].firstNode = q;
			}

			// 创建哈希表
			void CreateHT(HashTable ha[], KeyType keys[], int n) {
				for (int i = 0; i < _9_4_4_2_Base::m; ha[i++].firstNode = NULL);
				for (int i = 0; i < n; InsertHT(ha, keys[i++]));
			}

			// 删除算法
			bool DeleteHT(HashTable ha[], KeyType k) {
				int adr = k % _9_4_4_2_Base::p;
				NodeType* q = ha[adr].firstNode;
				NodeType* pre = q;
				while (q != NULL && q->key != k) {
					pre = q;
					q = q->next;
				}
				if (q == NULL) {
					return false;    // 未查找到，返回 false
				} else if (q->key == k) {
					pre->next = q->next;
					free(q);
					return true;
				}
				return false;
			}

			// 查找算法
			void SearchHT(HashTable ha[], KeyType k) {
				int adr = k % _9_4_4_2_Base::p;
				int count = 0;
				NodeType* q = ha[adr].firstNode;
				while (q != NULL && q->key != k) {
					++count;
					q = q->next;
				}
				if (q != NULL && q->key == k) {
					printf("Search Succeed. Key: %d , Comparsion count: %d\n", k, count);
				} else {
					printf("Search Failed. Key: %d , Comparsion count: %d\n", k, count);
				}
			}

			// 查找性能分析
			void ASL(HashTable ha[]) {
				int succ = 0, unsucc = 0, n = 0, count;
				NodeType* q;
				for (int i = 0; i < _9_4_4_2_Base::m; ++i) {
					count = 0;
					q = ha[i].firstNode;
					while (q != NULL) {
						++n;
						q = q->next;
						++count;
						succ += count;
					}
					unsucc += count;
				}
				printf("ASL of Success = %d / %d = %g\n", succ, n, succ * 1.0 / n);
				printf("ASL of Failed = %d / %d = %g\n", unsucc, _9_4_4_2_Base::m, unsucc * 1.0 / _9_4_4_2_Base::m);
			}

		} // END namespace _9_4_4_2 用拉链法构造的哈希表的运算

	} // END namespace _9_4 哈希表的查找

} // END namespace dst

#endif // !DST_9SEARCH_H