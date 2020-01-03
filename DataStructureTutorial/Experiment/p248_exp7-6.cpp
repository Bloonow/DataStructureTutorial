// Author��Akame Qisixi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_7_TREE_BINARY_TREE_H
#include "dst_7_tree_binary_tree.h"
#endif // DST_7_TREE_BINARY_TREE_H

// �ϻ�ʵ����7
// P248 ʵ����6����������еĽ�������Ҷ�ӽ�������ĳ����κͶ��������
// Ŀ�ģ����ն����������㷨��Ӧ�ã���Ϥʹ���������򡢺���3�ֵݹ�����㷨�Ͳ�α����㷨���ж�������������
// ���ݣ���дһ������exp7-6.cppʵ�����¹��ܣ�����ͼ7.33��ʾ�Ķ�����������֤
// (1)�����������b�Ľ�����
// (2)�����������b��Ҷ�ӽ�����
// (3)���������b��ָ�����ֵ���������н���ֵ��ͬ���Ľ��Ĳ��
// (4)�����ò�α����������b�Ŀ��
// ����޸ģ�2019-12-03
namespace experiment_7_6 {

	using dst::_7_3::_7_3_2::BTNode;
	using dst::_7_3::_7_3_2::ElemType;

	// dependency ����
	namespace dep {
		// ���Ͷ���
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
	} // END namespace dep ����

	// ���������ö������洢�������н�����
	int Nodes(BTNode* b) {
		if (b == NULL) {
			return 0;
		} else {
			return Nodes(b->lchild) + Nodes(b->rchild) + 1;
		}
	}

	// ���������ö������洢���������Ҷ�ӽ��
	int LeafNodes(BTNode* b) {
		if (b != NULL) {
			if (b->lchild == NULL && b->rchild == NULL) {
				return 1;
			}
			return LeafNodes(b->lchild) + LeafNodes(b->rchild);
		}
		return 0;
	}

	// ���������ö������洢����ֵΪx�Ľ�������еĲ��
	// ����ʱ��h = 1
	int Level(BTNode* b, ElemType x, int h) {
		// h ��ʾ ��� b �����еĵڼ��㣬���ⲿ����ʱ��ʼֵӦ��Ϊ1
		if (b == NULL) {
			return 0;
		} else if (b->data == x) {
			return h;
		} else {
			int lev = Level(b->lchild, x, h + 1);    // ���������в���
			// lev��Ϊ�㣬��ʾ�����������ҵ���
			if (lev != 0) {
				return lev;
			} else {
				// û�����������ҵ����������������в��ҵĽ��
				return Level(b->rchild, x, h + 1);
			}
		}
	}

	// ��α�����Ϊ��
	// �Ƚ��������ӣ��Ӳ�Ϊ��ʱѭ����������������ӣ����Һ�������ӣ���˲���ֱ���ӿ�
	int LevelOrderForWidth(BTNode* b) {
		typedef struct {
		BTNode* bt;
		int level;
		} QuNode;  // ������Ԫ�ص����ͣ�Ϊȷ�����н��Ĳ�Σ������м����� level ��
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
			// ����ǰ����Ѿ��ı䣬������Ӧ����
			if (p->level != curLevel) {
				curLevel = p->level;
				if (maxLevelWidth < curLevelWidth) {
					maxLevelWidth = curLevelWidth;
				}
				curLevelWidth = 1;
			} else {
				// ��ǰ�������һ�����ͬһ��Σ���ǰ��ο����1
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
		printf("���������£�\n");
		dst::_7_4::DispBTree(bt);
		
		printf("\n(1)�����������b�Ľ�����: %d\n", Nodes(bt));
		printf("(2)�����������b��Ҷ�ӽ�����: %d\n", LeafNodes(bt));
		printf("(3)���������b��ָ�����ֵ�Ľ��Ĳ�Σ����� %c �Ĳ��Ϊ %d \n", 'N', Level(bt, 'N', 1));
		printf("(4)�����ò�α����������b�Ŀ��: %d\n", LevelOrderForWidth(bt));

		dst::_7_4::DstroyBTree(bt);
	}

} // END namespace experiment_7_6