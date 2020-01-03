// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_5_RECURSION_H
#define DST_5_RECURSION_H

// 第五章：递归

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 5.1 什么是递归（recursion）
	// 直接递归（direct recursion）、间接递归（indirect recursion）
	// 尾递归（tail recursion）
	// 递归出口（recursive exit）、递归体（recursive body）
	// 递归链（链长即深度）、递归树（树高即深度）
	// 递归与数学归纳法
	// 5.2 栈和递归
	// 栈帧（stack frame）
	// 递归转换成非递归：借助栈保存状态，注意转换成栈后的入退栈顺序
	// 5.3 递归算法的设计
	// 最后修改：2019-9-26
	namespace _5 {
		// 汉诺塔（Hanoi Tower）
		// 描述：从上到下，从小到大，从1到n，在塔座X上，移动到Z上，要求大的必须在小的下面，可借助Y，最终顺序不变
		// 解题思路：1. 将X塔上的n-1个借助Z移动到Y上 Hanoi(n-1, x, z, y)
		// 2. 将X上最后一个最大的移到Z上 Move(n, x, z)
		// 3. 再将Y上的n-1个借助X塔移动到Z塔上 Hanoi(n-1, y, x, z)
		// 4. 重复上述步骤，直到 n == 1，即剩下最后一个
		// 如果一共有n个盘片，则需要2^n-1次移动
		// 最后修改：2019-9-26
		namespace _5_hanoi {
			// 递归算法实现汉诺塔
			// 最后修改：2019-9-26
			namespace _5_hanoi_1 {
				// 移动一个塔盘函数
				void Move(int no, char from, char dest) {
					printf("第 %d 个盘片： %c  ==>  %c \n", no, from, dest);
				}

				// 递归算法实现汉诺塔
				void Hanoi(int n, char from, char help, char dest) {
					if (n == 1) {
						Move(n, from, dest);    // 只有一个盘片，能够直接移动到目标塔座
					} else {
						Hanoi(n - 1, from, dest, help);
						Move(n, from, dest);
						Hanoi(n - 1, help, from, dest);
					}
				}
			} // END namespace _5_hanoi_1 递归算法实现汉诺塔

			// 非递归算法实现汉诺塔
			// 用栈帧存储调用信息，借助泛型栈
			// 栈深开到100，最多能处理约30左右个盘片
			// 将 Hanoi(n, form, help, dest)进栈，栈非空是循环
			// 出栈一个元素，若可直接移动，则指向Move
			// 否则，分解成n-1的信息，按如下顺序进栈：
			// Hanoi(n-1, help, from, dest)、Move(n, from, dest)、Hanoi(n-1, from, dest, help)
			// 最后修改：2019-9-26
			namespace _5_hanoi_2 {
				// 栈帧存储函数参数调用信息
				typedef struct {
					int n;    // 盘片个数
					char from, help, dest;    // 3个塔座
					bool canMove;    // 能否直接移动
				} ParamInfo;

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

				typedef dep::Stack<ParamInfo, 100> StackType;

				// 移动一个塔盘函数
				void Move(int no, char from, char dest) {
					printf("第 %d 个盘片： %c  ==>  %c \n", no, from, dest);
				}

				// 非递归算法实现汉诺塔
				void Hanoi(int n, char from, char help, char dest) {
					if (n <= 0) {
						return;    // 参数错误时直接返回
					}
					StackType* stateStack;
					InitStack(stateStack);
					ParamInfo e, toDest, toMove, toHelp;    // 存储函数参数调用信息
					e.n = n; e.from = from; e.help = help; e.dest = dest; e.canMove = false;
					Push(stateStack, e);    // 移动n个盘片的信息进栈
					// 栈不为空循环
					while (!StackEmpty(stateStack)) {
						Pop(stateStack, e);    // 从栈顶出栈一个函数调用参数信息
						// 若不能直接移动，即非最底的，分解
						if (e.canMove == false) {
							toDest.n = e.n - 1; toDest.from = e.help; toDest.help = e.from; toDest.dest = e.dest;
							if (toDest.n == 1) {
								toDest.canMove = true;    // 为最后一个盘片时，可以直接移动
							} else {
								toDest.canMove = false;
							}
							Push(stateStack, toDest);    // 进栈 Hanoi(n-1, help, from, dest)
							toMove.n = e.n; toMove.from = e.from; toMove.help = e.help; toMove.dest = e.dest; toMove.canMove = true;
							Push(stateStack, toMove);    // 进栈 Move(n, from, dest)
							toHelp.n = e.n - 1; toHelp.from = e.from; toHelp.help = e.dest; toHelp.dest = e.help;
							if (toHelp.n == 1) {
								toHelp.canMove = true;   // 为最后一个盘片时，可以直接移动
							} else {
								toHelp.canMove = false;
							}
							Push(stateStack, toHelp);    // 进栈 Hanoi(n-1, form, dest, help)
						} else {
							// 能直接移动
							Move(e.n, e.from, e.dest);
						}
					}
					DestroyStack(stateStack);    // 销毁栈
				}

			} // END namespace _5_hanoi_2 非递归算法实现汉诺塔

		} // END namespace _5_hanoi 汉诺塔

	} // END namespace _5 递归

} // END namespace dst 数据结构教程

#endif // !DST_5_RECURSION_H