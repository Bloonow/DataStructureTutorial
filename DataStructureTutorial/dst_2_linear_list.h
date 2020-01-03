// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_2_LINEAR_LIST_H
#define DST_2_LINEAR_LIST_H

// 第二章：线性表

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 2.1 线性表（linear list）及其逻辑结构
	// 元素个数叫线性表的长度
	// 表头元素、表尾元素
	// 最后修改：2019-9-10
	namespace _2_1 {
		// 线性表的抽象数据类型，描述如下
		/*
		ADT List {
			数据对象:
				D = { ai | 1 <= i <= n, ai为ElemType类型 }    // ElemType是自定义类型标识符
			数据关系:
				R = { <ai, a(i+1)> | ai、a(i+1) ∈ D, i = 1,...,n-1 }
			基本运算:
				InitList(&L)
				DestroyList(&L)
				ListEmpty(L)
				ListLength(L)
				DispList(L)
				GetElem(L,i,&e)
				LocateElem(L,e)
				ListInsert(&L,i,e)
				ListDelete(&L,i,&e)
		}
		*/

	} // END namespace _2_1 线性表及其逻辑结构

	// 2.2 线性表的顺序存储结构
	// 顺序表（sequential list）
	// 元素类型：int
	// 最后修改：2019-9-3
	namespace _2_2 {
		// 估计一个线性表不会超过50个元素
		const int MaxSize = 50;

		// 元素类型
		typedef int ElemType;

		// 声明线性表的顺序存储类型
		typedef struct {
			ElemType data[MaxSize];    // 存放线性表中的元素
			int length;    // 存放线性表的长度
		} SqList;    // 顺序表类型

		// 建立线性表，由数组元素a[0...n-1]创建顺序表L
		void CreateList(SqList*& L, ElemType a[], int n) {
			int i = 0, k = 0;    // k表示L中的元素的个数，初始值为0
			L = (SqList*)malloc(sizeof(SqList));    // 分配存放线性表的空间
			// i扫描数组a的元素
			while (i < n) {
				L->data[k] = a[i];    // 将元素a[i]放到L中
				++k;
				++i;
			}
			L->length = k;    // 设置L的长度k
		}

		// 初始化线性表 InitList(&L)
		void InitList(SqList*& L) {
			L = (SqList*)malloc(sizeof(SqList));    // 分配存放线性表的空间
			L->length = 0;    // 置空线性表的长度为0
		}

		// 销毁线性表 DestroyList(&L) O(1)
		void DestroyList(SqList*& L) {
			free(L);    // 释放L所指的顺序表空间
		}

		// 判断线性表是否为空表 ListEmpty(L) O(1)
		bool ListEmpty(SqList* L) {
			return L->length == 0;
		}

		// 求线性表的长度 ListLength(L) O(1)
		int ListLength(SqList* L) {
			return L->length;
		}

		// 输出线性表 DispList(L) O(n)
		void DispList(SqList* L) {
			// 扫描线性表输出各元素值
			for (int i = 0; i < L->length; ++i) {
				printf("%d ", L->data[i]);
			}
			printf("\n");
		}

		// 求线性表中的某个数据元素的值 GetElem(L, i, &e) O(1)
		bool GetElem(SqList* L, int i, ElemType& e) {
			if (i < 1 || i > L->length) {
				return false;    // 参数i错误时返回false
			}
			e = L->data[i - 1];    // 取元素值
			return true;    // 成功找到元素时返回true 
		}

		// 按元素值查找 LocateElem(L, e) O(n)
		int LocateElem(SqList* L, ElemType e) {
			int i = 0;
			// 查找元素e
			while (i < L->length && L->data[i] != e) {
				++i;
			}

			if (i >= L->length) {
				return 0;    // 未找到时返回0
			} else {
				return i + 1;    // 找到后返回其逻辑序号
			}
		}

		// 插入数据元素 ListInsert(&L, i, e) O(n)
		bool ListInsert(SqList*& L, int i, ElemType e) {
			if (i < 1 || i > L->length + 1) {
				return false;
			}    // 参数i错误时返回false
			--i;    // 将顺序表逻辑序号转化为物理序号
			for (int j = L->length; j > i; --j) {
				L->data[j] = L->data[j - 1];    // 将data[i]及后面的元素后移一个位置
			}
			L->data[i] = e;    // 插入元素e
			++L->length;    // 顺序表长度加1
			return true;    // 成功插入返回true
		}

		// 删除数据元素 ListDelete(&L, i, &e) O(n)
		bool ListDelete(SqList*& L, int i, ElemType& e) {
			if (i < 1 || i > L->length) {
				return false;    // 参数i错误时返回false
			}
			--i;    // 将顺序表逻辑序号转化为物理序号
			e = L->data[i];
			for (int j = i; j < L->length - 1; ++j) {
				L->data[j] = L->data[j + 1];    // 将data[i]之后的元素前移一个位置
			}
			--L->length;    // 顺序表长度减1
			return true;    // 成功插入返回true
		}

		/// 顺序表的应用示例

		// 例2.3 假设一个线性表采用顺序表表示，设计一个算法，删除其中所有值等于x的元素
		// 要求算法的时间复杂度为O(n)，空间复杂度为O(1)
		// 解法一：扫描顺序表，重建L只含不等于x的元素
		// 从左到右扫描L中的所有元素，当等于x时跳过它；否则将其放在k的位置，++k
		void delnode1(SqList*& L, ElemType x) {
			int k = 0, i;    // k记录不等于x的元素的个数，即要插入到L中元素的个数
			for (i = 0; i < L->length; ++i) {
				// 若当前元素不为x，将其插入到L中
				if (L->data[i] != x) {
					L->data[k] = L->data[i];
					++k;    // 插入一个元素时，元素的个数加1
				}
			}
			L->length = k;    // 顺序表L的长度等于k
		}

		// 例2.3 假设一个线性表采用顺序表表示，设计一个算法，删除其中所有值等于x的元素
		// 要求算法的时间复杂度为O(n)，空间复杂度为O(1)
		// 解法二：从左到右扫描L，用k记录L中当前等于x的个数，边扫描边统计
		// 等于x时k加一；否则将不为x的元素向前移k个位置
		void delnode2(SqList*& L, ElemType x) {
			int k = 0, i = 0;    // k记录当前等于x的元素的个数
			while (i < L->length) {
				// 当前元素为x时k加一
				if (L->data[i] == x) {
					++k;
				} else {
					// 当前元素不为x时，将其前移k个位置
					L->data[i - k] = L->data[i];
				}
				++i;
			}
			L->length -= k;    // 顺序表长度减k
		}

		// 例2.4 有一个顺序表L，以第一个元素为分界线（基准）
		// 将小于它的移到该基准前面，大于它的移到该基准后面
		// 基本思路是：以第一个元素为基准，从右向左找一个小于等于基准的元素x，
		// 从左向右找一个大于基准的元素y，将两者交换，直到全部找完
		// 时间复杂度为O(n)，空间复杂度为O(1)
		// 解法一：都找到，将大的跟小的交换，最后交换基准和重合处的元素
		void partition1(SqList*& L) {
			int i = 0, j = L->length - 1;
			ElemType pivot = L->data[0];    // 以data[0]为基准
			ElemType temp;    // 元素交换时用的临时变量
			// 从区间两端交替向中间扫描，直到i=j为止
			while (i < j) {
				// 从右向左扫描，找到一个小于等于pivot的元素
				while (i < j && L->data[j] > pivot) {
					--j;
				}
				// 从左向右扫描，找到一个大于pivot的元素
				while (i < j && L->data[i] <= pivot) {
					++i;
				}
				// 将大的跟小的交换
				if (i < j) {
					temp = L->data[i];
					L->data[i] = L->data[j];
					L->data[j] = temp;
				}
			}
			// 将重合处跟基准交换
			temp = L->data[0];
			L->data[0] = L->data[i];
			L->data[i] = temp;
		}

		// 例2.4 有一个顺序表L，以第一个元素为分界线（基准）
		// 将小于它的移到该基准前面，大于它的移到该基准后面
		// 基本思路是：以第一个元素为基准，从右向左找一个小于等于基准的元素x，
		// 从左向右找一个大于基准的元素y，将两者交换，直到全部找完
		// 时间复杂度为O(n)，空间复杂度为O(1)
		// 解法二：找到便立即交换（i跟j），最后用基准赋给重合处
		void partition2(SqList*& L) {
			int i = 0, j = L->length - 1;
			ElemType pivot = L->data[0];    // 以data[0]为基准
			while (i < j) {
				while (i < j && L->data[j] > pivot) {
					--j;    // 从右向左扫描，找到一个小于等于pivot的元素data[j]
				}
				L->data[i] = L->data[j];    // 将data[j]放到data[i]处
				while (i < j && L->data[i] <= pivot) {
					++i;    // 从左向右扫描，找到一个大于pivot的元素data[i]
				}
				L->data[j] = L->data[i];    // 将data[i]放到data[j]处
			}
			L->data[i] = pivot;    // 将基准放到重合处
		}

		// 例2.5 将顺序表L中的所有奇数移动到偶数前面
		// 时间复杂度为O(n)，空间复杂度为O(1)
		// 解法一：类似于例2.4解法一的思路
		void move1(SqList*& L) {
			int i = 0, j = L->length - 1;
			ElemType temp;
			while (i < j) {
				while (i < j && L->data[j] % 2 == 0) {
					--j;    // 从右向左，找一个奇数
				}
				while (i < j && L->data[i] % 2 != 0) {
					++i;    // 从左向右，找一个偶数
				}
				// 交换两个所找到的元素
				if (i < j) {
					temp = L->data[i];
					L->data[i] = L->data[j];
					L->data[j] = temp;
				}
			}
		}

		// 例2.5 将顺序表L中的所有奇数移动到偶数前面
		// 时间复杂度为O(n)，空间复杂度为O(1)
		// 解法二：扫描遍历顺序表L，重建（有交换元素在里面）顺序表
		// data[0...i]表示奇数区间（i指向奇数区间最后一个元素，初始为-1时表示为空）
		// 用j从左向右遍历所有元素，若j指向奇数，则将i加一，j和i上的元素交换，over
		void move2(SqList*& L) {
			int i = -1, j;
			ElemType temp;
			for (j = 0; j < L->length; ++j) {
				// 当j指向奇数时
				if (L->data[j] % 2 != 0) {
					++i;    // 奇数区间元素个数加一
					// 若i和j不指向同一元素，则将他们交换
					if (i != j) {
						temp = L->data[i];
						L->data[i] = L->data[j];
						L->data[j] = temp;
					}
				}
			}
		}

		// 自实现快排，辅助将顺序表递增排序
		void Qsort(ElemType a[], int firstIndex, int lastIndex) {
			if (firstIndex >= lastIndex) {
				return;
			}
			int left = firstIndex, right = lastIndex;
			ElemType pivot = a[firstIndex];
			while (left < right) {
				while (left < right && a[right] > pivot) {
					right--;
				}
				a[left] = a[right];
				while (left < right && a[left] <= pivot) {
					left++;
				}
				a[right] = a[left];
			}
			a[left] = pivot;
			Qsort(a, firstIndex, left - 1);
			Qsort(a, left + 1, lastIndex);
		}

		// 自实现：将顺序表递增排序，快排
		void Sort(SqList*& L) {
			Qsort(L->data, 0, L->length - 1);
		}

	} // END namespace _2_2 线性表的顺序存储结构

	// 2.3 线性表的链式存储结构
	// 链表（linked list）：单链表（singly linked list），双链表（double linkde list）
	// 循环链表（circular linked list），静态链表（static linked list）
	// 头指针（head pointer），首指针（first pointer），尾指针（tail pointer）
	// 最后修改：2019-9-10
	namespace _2_3 {
		// 2.3.2 单链表（singly linked list）
		// 元素类型：int 
		// 最后修改：2019-9-5
		namespace _2_3_2 {
			// 元素类型
			typedef int ElemType;

			// 每个结点用LinkNode表示
			typedef struct LNode {
				ElemType data;
				struct LNode* next;
			} LinkNode;

			// 建立单链表 头插法
			// 用数组a[]做最初元素（最后链表与数组顺序相反）
			void CreateListF(LinkNode*& L, ElemType a[], int n) {
				LinkNode* s;
				L = (LinkNode*)malloc(sizeof(LinkNode));
				L->next = NULL;    // 创建头结点，其next域置为null
				// 循环建立数据结点s
				for (int i = 0; i < n; ++i) {
					s = (LinkNode*)malloc(sizeof(LinkNode));
					s->data = a[i];    // 创建数据结点s
					s->next = L->next;    // 将s插入到首结点之前，头结点之后
					L->next = s;
				}
			}

			// 建立单链表 尾插法
			// 用数组a[]做最初元素
			// 还需要一个尾指针r，最后将其next域置为null
			void CreateListR(LinkNode*& L, ElemType a[], int n) {
				LinkNode *s, *r;
				L = (LinkNode*)malloc(sizeof(LinkNode));    // 创建头结点
				r = L;    // r始终指向尾结点，初始时头结点即尾结点
				// 循环建立数据结点
				for (int i = 0; i < n; ++i) {
					s = (LinkNode*)malloc(sizeof(LinkNode));
					s->data = a[i];     // 创建数据结点s
					r->next = s;    // 将结点s插入到尾结点r之后
					r = s;    // 尾结点r更新为最后一个
				}
				r->next = NULL;    // 尾结点next域置为null
			}

			// 初始化线性表 InitList(&L) O(1)
			void InitList(LinkNode*& L) {
				L = (LinkNode*)malloc(sizeof(LinkNode));
				L->next = NULL;
			}

			// 销毁线性表 DestroyList(&L) O(n)
			// 须遍历线性表，逐一释放每个结点空间
			void DestroyList(LinkNode*& L) {
				LinkNode *pre = L, *p = L->next;    // pre指向结点p的前驱节点
				// 扫描单链表L
				while (p != NULL) {
					free(pre);    // 释放pre结点
					pre = p;    // pre、p同步后移一个结点
					p = p->next;
				}
				free(pre);    // 循环结束时p为null，pre指向尾结点，释放之
			}

			// 判断线性表是否为空链表 ListEmpty(L) O(1)
			bool ListEmpty(LinkNode* L) {
				return L->next == NULL;
			}

			// 求线性表的长度 ListLength(L) O(n)
			int ListLength(LinkNode* L) {
				int n = 0;
				LinkNode* p = L;    // p初始指向头结点，n为0，即头结点的序号为0
				while (p->next != NULL) {
					n++;
					p = p->next;
				}
				return n;    // 循环结束，p指向尾结点，其序号n为结点个数
			}

			// 输出线性表 DispList(L) O(n)
			void DispList(LinkNode* L) {
				LinkNode* p = L->next;    // p指向首结点
				// p不为null，输出结点p的data域
				while (p != NULL) {
					printf("%d ", p->data);
					p = p->next;    // p移向下一个结点
				}
				printf("\n");
			}

			// 求线性表中的某个数据元素值 GetElem(L, i, &e) O(n)
			bool GetElem(LinkNode* L, int i, ElemType& e) {
				if (i <= 0) {
					return false;    // i错误返回false
				}
				int j = 0;
				LinkNode* p = L;    // p初始指向头结点，j置为0（即头结点的序号为0）
				// 找到第i个结点，或者遍历到尾（没有第i个结点，即单链表长度小于i）
				while (j < i && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;    // 不存在第i个结点（i超出单链表长度），返回false
				} else {
					e = p->data;    // 存在第i个结点，赋给e，返回true
					return true;
				}
			}

			// 按元素值查找 LocateElem(L, e) O(n)
			int LocateElem(LinkNode* L, ElemType e) {
				int i = 1;
				LinkNode* p = L->next;    // p初始指向首结点，i置为1（即首结点序号为1）
				// 查找data值为e的结点，其序号为i
				while (p != NULL && p->data != e) {
					p = p->next;
					++i;
				}
				if (p == NULL) {
					return 0;    // 不存在值为e的结点，返回0
				} else {
					return i;    // 存在值为e的结点，返回其逻辑序号
				}
			}

			// 插入数据元素 ListInsert(&L, i, e) O(n)
			bool ListInsert(LinkNode*& L, int i, ElemType e) {
				if (i <= 0) {
					return false;    // i错误返回false
				}
				int j = 0;
				LinkNode *p = L, *s;    // p初始指向头结点，j置为0（即头结点序号为0）
				// 查找第i个结点的前驱节点，即第i-1个结点，用p指向
				while (j < i - 1 && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;    // i-1超出单链表长度，返回false
				} else {
					// 找到第i-1个结点p，插入新结点，返回true
					s = (LinkNode*)malloc(sizeof(LinkNode));
					s->data = e;    // 创建新结点s，其data域为e
					s->next = p->next;    // 将新结点插入到p结点之后（即i-1之后，i之前）
					p->next = s;
					return true;
				}
			}

			// 删除数据元素 ListDelete(&L, i, &e) O(n)
			bool ListDelete(LinkNode*& L, int i, ElemType &e) {
				if (i <= 0) {
					return false;    // i错误返回false
				}
				int j = 0;
				LinkNode *p = L, *q;    // p初始指向头结点，j置为0（即头结点序号为0）
				// 查找第i个结点的前驱节点，即第i-1个结点，用p指向
				while (j < i - 1 && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;    // i-1超出单链表长度，返回false
				} else {
					// 找到第i-1个结点
					q = p->next;    // q指向第i个结点
					if (q == NULL) {
						// 若第i个结点为null，即第i-1个结点为尾结点, 返回false
						// 是因为之前while中判断语句的短路特性，当i正好是尾结点时
						// while是由于j == i-1而跳出的循环，此时前驱节点(i-1)p指向尾结点
						// 这种情况下，再令q = p->next时，q是NULL，故需要判断
						return false;
					}
					e = q->data;    // 删除的结点元素作为返回值返回
					p->next = q->next;    // 从单链表中删除q结点，即第i个结点
					free(q);    // 释放空间
					return true;
				}
			}

			// 自实现：向单链表尾加入结点 pushElem(&L, e) O(n)
			void pushElem(LinkNode*& L, ElemType e) {
				LinkNode *p = L, *s;
				while (p->next != NULL) {
					p = p->next;
				}
				s = (LinkNode*)malloc(sizeof(LinkNode));
				s->next = NULL;
				s->data = e;
				p->next = s;
			}

			/// 单链表的应用示例

			// 例2.6 将带有头结点的单链表L={a1,b1,a2,b2,...,an,bn}（偶数个元素结点）
			// 拆成两个带头结点的L1和L2，要求L1使用L的头结点
			// L1={a1,a2,a3,...,an}  L2={bn,b(n-1),...,b2,b1}
			// 解题思路：重建L1和L2，由其顺序知L1用尾插法，L2用头插法
			// 时间复杂度为O(n)
			void split(LinkNode*& L, LinkNode*& L1, LinkNode*& L2) {
				LinkNode *p = L->next, *q, *r1;    // p初始指向第一个数据结点
				L1 = L;    // L1利用原来的L的头结点
				r1 = L1;    // r1始终指向L1的尾结点，初始时头结点即尾结点
				L2 = (LinkNode*)malloc(sizeof(LinkNode));    // 创建L2的头结点
				L2->next = NULL;    // 置L2的指针域为NULL
				while (p != NULL) {
					r1->next = p;    // 采用尾插法将p结点（data为ai）插入到L1中
					r1 = p;
					p = p->next;    // 将p移动到下一结点（data为bi）
					q = p->next;    // 用q记录当前p的后继结点（ data为a(i+1) )，因为头插法会改变p结点的next指针域
					p->next = L2->next;    // 采用头插法将p结点（data为bi）插入到L2中
					L2->next = p;
					p = q;    // p结点重新指向a(i+1)结点
				}
				r1->next = NULL;    // 将L1的尾结点的next指针域置为NULL
			}

			// 例2.7 删除一个单链表L中元素最大的结点（假设这样的结点唯一）
			// 插入或删除操作离不开前驱节点pre和当前结点p（一般用p表示）
			// 解题思路：类似数组操作中找最大的值，遍历，用max存储当前最大
			// 时间复杂度为O(n)
			void delMaxNode(LinkNode*& L) {
				LinkNode *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
				// 用p扫描整个单链表，pre始终指向其前驱结点
				while (p != NULL) {
					// 若找到一个更大的结点
					if (maxp->data < p->data) {
						maxp = p;    // 更新maxp和maxpre
						maxpre = pre;
					}
					pre = p;    //p、pre同步向后移一个结点
					p = p->next;
				}
				maxpre->next = maxp->next;    // 删除maxp结点并释放其空间
				free(maxp);
			}

			// 例2.8 将单链表L（至少有一个数据元素结点），递增排序
			// 解题思路：重建L，从原单链表每取一个，遍历新的L，判断应该插入的位置，插入之
			// 时间复杂度为O(n^2)
			bool sort(LinkNode*& L) {
				if (L->next == NULL) {
					return false;    // 若L无数据结点，返回false
				}
				LinkNode *p, *pre, *q;
				p = L->next->next;    // p指向L的第2个数据结点
				L->next->next = NULL;    // 构造一个只含一个数据结点的有序单链表（一个数据结点一定有序）
				while (p != NULL) {
					q = p->next;    // q保存p结点后继结点的指针
					pre = L;
					// 注意while里的判断表达式，根据短路定理，&&两边不能颠倒
					// 因为pre->next为空时就要跳出，就不用判断pre->next->data了
					// 若反过来，需要先判断pre->next->data
					// 而当pre->next为空时，先判断时要访问pre->next->data会出错（NULL没有data域）
					while (pre->next != NULL && pre->next->data < p->data) {
						pre = pre->next;    // 在有序单链表中寻找插入p所指结点的前驱结点的位置（pre所指向）
					}
					// 跳出while循环有两种情况：
					// 1）：pre结点小于p，pre->next大于p 
					// (因为新单链表是有序递增的，故第一次因pre->next大于等于p而跳出循环时，pre小于p）
					// 2）：pre指向尾结点，pre->next为null
					p->next = pre->next;    // 在pre所指结点之后插入p所指结点
					pre->next = p;
					p = q;    // 扫描原单链表余下的结点
				}
				return true;
			}

		} // END namespace _2_3_2 单链表

		// 2.3.3 双链表（double linked list）
		// 元素类型：int
		// 最后修改：2019-9-10
		namespace _2_3_3 {
			// 元素类型
			typedef int ElemType;

			typedef struct DNode {
				ElemType data;
				struct DNode* prior;    // 前驱结点
				struct DNode* next;    // 后继结点
			} DLinkNode;    // 双链表的结点类型

			// 建立双链表 头插法
			void CreateListF(DLinkNode*& L, ElemType a[], int n) {
				DLinkNode* s;
				L = (DLinkNode*)malloc(sizeof(DLinkNode));
				L->prior = L->next = NULL;
				for (int i = 0; i < n; ++i) {
					s = (DLinkNode*)malloc(sizeof(DLinkNode));
					s->data = a[i];
					s->next = L->next;    // 将s结点插入到头结点之后
					// 判断p->next是否为NULL，若p->next为NULL，则对其进行->prior运算会抛错
					// 此处是判断L的下一个结点是否为空，即插入第一个结点的情况
					if (L->next != NULL) {
						L->next->prior = s;
					}
					s->prior = L;    // 此处两个语句可替换顺序，不影响结果
					L->next = s;
				}
			}

			// 建立双链表 尾插法
			void CreateListR(DLinkNode*& L, ElemType a[], int n) {
				L = (DLinkNode*)malloc(sizeof(DLinkNode));
				L->prior = L->next = NULL;
				DLinkNode* r = L;    // r始终指向尾结点，开始时头即是尾
				DLinkNode* s;
				for (int i = 0; i < n; ++i) {
					s = (DLinkNode*)malloc(sizeof(DLinkNode));
					s->data = a[i];
					r->next = s;
					s->prior = r;
					r = s;
				}
				r->next = NULL;
			}

			// 在双链表中，有些运算（初始化，销毁，判断是否为空，求长度，输出，求某个元素值，按元素值查找）
			// 是与单链表中相应的算法相同的，有区别的是插入和删除结点的算法

			// 初始化双链表 InitList(&L) O(1)
			void InitList(DLinkNode*& L) {
				L = (DLinkNode*)malloc(sizeof(DLinkNode));
				L->prior = L->next = NULL;
			}

			// 销毁双链表 DestroyList(&L) O(n)
			void DestroyList(DLinkNode*& L) {
				DLinkNode *pre = L, *p = L->next;
				while (p != NULL) {
					free(pre);
					pre = p;
					p = p->next;
				}
				free(pre);
			}

			// 判断双链表是否为空 ListEmpty(L) O(1)
			bool ListEmpty(DLinkNode* L) {
				return L->next == NULL;
			}

			// 求双链表的长度 ListLength(L) O(n)
			int ListLength(DLinkNode* L) {
				int n = 0;
				DLinkNode* p = L;
				while (p->next != NULL) {
					++n;
					p = p->next;
				}
				return n;
			}

			// 输出双链表 DispList(L) O(n)
			void DispList(DLinkNode* L) {
				DLinkNode* p = L->next;
				while (p != NULL) {
					printf("%d ", p->data);
					p = p->next;
				}
				printf("\n");
			}

			// 求双链表中第i个元素的值 GetElem(L,i,&e) O(n)
			bool GetElem(DLinkNode* L, int i, ElemType& e) {
				if (i <= 0) {
					return false;
				}
				int j = 0;
				DLinkNode* p = L;
				while (j < i && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;
				} else {
					e = p->data;
					return true;
				}

			}

			// 按元素值查找位置 LocateElem(L,e) O(n)
			int LocateElem(DLinkNode* L, ElemType e) {
				DLinkNode* p = L->next;
				int i = 1;
				while (p != NULL && p->data != e) {
					++i;
					p = p->next;
				}
				if (p == NULL) {
					return 0;
				} else {
					return i;
				}
			}

			// 在双链表第i个位置上插入元素 ListInsert(&L,i,e) O(n)
			bool ListInsert(DLinkNode*& L, int i, ElemType e) {
				if (i <= 0) {
					return false;
				}
				int j = 0;
				DLinkNode* p = L;
				// 从0（头结点）开始，寻找第i-1个结点
				while (j < i - 1 && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;
				} else {
					DLinkNode* s = (DLinkNode*)malloc(sizeof(DLinkNode));
					s->data = e;
					s->next = p->next;
					// 若p存在后继结点，则修改其前驱指针
					if (p->next != NULL) {
						p->next->prior = s;
					}
					s->prior = p;
					p->next = s;
					return true;
				}
			}
			// 在双链表中删除第i个结点 ListDelete(&L,i,&e) O(n)
			bool ListDelete(DLinkNode*& L, int i, ElemType& e) {
				if (i <= 0) {
					return false;
				}
				int j = 0;
				DLinkNode *p = L;
				while (j < i - 1 && p != NULL) {
					++j;
					p = p->next;
				}
				if (p == NULL) {
					return false;
				} else {
					// 要删除第i个结点，p是所找到的第i-1个结点
					// q指向要删掉的第i个结点，若为空返回false
					// 不为空，删除之（注意判断第i+1个结点是否为空，从而确定怎么更新指针域信息）
					DLinkNode* q = p->next;
					if (q == NULL) {
						return false;
					}
					e = q->data;
					p->next = q->next;
					if (q->next != NULL) {
						q->next->prior = p;
					}
					free(q);
					return true;
				}
			}

			/// 双链表的应用示例

			// 例2.9 将带有头结点的双链表L逆置 O(n)
			// 解题思路：使用头插法，重建L
			void reverse(DLinkNode*& L) {
				DLinkNode *p = L->next, *q;
				L->next = NULL;
				while (p != NULL) {
					q = p->next;
					p->next = L->next;
					if (L->next != NULL) {
						L->next->prior = p;
					}
					L->next = p;
					p->prior = L;
					p = q;
				}
			}

			// 例2.10 带有头结点的双链表，使其递增有序排列 O(n)
			// 解题思路同例2.8 只是插入结点的操作有些不同
			void sort(DLinkNode*& L) {
				if (L->next == NULL) {
					return;
				}
				DLinkNode* p = L->next->next, *q, *pre;
				L->next->next = NULL;
				while (p != NULL) {
					q = p->next;
					pre = L;
					while (pre->next != NULL && pre->next->data < p->data) {
						pre = pre->next;
					}
					p->next = pre->next;
					if (pre->next != NULL) {
						pre->next->prior = p;
					}
					pre->next = p;
					p->prior = pre;
					p = q;
				}
			}

		} // END namespace _2_3_3 双链表

		// 2.3.4 循环链表（circular linked list）
		// 循环链表是另一种形式的链式存储结构。有单循环链表和双循环链表两种类型
		// 循环链表和非循环链表的结点类型LinkNode和DLinkNode相同
		// 单循环链表的尾next指向头；双循环链表尾next指向头，头prior指向尾
		// 判断表尾结点p的条件是 p->next == L ，而不是 p->next == NULL
		// 元素类型：int
		// 该命名空间中内容只是声明，未实现
		// 最后修改：2019-9-10
		namespace _2_3_4 {
			// 元素类型
			typedef int ElemType;

			typedef struct LNode {
				ElemType data;
				struct LNode* next;
			} LinkNode;

			typedef struct DNode {
				ElemType data;
				struct DNode* prior;
				struct DNode* next;
			} DLinkNode;
		}

		// 2.3.5 静态链表（static linked list）
		// 存储模式是内存中顺序存储，即数组
		// 使用伪指针curNext（int类型，存储数组索引），其值为后驱元素的数组索引
		// 元素类型：int
		// 该命名空间中内容只是声明，未实现
		// 最后修改：2019-9-10
		namespace _2_3_5 {
			const int MaxSize = 50;

			// 元素类型
			typedef int ElemType;

			typedef struct SNode {
				ElemType data[MaxSize];
				int curNext;
			} StaticNode;
		} // END namespace _2_3_5

	} // END namespace _2_3 线性表的链式存储结构

	// 2.4 线性表的应用
	// 最后修改：2019-9-10
	namespace _2_4 {
		// 空
	} // END namespace _2_4 线性表的应用

	// 2.5 有序表（ordered list）
	// 有序表是一种特殊的线性表，它的元素按顺序排列，递增或递减
	// 有序表的算法基本和一般线性表相同，有差别的只是插入算法 ListInset
	// 有序表（逻辑结构）可以用顺序表、链表（存储结构）实现
	// 该命名空间中的实现基于递增有序表，且只实现了与一般线性表不同的算法
	// 使用时请先根据其他命名空间中的sort算法，将一般线性表递增排序
	// 然后可用命名空间中的算法
	// 元素类型：int
	// 最后修改：2019-9-10
	namespace _2_5 {
		// 元素类型
		typedef int ElemType;

		using dst::_2_2::SqList;
		using dst::_2_3::_2_3_2::LinkNode;

		// 有序顺序表插入算法 ListInsert(&L,e) O(n)
		void ListInsert(SqList*& L, ElemType e) {
			int i = 0, j;
			// 查找第一个比e大的元素i处
			while (i < L->length && L->data[i] < e) {
				++i;
			}
			// 将从i处的元素开始都向后移一位
			for (j = ListLength(L); j > i; --j) {
				L->data[j] = L->data[j - 1];
			}
			// 将e插入i上
			L->data[i] = e;
			++L->length;
		}

		// 有序单链表的插入算法 ListInsert(&L,e) O(n)
		void ListInsert(LinkNode*& L, ElemType e) {
			LinkNode* pre = L;
			while (pre->next != NULL && pre->next->data < e) {
				pre = pre->next;
			}
			LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
			s->data = e;
			s->next = pre->next;
			pre->next = s;
		}

		// 例2.14 有序表归并算法
		// 有两个有序表LA和LB，假设每个有序表和两个有序表间不存在重复元素
		// 不破坏LA和LB，将其合并成一个有序表LC
		// 解题思路：比较当前元素，小的放入LC，再从较小元素所在表取下元素，重复
		// 顺序表
		void UnionList(SqList* LA, SqList* LB, SqList*& LC) {
			int i = 0, j = 0, k = 0;    // i、j 分别为LA、LB下标，k为LC中元素个数
			LC = (SqList*)malloc(sizeof(SqList));
			while (i < LA->length && j < LB->length) {
				if (LA->data[i] < LB->data[j]) {
					LC->data[k] = LA->data[i];
					++i;
					++k;
				} else {
					// LA->data[i] > LB->data[j]，前提假设不存在重复
					LC->data[k] = LB->data[j];
					++j;
					++k;
				}
			}
			// LA未扫描完，将其余元素接入到LC末尾
			while (i < LA->length) {
				LC->data[k] = LA->data[i];
				++i;
				++k;
			}
			// LB未扫描完，将其余元素接入到LC末尾
			while (j < LB->length) {
				LC->data[k] = LB->data[j];
				++j;
				++k;
			}
			LC->length = k;
		}

		// 例2.14 有序表归并算法
		// 有两个有序表LA和LB，假设每个有序表和两个有序表间不存在重复元素
		// 不破坏LA和LB，将其合并成一个有序表LC
		// 解题思路：比较当前元素，小的放入LC，再从较小元素所在表取下元素，重复
		// 单链表
		void UnionList(LinkNode* LA, LinkNode* LB, LinkNode*& LC) {
			LinkNode *pa = LA->next, *pb = LB->next, *s, *r;
			LC = (LinkNode*)malloc(sizeof(LinkNode));
			r = LC;    // 为保持原递增顺序不变，LC采用尾插法，初始时尾r和头LC重回
			while (pa != NULL && pb != NULL) {
				if (pa->data < pb->data) {
					// 新开辟空间，避免破坏原有序表
					s = (LinkNode*)malloc(sizeof(LinkNode));
					s->data = pa->data;
					r->next = s;
					r = s;
					pa = pa->next;
				} else {
					s = (LinkNode*)malloc(sizeof(LinkNode));
					s->data = pb->data;
					r->next = s;
					r = s;
					pb = pb->next;
				}
			}
			// 为避免破环原表，不能直接接过去
			while (pa != NULL) {
				s = (LinkNode*)malloc(sizeof(LinkNode));
				s->data = pa->data;
				r->next = s;
				r = s;
				pa = pa->next;
			}
			while (pb != NULL) {
				s = (LinkNode*)malloc(sizeof(LinkNode));
				s->data = pb->data;
				r->next = s;
				r = s;
				pb = pb->next;
			}
			r->next = NULL;
		}

	} // END namespace _2_5 有序表

} // END namespace dst 数据结构教程

#endif // !DST_2_LINEAR_LIST