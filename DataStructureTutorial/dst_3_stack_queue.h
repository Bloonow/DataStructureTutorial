// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_3_STACK_QUEUE_H
#define DST_3_STACK_QUEUE_H

// 第三章：栈和队列

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 3.1 栈（stack）
	// 最后修改：2019-10-24
	namespace _3_1 {
		// 泛型栈
		// 实现基于顺序栈
		// 最后修改：2019-10-24
		namespace aq_3_1 {
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

		} // END namespace aq_3_1 泛型栈

		// 3.1.1 栈的定义
		// 栈顶（top）、栈底（bottom）、进栈或入栈（push）、出栈或退栈（pop）
		// 后进先出（Last In First Out，LIFO）
		// 最后修改：2019-9-12
		namespace _3_1_1 {
			// 栈抽象数据类型的定义如下
			/*
			ADT Stack {
				数据对象:
					D = { ai | 1 <= i <= n, n >= 0, ai为ElemType类型 }    // ElemType 是自定义类型标识符
				数据关系:
					R = { <ai,a(i+1)> | ai, a(i+1) ∈ D, i = 1,...,n-1 }
				基本运算:
					InitStack(&s)
					DestroyStack(&s)
					StackEmpty(s)
					Push(&s,e)
					Pop(&s,&e)
					GetTop(s,&e)
			}
			*/

			// n个不同的元素通过一个栈产生的出栈序列有C(n)(2n)/(n+1)种

		} // END namespace _3_1_1 栈的定义

		// 3.1.2 栈的顺序存储结构及其基本运算的实现
		// 顺序栈（sequential stack）
		// 栈空条件：顶指针为-1； 栈满条件：顶指针为数组最大下标
		// 元素类型：char
		// 最后修改：2019-9-12
		namespace _3_1_2 {
			// 元素类型
			typedef char ElemType;

			// 顺序栈最大数据元素数量，即栈深
			const int MaxSize = 50;

			typedef struct {
				ElemType data[MaxSize];    // 存放栈中的数据元素
				int top;    // 栈顶指针，即存放栈顶元素在data数组中的下标
			} SqStack;    // 顺序栈类型

			// 初始化栈 InitStack(&s) O(1)
			void InitStack(SqStack*& s) {
				s = (SqStack*)malloc(sizeof(SqStack));
				s->top = -1;    // 栈顶指针置为-1
			}

			// 销毁栈 DestroyStack(&s) O(1)
			void DestroyStack(SqStack*& s) {
				free(s);
			}

			// 判断栈是否为空 StackEmpty(s)
			bool StackEmpty(SqStack* s) {
				return (s->top == -1);
			}

			// 进栈 Push(&s,e) O(1)
			bool Push(SqStack*& s, ElemType e) {
				// 栈满，返回false
				if (s->top == MaxSize - 1) {
					return false;
				}
				++s->top;
				s->data[s->top] = e;
				return true;
			}

			// 出栈 Pop(&s,&e) O(1)
			bool Pop(SqStack*& s, ElemType& e) {
				// 栈空，返回false
				if (s->top == -1) {
					return false;
				}
				e = s->data[s->top];
				--s->top;
				return true;
			}

			// 取栈顶元素 GetTop(s,&e) O(1)
			bool GetTop(SqStack* s, ElemType& e) {
				// 栈空，返回false
				if (s->top == -1) {
					return false;
				}
				e = s->data[s->top];
				return true;
			}

			// 例3.4 利用顺序栈判断一个字符串是否为对称串
			bool symmetry(ElemType str[]) {
				int i;
				ElemType e;
				SqStack* st;
				InitStack(st);    // 初始化栈
				// 将str中所有元素进栈
				for (i = 0; str[i] != '\0'; ++i) {
					Push(st, str[i]);
				}
				for (i = 0; str[i] != '\0'; ++i) {
					Pop(st, e);
					// 若e与当前串字符不同表示不是对称串，返回false
					if (str[i] != e) {
						DestroyStack(st);
						return false;
					}
				}
				DestroyStack(st);
				return true;    // 遍历完，未发现不同，即对称，返回true
			}

			// 共享栈（用一个数组来实现两个栈）
			/*
			typedef struct {
				ElemType data[MaxSize];
				int top1, top2;
			} DStack;
			*/
		} // END namespace _3_1_2 栈的顺序存储结构及其基本运算的实现

		// 3.1.3 栈的链式存储结构及其基本运算的实现
		// 链栈（linked stack）
		// 栈顶操作都是在单链表头进行操作（进栈用头插法）
		// 栈空条件：s->next为NULL
		// 元素类型：char
		// 最后修改：2019-9-12
		namespace _3_1_3 {
			// 元素类型
			typedef char ElemType;

			typedef struct linknode {
				ElemType data;    // 数据域
				struct linknode* next;    // 指针域
			} LinkStNode;    // 链栈结点类型

			// 初始化栈 InitStack(&s) O(1)
			void InitStack(LinkStNode*& s) {
				s = (LinkStNode*)malloc(sizeof(LinkStNode));
				s->next = NULL;
			}

			// 销毁栈 DestroyStack(&s) O(1)
			void DestroyStack(LinkStNode*& s) {
				LinkStNode *pre = s, *p = s->next;    // pre指向头结点，p指向首结点
				// 循环到p为空
				while (p != NULL) {
					free(pre);    // 释放pre结点
					pre = p;    // pre、p同步后移
					p = p->next;
				}
				free(pre);    // 此时pre指向尾结点，释放之
			}

			// 判断栈是否为空 StackEmpty(s)
			bool StackEmpty(LinkStNode* s) {
				return (s->next == NULL);
			}

			// 进栈 Push(&s,e) O(1)
			void Push(LinkStNode*& s, ElemType e) {
				LinkStNode* p = (LinkStNode*)malloc(sizeof(LinkStNode));
				p->data = e;
				p->next = s->next;    // 将p插入作为首结点
				s->next = p;
			}

			// 出栈 Pop(&s,&e) O(1)
			bool Pop(LinkStNode*& s, ElemType& e) {
				// 栈空，返回false
				if (s->next == NULL) {
					return false;
				}
				LinkStNode* p = s->next;    // p指向首结点
				e = p->data;    // 提取首结点的值
				s->next = p->next;    // 删除首结点，并释放其空间
				free(p);
				return true;
			}

			// 取栈顶元素 GetTop(s,&e) O(1)
			bool GetTop(LinkStNode* s, ElemType& e) {
				// 栈空，返回false
				if (s->next == NULL) {
					return false;
				}
				e = s->next->data;    // 提取首结点的值
				return true;
			}

			// 例3.5 判断输入的表达式中括号是否配对
			// 解题思路：从左到右扫描表达式，遇到 ( 进栈；遇到 ) 时，若栈顶为 ( ，一起出栈，否则返回false
			bool Match(char exp[], int length) {
				int i = 0;
				char e;
				bool match = true;
				LinkStNode* st;
				InitStack(st);
				// 扫描exp中所有字符
				while (i < length && match) {
					// 当前字符为 ( ，将其进栈
					if (exp[i] == '(') {
						Push(st, exp[i]);
					} else if (exp[i] == ')') {
						// 当前字符为 )
						if (GetTop(st, e) == true) {
							// 成功提取栈顶元素，即栈非空
							if (e != '(') {
								match = false;    // 栈顶元素不为 ( 时，表示不匹配
							} else {
								Pop(st, e);    // 栈顶元素为 ( ,出栈
							}
						} else {
							match = false;    // 无法取栈中元素表示不匹配
						}
					}
					++i;
				}
				// 栈非空表示不匹配
				if (!StackEmpty(st)) {
					match = false;
				}
				DestroyStack(st);
				return match;
			}

		} // END namespace _3_1_3 栈的链式存储结构及其基本运算的实现

		// 3.1.4 栈的应用
		// 最后修改：2019-9-17
		namespace _3_1_4 {
			// 1. 简单表达式求值
			// (1) 将算术表达式转换成后缀表达式：（利用操作符栈）
			// 原理：先执行的运算符先出栈
			// 从左到右扫描算术表达式，遇到操作数直接保存到后缀表达式中，每个数字后加一个 # 以分隔
			// 遇到左括号 ( ，表示一个子表达式开始，左括号直接压入栈顶
			// 继续扫描，如果遇到运算符op为右括号 ) ，表示子表达式结束，依次出栈op放入后缀表达式，直到栈顶为左括号 ( ，将左括号出栈
			// 继续扫描，当op是其他运算符，而栈顶是左括号 ( 或栈空，直接入栈
			// 其他情况，如果遇到运算符op，优先级高于栈顶元素，则压入栈
			// 否则依次出栈放入后缀表达式中，直到满足op优先级高于栈顶运算符，然后op进栈
			// (2) 对后缀表达式求值：（利用操作数栈）
			// 从左到右扫描后缀表达式，遇到操作数直接压入栈顶
			// 遇到操作符op，从栈中一次弹出两个数right和left，执行left op right，结果压入栈顶，重复
			// 最后修改：2019-9-12
			namespace _3_1_4_1 {
				// 引用泛型栈
				using dst::_3_1::aq_3_1::Stack;

				/*
				将算术表达式转换成后缀表达式
				form exp to postexp
				伪代码描述：
				while (从exp中读取字符ch, ch != '\0') {
					ch 为数字: 将后续所有数字依次存放的postexp中，并以#标识数字串结束;
					ch 为左括号'(': 将左括号压入栈顶
					ch 为右括号')': 将opStack中出栈时遇到的第一个左括号'('以前的运算符依次出栈并放到postexp中，然后左括号出栈
					ch 为'+'或'-': 出栈运算符并放到postexp中，直到栈顶为'('或栈空，然后ch进栈
					ch 为'*'或'/': 出栈运算符并放到postexp中，直到栈顶为'('、'+'、'-'为栈空，然后ch进栈 }
				若exp扫描完毕，将opStack中所有运算符依次出栈，放到postexp中
				*/
				void trans(char* exp, char postexp[]) {
					char e;
					Stack<char>* opStack;    // 定义运算符栈指针
					InitStack(opStack);    // 初始化运算符栈
					int i = 0;    // i作为后缀表达式postexp的下标
					// 算术表达式exp未扫描完时循环
					while (*exp != '\0') {
						switch (*exp) {
						case '(':    // 判定为左括号 (
							Push(opStack, '(');    // 左括号进栈
							exp++;
							break;
						case ')':    // 判定为右括号 )
							Pop(opStack, e);    // 出栈元素e
							// 出栈元素e不为 ( 时循环
							while (e != '(') {
								postexp[i++] = e;    // 将e放入到后缀表达式
								Pop(opStack, e);
							}
							exp++;
							break;
						case '+':    // 判断为加号或减号 + -
						case '-':
							// 栈不为空循环
							while (!StackEmpty(opStack)) {
								GetTop(opStack, e);    // 取栈顶元素e
								if (e != '(') {
									// e不是左括号，放入postext中，并出栈
									postexp[i++] = e;
									Pop(opStack, e);
								} else {
									break;    // e为左括号时退出循环
								}
							}
							Push(opStack, *exp);    // 将 '+'或'-'进栈
							exp++;
							break;
						case '*':
						case '/':
							while (!StackEmpty(opStack)) {
								GetTop(opStack, e);
								// 将栈顶的 * 或 / 出栈，放入postexp
								if (e == '*' || e == '/') {
									postexp[i++] = e;
									Pop(opStack, e);
								} else {
									break;    // 栈顶不为 * 或 / 时退出循环
								}
							}
							Push(opStack, *exp);
							exp++;
							break;
						default:    // 处理数字字符
							// 判断为数字字符
							while (*exp >= '0' && *exp <= '9') {
								postexp[i++] = *exp;
								exp++;
							}
							postexp[i++] = '#';    // 用#标识一个数字串结束
						}
					}
					// 栈不为空时循环，取出元素e，放入postexp中
					while (!StackEmpty(opStack)) {
						Pop(opStack, e);
						postexp[i++] = e;
					}
					postexp[i++] = '\0';    // 给postexp表达式加上结束标识符
					DestroyStack(opStack);    // 销毁栈
				}

				// 后缀表达式求值
				// 依次扫描，遇到操作数压入栈顶，遇到操作符op弹出两个数，计算，压入栈顶，重复
				bool compvalue(char* postexp, float& result) {
					float right, left, value, temp;
					Stack<float>* opNum;
					InitStack(opNum);
					// postexp未扫描完时循环
					while (*postexp != '\0') {
						// 判定为操作符，计算，入栈
						switch (*postexp) {
						case '+':
							Pop(opNum, right);
							Pop(opNum, left);
							value = left + right;
							Push(opNum, value);
							break;
						case '-':
							Pop(opNum, right);
							Pop(opNum, left);
							value = left - right;
							Push(opNum, value);
							break;
						case '*':
							Pop(opNum, right);
							Pop(opNum, left);
							value = left * right;
							Push(opNum, value);
							break;
						case '/':
							Pop(opNum, right);
							Pop(opNum, left);
							if (right == 0) {
								return false;
							}
							value = left / right;
							Push(opNum, value);
							break;
						default:    // 处理数字字符
							temp = 0;
							// 将连续的数字转换成对应的数值存放到temp中
							while (*postexp >= '0' && *postexp <= '9' && *postexp != '#') {
								temp = 10 * temp + (*postexp - '0');
								postexp++;
							}
							Push(opNum, temp);    // 将数值temp进栈
							break;
						}
						postexp++;
					}
					GetTop(opNum, result);
					DestroyStack(opNum);
					return true;
				}
			} // END namespace _3_1_4_1 简单表达式求值

			// 2. 求解迷宫问题（深度优先搜索）
			// 给定一个 M x N 的迷宫，求一条从指定入口到出口的迷宫路径（非最短路径）
			// 用二维数组表示迷宫，1不可走，0可走，-1为相邻来的路径不可走
			// 一个方块(i,j)从上方开始顺时针编号 0 1 2 3 表示 上 右 下 左 四个方向
			// 当前位置进栈，判断是否可走，可走进栈，不可走退栈，重复直到出口
			// 最后修改：2019-9-17
			namespace _3_1_4_2 {
				// 迷宫例子
				const int M = 8;
				const int N = 8;
				int mg[M + 2][N + 2] = {
					{1,1,1,1,1,1,1,1,1,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,0,0,1,1,0,0,1},
					{1,0,1,1,1,0,0,0,0,1}, {1,0,0,0,1,0,0,0,0,1}, {1,0,1,0,0,0,1,0,0,1}, {1,0,1,1,1,0,1,1,0,1},
					{1,1,0,0,0,0,0,0,0,1}, {1,1,1,1,1,1,1,1,1,1}
				};

				typedef struct {
					int i;    // 方块行号
					int j;    // 方块列号
					int dire;    // 下一相邻可走方块号 0 1 2 3
				} Box;    // 方块类型

				using dst::_3_1::aq_3_1::Stack;
				typedef Stack<Box> StType;    // 引用泛型类
				const int MaxSize = 50;    // 代表从入口到出口的长度，即方块的个数

				/*
				求解迷宫中从入口(xi,yi)到出口(xe,ye)的一条迷宫路径的伪代码过程如下：
				将入口(xi,yi)进栈（其初始方块位置设置为-1）;
				mg[xi][yi] = -1;
				while (栈不空) {
					取栈顶方块(i,j,di);
					if ((i,j)时出口(xe,ye)) {
						输出栈中的全部方块构成的一条迷宫路径;
						return true;
					}
					查找(i,j,di)的下一个相邻的可走方块;
					if (找到一个相邻可走方块) {
						该方块为(i1,j1),对应方位d;
						将栈顶方块的di设置为d;
						(i1,j1,-1)进栈;
						mg[i1][j1] = -1;
					}
					if (没有找到(i,j,di)的任何相邻的可走方块) {
						将(i,j,di)出栈;
						mg[i][j] = 0;
					}
				}
				return false;
				*/
				bool mgpath(int xi, int yi, int xe, int ye) {
					// 求解路径为(xi,yi) -> (xe,ye)
					Box e;
					int i, j, di, i1, j1;
					bool find;
					StType* st;    // 定义并初始化栈
					InitStack(st);
					e.i = xi; e.j = yi; e.dire = -1;    // 设置e为入口
					Push(st, e);
					mg[xi][yi] = -1;    // 将入口的迷宫值置为-1，避免重复走到该方块
					while (!StackEmpty(st)) {
						GetTop(st, e);
						i = e.i; j = e.j; di = e.dire;
						// 找到了出口，输出路径
						if (i == xe && j == ye) {
							int k = 0;
							Box path[MaxSize];
							while (!StackEmpty(st)) {
								Pop(st, e);
								path[k++] = e;
							}
							while (k >= 1) {
								--k;
								printf("\t(%d, %d) ", path[k].i, path[k].j);
								if ((k + 2) % 5 == 0) {
									printf("\n");
								}
							}
							printf("\n");
							DestroyStack(st);
							return true;
						}
						find = false;
						// 寻找方块(i,j)的下一个相邻可走方块(i1,j1)
						while (di < 4 && !find) {
							++di;
							switch (di) {
							case 0:
								i1 = i - 1; j1 = j; break;
							case 1:
								i1 = i; j1 = j + 1; break;
							case 2:
								i1 = i + 1; j1 = j; break;
							case 3:
								i1 = i; j1 = j - 1; break;
							}
							// 找到一个相邻可走方块，设find为true
							if (mg[i1][j1] == 0) {
								find = true;
							}
						}
						if (find) {
							// 找到修改栈顶元素信息
							st->data[st->top].dire = di;
							e.i = i1; e.j = j1; e.dire = -1;
							Push(st, e);    // 将相邻可走方块进栈
							mg[i1][j1] = -1;    // 设为-1，避免重新走上
						} else {
							// 没有路径可走，退栈
							Pop(st, e);
							mg[e.i][e.j] = 0;
						}
					}
					DestroyStack(st);
					return false;
				}

			} // END namespace _3_1_4_2 求解迷宫问题

		} // END namespace _3_1_4 栈的应用

	} // END namespace _3_1 栈

	// 3.2 队列（queue）
	// 最后修改：2019-9-19
	namespace _3_2 {
		// 泛型队列
		// 实现基于顺序队列
		// 最后修改：2019-9-19
		namespace aq_3_2 {
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

		} // END namespace aq_3_2 泛型队列

		// 3.2.1 队列的定义
		// 队头或队首（front）、队尾（rear）、进队或入队（enqueue）、出队或离队（dequeue）
		// 先进先出（First In First Out，FIFO）
		// 最后修改：2019-9-17
		namespace _3_2_1 {
			// 队列抽象数据类型的定义如下
			/*
			ADT Queue {
				数据对象:
					D = { ai | 1 <= i <= n, n >= 0, ai为ElemType类型 }    // ElemType 是自定义类型标识符
				数据关系:
					R = { <ai,a(i+1)> | ai, a(i+1) ∈ D, i = 1,...,n-1 }
				基本运算:
					InitQueue(&q)
					DestroyQueue(&q)
					QueueEmpty(q)
					enQueue(&q,e)
					deQueue(&q,&e)
			}
			*/
		} // END namespace _3_2_1 队列的定义

		// 3.2.2 队列的顺序存储结构及其基本运算的实现
		// 最后修改：2019-9-17
		namespace _3_2_2 {
			// 3.2.2.1 顺序队中实现队列的基本运算
			// 顺序队（sequential queue）
			// 队空：front == rear， 队满：rear == MaxSize - 1
			// 会出现判断为队满，但实际队为空的情况，即假溢出（false overflow）
			// 顺序空间存储，出队元素不被覆盖，最多MaxSize-1个元素
			// 元素类型：int
			// 最后修改：2019-9-17
			namespace _3_2_2_1 {
				const int MaxSize = 50;
				typedef int ElemType;

				typedef struct {
					ElemType data[MaxSize];    // 存放队中元素
					int front;    // 队头, 指向头元素的前一个
					int rear;    // 队尾，指向尾元素
				} SqQueue;    // 顺序队类型

				// 初始化队列 InitQueue(&q) O(1)
				void InitQueue(SqQueue*& q) {
					q = (SqQueue*)malloc(sizeof(SqQueue));
					q->front = q->rear = -1;
				}
				// 销毁队列 DestroyQueue(&q) O(1)
				void DestroyQueue(SqQueue*& q) {
					free(q);
				}
				// 判断队列是否为空 QueueEmpty(q) O(1)
				bool QueueEmpty(SqQueue* q) {
					return (q->front == q->rear);
				}
				// 进队列 enQueue(&q, e) O(1)
				bool enQueue(SqQueue*& q, ElemType e) {
					if (q->rear == MaxSize - 1) {
						return false;    // 队满返回false
					}
					++q->rear;
					q->data[q->rear] = e;
					return true;
				}
				// 出队列 deQueue(&q, &e) O(1)
				bool deQueue(SqQueue*& q, ElemType& e) {
					if (q->front == q->rear) {
						return false;    // 队空返回false，此处空为伪空
					}
					++q->front;    // front指向头元素的前一位置
					e = q->data[q->front];
					return true;
				}

			} // END namespace _3_2_2_1 顺序队中实现队列的基本运算

			// 3.2.2.2 环形队中实现队列的基本运算
			// 环形队列或循环队列（circular queue）
			// 逻辑上看成一个环，注意取余运算
			// 队空：front == rear， 队满：(rear + 1) % MaxSize = front
			// 重复利用空间，出队元素可能被覆盖, 最多MaxSize-1个元素
			// 元素类型：int
			// 最后修改：2019-9-17
			namespace _3_2_2_2 {
				const int MaxSize = 50;
				typedef int ElemType;

				typedef struct {
					ElemType data[MaxSize];    // 存放队中元素
					int front;    // 队头, 指向头元素的前一个
					int rear;    // 队尾，指向尾元素
				} SqQueue;    // 顺序队类型

				// 初始化队列 InitQueue(&q) O(1)
				void InitQueue(SqQueue*& q) {
					q = (SqQueue*)malloc(sizeof(SqQueue));
					q->front = q->rear = 0;
				}
				// 销毁队列 DestroyQueue(&q) O(1)
				void DestroyQueue(SqQueue*& q) {
					free(q);
				}
				// 判断队列是否为空 QueueEmpty(q) O(1)
				bool QueueEmpty(SqQueue* q) {
					return (q->front == q->rear);
				}
				// 进队列 enQueue(&q, e) O(1)
				bool enQueue(SqQueue*& q, ElemType e) {
					if ((q->rear + 1) % MaxSize == q->front) {
						return false;    // 队满返回false
					}
					q->rear = (q->rear + 1) % MaxSize;
					q->data[q->rear] = e;
					return true;
				}
				// 出队列 deQueue(&q, &e) O(1)
				bool deQueue(SqQueue*& q, ElemType& e) {
					if (q->front == q->rear) {
						return false;    // 队空返回false，此处空为伪空
					}
					q->front = (q->front + 1) % MaxSize;    // front指向头元素的前一位置
					e = q->data[q->front];
					return true;
				}

			} // END namespace _3_2_2_2 环形队中实现队列的基本运算

			// 例3.7 用元素个数代替尾指针，可存MaxSize个元素
			// 队尾指针计算公式：rear = (front + count) % MaxSize
			// 队空：count == 0， 队满：count == MaxSize
			// 元素类型：int
			// 最后修改：2019-9-17
			namespace _3_2_2_3 {
				const int MaxSize = 50;
				typedef int ElemType;

				typedef struct {
					ElemType data[MaxSize];
					int front;    // 队头指针，指向头元素的前一个元素
					int count;    // 元素个数
				} QuType;    // 环形队列的类型

				// 初始化
				void InitQueue(QuType*& qu) {
					qu = (QuType*)malloc(sizeof(QuType));
					qu->front = 0;    // 队头指针设为0
					qu->count = 0;
				}

				// 销毁队列
				void DestroyQueue(QuType*& qu) {
					free(qu);
				}

				// 队列是否为空
				bool QueueEmpty(QuType* qu) {
					return (qu->count == 0);
				}

				// 进队
				bool EnQueue(QuType*& qu, ElemType x) {
					if (qu->count == MaxSize) {
						return false;    // 队满，返回false
					}
					int rear = (qu->front + qu->count) % MaxSize;    // 计算尾指针
					rear = (rear + 1) % MaxSize;
					qu->data[rear] = x;
					++qu->count;
					return true;
				}

				// 出队
				bool DeQueue(QuType*& qu, ElemType& x) {
					if (qu->count == 0) {
						return false;    // 队空，返回false
					}
					qu->front = (qu->front + 1) % MaxSize;
					x = qu->data[qu->front];
					--qu->count;
					return true;
				}

			} // END namespace _3_2_2_3 例3.7

		} // END namespace _3_2_2 队列的顺序存储结构及其基本运算的实现

		// 3.2.3 队列的链式存储结构及其基本运算的实现
		// 链队（linked queue）
		// 最后修改：2019-9-19
		namespace _3_2_3 {
			// 第一种实现：
			// 头结点包括两个指针：front和rear
			// 数据结点：数据和下一个结点的指针next
			// 队空条件：rear == NULL 或 front == NULL 两种都可
			// 注意判断队空或只有一个元素时的特殊情况
			// 元素类型：int
			// 最后修改：2019-9-19
			namespace _3_2_3_1 {
				// 元素类型
				typedef int ElemType;

				// 数据结点类型
				typedef struct qnode {
					ElemType data;    // 存放元素
					struct qnode* next;    // 下一个结点指针
				} DataNode;

				// 头结点类型
				typedef struct {
					DataNode* front;    // 指向队列首结点
					DataNode* rear;    // 指向队列尾结点
				} LinkQuNode;

				// 初始化队列 O(1)
				void InitQueue(LinkQuNode*& q) {
					q = (LinkQuNode*)malloc(sizeof(LinkQuNode));
					q->front = q->rear = NULL;
				}

				// 销毁队列 O(n)
				void DestroyQueue(LinkQuNode*& q) {
					DataNode* pre = q->front, *p;    // pre指向队首结点
					if (pre != NULL) {
						p = pre->next;    // p指向pre的后继结点
						// p不为空循环
						while (p != NULL) {
							free(pre);    // 释放pre结点
							pre = p;
							p = p->next;    // p和pre同步后移
						}
						free(pre);    //p为空时跳出循环，此时pre指向最后一个结点，释放之
					}
					free(q);    // 最后释放链队的头结点
				}

				// 判断队列是否为空 O(1)
				bool QueueEmpty(LinkQuNode* q) {
					return (q->rear == NULL);
				}

				// 进队 O(1)
				// 先创建一个新结点存放数据，进队该结点
				// 若原队列为空，则front和rear都指向新结点
				// 原队列非空，则尾结点的next指向新结点，更新尾结点
				void enQueue(LinkQuNode*& q, ElemType e) {
					DataNode* p = (DataNode*)malloc(sizeof(DataNode));
					p->data = e;
					p->next = NULL;    // 创建新结点并完成赋值操作
					if (q->rear == NULL) {
						q->rear = q->front = p;    // 原队列为空，则头和尾都指向p
					} else {
						q->rear->next = p;    // 原队列非空，在最后插入p（进队）
						q->rear = p;    // 更新尾结点
					}
				}

				// 出队列 O(1)
				bool deQueue(LinkQuNode*& q, ElemType &e) {
					if (q->rear == NULL) {
						return false;    // 队空，返回false
					}
					DataNode* t = q->front;    // t指向首结点
					if (q->front == q->rear) {
						q->front = q->rear = NULL;    // 原队列就一个结点，则出队后队列为空
					} else {
						q->front = t->next;    // 原队列有两个及以上元素，出队后，更新队首元素
					}
					e = t->data;    // 取出原队列的队首元素的数据
					free(t);
					return true;
				}

			} // END namespace _3_2_3_1

			// 第二种实现：
			// 例3.8 不带头结点，只有尾结点
			// 只有数据结点LinkNode，没有头结点，队尾结点的next指向首结点（循环链队）
			// 队空条件：rear == NULL
			// 元素类型：int
			// 最后修改：2019-9-19
			namespace _3_2_3_2 {
				// 元素类型
				typedef int ElemType;

				// 结点类型
				typedef struct LNode {
					ElemType data;
					struct LNode* next;
				} LinkNode;

				// 初始化算法 O(1)
				void InitQueue(LinkNode*& rear) {
					rear = NULL;
				}

				// 销毁队列 O(n)
				void DestroyQueue(LinkNode*& rear) {
					// 与 _3_2_3_1 种类似，只是用 p == rear 判断是否到达队尾
					if (rear == NULL) {
						return;    // 空队列直接返回
					}
					LinkNode* pre = rear->next, *p;
					if (pre != rear) {
						p = pre->next;
						while (p != rear) {
							free(pre);
							pre = p;
							p = pre->next;
						}
						free(pre);
					}
					free(rear);
				}

				// 判断队列是否为空 O(1)
				bool queueEmpty(LinkNode* rear) {
					return (rear == NULL);
				}

				// 进队 O(1)
				void enQueue(LinkNode*& rear, ElemType e) {
					LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
					p->data = e;
					if (rear == NULL) {
						p->next = p;    // 原队列为空，改为循环链表
						rear = p;    // rear指向新结点
					} else {
						// 原队列非空
						p->next = rear->next;    // p的next指向首结点
						rear->next = p;    // 当前尾结点的next指向p，即改为循环链队
						rear = p;    // 尾结点更新尾p
					}
				}

				// 出队 O(1)
				bool deQueue(LinkNode*& rear, ElemType& e) {
					if (rear == NULL) {
						return false;    // 队空返回false
					}
					if (rear->next == rear) {
						e = rear->data;
						free(rear);
						rear = NULL;    // 原队列只有个一个结点，出队后为空
					} else {
						LinkNode* t = rear->next;    // t指向首结点
						e = t->data;
						rear->next = t->next;    // 原队列有两个或两个以上的结点，去掉首结点
						free(t);
					}
					return true;
				}

			} // END namespace _3_2_3_2

		} // END namespace _3_2_3 队列的链式存储结构及其基本运算的实现

		// 3.2.4 队列的应用举例
		// 如果先存入的元素先处理，则采用队列
		// 注意之后是否还需用到出队元素，来选择队列的物理存储实现（原数据是否能覆盖）
		// 最后修改：2019-9-19
		namespace _3_2_4 {
			// 1.求解报数问题
			// n个人站一排，从左到右依次为1~n，从左到右报数“1 2 1 2 1 2....”
			// 报到1的出列，报到2的立即去到最右边，直到队伍为空，输出出列顺序
			// 接题思路，出队，为1直接出列，为2从最后再进队，不会再用到出队元素，采用循环队列
			// 最后修改：2019-9-19
			namespace _3_2_4_1 {
				// 引用循环队列
				using dst::_3_2::_3_2_2::_3_2_2_2::SqQueue;
				using dst::_3_2::_3_2_2::_3_2_2_2::ElemType;

				// 对应算法如下：
				void number(int n) {
					ElemType e;
					SqQueue* q;
					InitQueue(q);
					// 构建初始序列
					for (int i = 1; i <= n; ++i) {
						enQueue(q, i);
					}
					printf("报数出列顺序： ");
					while (!QueueEmpty(q)) {
						deQueue(q, e);    // 出列一个元素e，报1
						printf("%d ", e);    // 输出其编号
						if (!QueueEmpty(q)) {
							// 队列不为空，再出队一个元素，其报数为2，让其从队尾进队
							deQueue(q, e);
							enQueue(q, e);
						}
					}
					printf("\n");
					DestroyQueue(q);
				}


			} // END namespace _3_2_4_1 求解报数问题

			// 2.求解迷宫问题 （广度优先搜索）。// 给定一个 M x N 的迷宫，求一条从指定入口到出口的迷宫路径（非最短路径）
			// 用二维数组表示迷宫，1不可走，0可走，-1为相邻来的路径不可走
			// 一个方块(i,j)从上方开始顺时针编号 0 1 2 3 表示 上 右 下 左 四个方向
			// 当前位置(i,j)的相邻可走方块依次进队，出队重复，直到出口
			// 由于会再次用到出队元素，故使用顺序队列
			// 最后修改：2019-9-19
			namespace _3_2_4_2 {
				// 迷宫例子
				const int M = 8;
				const int N = 8;
				int mg[M + 2][N + 2] = {
					{1,1,1,1,1,1,1,1,1,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,1,0,0,0,1,0,1}, {1,0,0,0,0,1,1,0,0,1},
					{1,0,1,1,1,0,0,0,0,1}, {1,0,0,0,1,0,0,0,0,1}, {1,0,1,0,0,0,1,0,0,1}, {1,0,1,1,1,0,1,1,0,1},
					{1,1,0,0,0,0,0,0,0,1}, {1,1,1,1,1,1,1,1,1,1}
				};

				// 方块类型
				typedef struct {
					int i;
					int j;
					int pre;    // 本路径上前一个方块在队列中的下标
				} Box;

				// 引用泛型队列
				using dst::_3_2::aq_3_2::Queue;
				typedef Queue<Box, 100> QuType;
				const int MaxSize = 100;

				// 辅助方法：输出路径
				// 反向找到最短路径，将该路径上的方块的pre置为-1
				void printPath(QuType* qu, int front) {
					int k = front, j, ns = 0;
					printf("\n");
					do {
						j = k;
						k = qu->data[k].pre;
						qu->data[j].pre = -1;
					} while (k != 0);
					printf("一条迷宫路径如下：\n");
					k = 0;
					// 正向搜索pre为-1的方块，即构成正向的路径
					while (k < MaxSize) {
						if (qu->data[k].pre == -1) {
							++ns;
							printf("\t(%d,%d)", qu->data[k].i, qu->data[k].j);
							if (ns % 5 == 0) {
								printf("\n");
							}
						}
						++k;
					}
					printf("\n");
				}

				/*
				算法的伪代码描述如下：
				将入口(xi,yi)的pre置为-1，并进队;
				mg[xi][yi] = -1;
				while (队列qu不为空) {
					出队一个方块e，其在队列中的位置是front;
					if (方块e是出口) {
						输出一条迷宫路径;
						return true;
					}
					for (对于方块e的所有相邻的可走方块e1) {
						设置e1的pre为front;
						将方块e1进队;
						将方块e1的迷宫数组的值置为-1;
					}
				}
				return false;    // 没有路径，返回false
				*/
				bool mgpath(int xi, int yi, int xe, int ye) {
					Box e;
					int i, j, dire, i1, j1;
					QuType* qu;    // 声明顺序队列指针qu
					InitQueue(qu);
					e.i = xi; e.j = yi; e.pre = -1;
					enQueue(qu, e);    // (xi, yi)进队
					mg[xi][yi] = -1;    // 将其在二维数组中的值置为-1，避免重复搜索
					while (!QueueEmpty(qu)) {
						deQueue(qu, e);
						i = e.i; j = e.j;
						if (i == xe && j == ye) {
							// 找到出口，输出路径
							printPath(qu, qu->front);
							DestroyQueue(qu);
							return true;
						}
						// 扫描当前方块四周的方块，将可走的入队
						for (dire = 0; dire < 4; ++dire) {
							switch (dire) {
							case 0:
								i1 = i - 1; j1 = j; break;
							case 1:
								i1 = i; j1 = j + 1; break;
							case 2:
								i1 = i + 1; j1 = j; break;
							case 3:
								i1 = i; j1 = j - 1; break;
							}
							if (mg[i1][j1] == 0) {
								// 如果相邻方块可走，设置其属性，进队
								// pre指向上一方块在队列的顺序数组中的下标（由于出队，上一方块在队首，但front值为其在实现的数组中的下标位置）
								e.i = i1; e.j = j1; e.pre = qu->front;
								enQueue(qu, e);
								mg[i1][j1] = -1;    // 置为-1避免重复搜索
							}
						}
					}
					DestroyQueue(qu);
					return false;
				}

			} // END namespace _3_2_4_2 求解迷宫问题

		} // END namespace _3_2_4 队列的应用举例

		// 3.2.5 双端队列（deque，double-ended queue）
		// 两端都可以进行进队和出队的操作
		// 输入受限的双端队列 和 输出受限的双端队列
		namespace _3_2_5 {
			// 空
		} // END namespace _3_2_5 双端队列

	} // END namespace _3_2 队列

} // END namespace dst 数据结构教程

#endif // !DST_3_STACK_QUEUE_H