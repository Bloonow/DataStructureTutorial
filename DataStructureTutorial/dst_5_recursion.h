// Author��Akame Qixisi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_5_RECURSION_H
#define DST_5_RECURSION_H

// �����£��ݹ�

// ���ݽṹ�̳̣���5�棩 �廪��ѧ������
// Data Structure Tutorial
namespace dst {
	// 5.1 ʲô�ǵݹ飨recursion��
	// ֱ�ӵݹ飨direct recursion������ӵݹ飨indirect recursion��
	// β�ݹ飨tail recursion��
	// �ݹ���ڣ�recursive exit�����ݹ��壨recursive body��
	// �ݹ�������������ȣ����ݹ��������߼���ȣ�
	// �ݹ�����ѧ���ɷ�
	// 5.2 ջ�͵ݹ�
	// ջ֡��stack frame��
	// �ݹ�ת���ɷǵݹ飺����ջ����״̬��ע��ת����ջ�������ջ˳��
	// 5.3 �ݹ��㷨�����
	// ����޸ģ�2019-9-26
	namespace _5 {
		// ��ŵ����Hanoi Tower��
		// ���������ϵ��£���С���󣬴�1��n��������X�ϣ��ƶ���Z�ϣ�Ҫ���ı�����С�����棬�ɽ���Y������˳�򲻱�
		// ����˼·��1. ��X���ϵ�n-1������Z�ƶ���Y�� Hanoi(n-1, x, z, y)
		// 2. ��X�����һ�������Ƶ�Z�� Move(n, x, z)
		// 3. �ٽ�Y�ϵ�n-1������X���ƶ���Z���� Hanoi(n-1, y, x, z)
		// 4. �ظ��������裬ֱ�� n == 1����ʣ�����һ��
		// ���һ����n����Ƭ������Ҫ2^n-1���ƶ�
		// ����޸ģ�2019-9-26
		namespace _5_hanoi {
			// �ݹ��㷨ʵ�ֺ�ŵ��
			// ����޸ģ�2019-9-26
			namespace _5_hanoi_1 {
				// �ƶ�һ�����̺���
				void Move(int no, char from, char dest) {
					printf("�� %d ����Ƭ�� %c  ==>  %c \n", no, from, dest);
				}

				// �ݹ��㷨ʵ�ֺ�ŵ��
				void Hanoi(int n, char from, char help, char dest) {
					if (n == 1) {
						Move(n, from, dest);    // ֻ��һ����Ƭ���ܹ�ֱ���ƶ���Ŀ������
					} else {
						Hanoi(n - 1, from, dest, help);
						Move(n, from, dest);
						Hanoi(n - 1, help, from, dest);
					}
				}
			} // END namespace _5_hanoi_1 �ݹ��㷨ʵ�ֺ�ŵ��

			// �ǵݹ��㷨ʵ�ֺ�ŵ��
			// ��ջ֡�洢������Ϣ����������ջ
			// ջ���100������ܴ���Լ30���Ҹ���Ƭ
			// �� Hanoi(n, form, help, dest)��ջ��ջ�ǿ���ѭ��
			// ��ջһ��Ԫ�أ�����ֱ���ƶ�����ָ��Move
			// ���򣬷ֽ��n-1����Ϣ��������˳���ջ��
			// Hanoi(n-1, help, from, dest)��Move(n, from, dest)��Hanoi(n-1, from, dest, help)
			// ����޸ģ�2019-9-26
			namespace _5_hanoi_2 {
				// ջ֡�洢��������������Ϣ
				typedef struct {
					int n;    // ��Ƭ����
					char from, help, dest;    // 3������
					bool canMove;    // �ܷ�ֱ���ƶ�
				} ParamInfo;

				// dependence ����
				namespace dep {
					// ����ջ
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
				} // END namespace dep ����

				typedef dep::Stack<ParamInfo, 100> StackType;

				// �ƶ�һ�����̺���
				void Move(int no, char from, char dest) {
					printf("�� %d ����Ƭ�� %c  ==>  %c \n", no, from, dest);
				}

				// �ǵݹ��㷨ʵ�ֺ�ŵ��
				void Hanoi(int n, char from, char help, char dest) {
					if (n <= 0) {
						return;    // ��������ʱֱ�ӷ���
					}
					StackType* stateStack;
					InitStack(stateStack);
					ParamInfo e, toDest, toMove, toHelp;    // �洢��������������Ϣ
					e.n = n; e.from = from; e.help = help; e.dest = dest; e.canMove = false;
					Push(stateStack, e);    // �ƶ�n����Ƭ����Ϣ��ջ
					// ջ��Ϊ��ѭ��
					while (!StackEmpty(stateStack)) {
						Pop(stateStack, e);    // ��ջ����ջһ���������ò�����Ϣ
						// ������ֱ���ƶ���������׵ģ��ֽ�
						if (e.canMove == false) {
							toDest.n = e.n - 1; toDest.from = e.help; toDest.help = e.from; toDest.dest = e.dest;
							if (toDest.n == 1) {
								toDest.canMove = true;    // Ϊ���һ����Ƭʱ������ֱ���ƶ�
							} else {
								toDest.canMove = false;
							}
							Push(stateStack, toDest);    // ��ջ Hanoi(n-1, help, from, dest)
							toMove.n = e.n; toMove.from = e.from; toMove.help = e.help; toMove.dest = e.dest; toMove.canMove = true;
							Push(stateStack, toMove);    // ��ջ Move(n, from, dest)
							toHelp.n = e.n - 1; toHelp.from = e.from; toHelp.help = e.dest; toHelp.dest = e.help;
							if (toHelp.n == 1) {
								toHelp.canMove = true;   // Ϊ���һ����Ƭʱ������ֱ���ƶ�
							} else {
								toHelp.canMove = false;
							}
							Push(stateStack, toHelp);    // ��ջ Hanoi(n-1, form, dest, help)
						} else {
							// ��ֱ���ƶ�
							Move(e.n, e.from, e.dest);
						}
					}
					DestroyStack(stateStack);    // ����ջ
				}

			} // END namespace _5_hanoi_2 �ǵݹ��㷨ʵ�ֺ�ŵ��

		} // END namespace _5_hanoi ��ŵ��

	} // END namespace _5 �ݹ�

} // END namespace dst ���ݽṹ�̳�

#endif // !DST_5_RECURSION_H