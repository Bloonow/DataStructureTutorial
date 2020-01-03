// Author��Akame Qisixi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_3_STACK_QUEUE_H
#include "dst_3_stack_queue.h"
#endif // DST_3_STACK_QUEUE_H

// �ϻ�ʵ����3
// P119 ʵ����5����ջ����Թ����������·�������·������
// Ŀ�ģ�����ջ������Թ������е�Ӧ��
// ���ݣ���дһ������exp3-5.cpp���Ľ�3.1.4�ڵ�����Թ��������
// Ҫ�����ͼ3.28��ʾ �Թ�������·���������һ�����·�����ȼ����·��
// ����޸ģ�2019-11-5
namespace experiment_3_5 {
	// ���Թ���6 x 6���ö�ά�����ʾ��0��ʾͨ·��1��ʾ�ϰ�
	int mg[6][6] = { {1,1,1,1,1,1}, {1,0,0,0,1,1}, {1,0,1,0,0,1},
				   {1,0,0,0,1,1}, {1,1,0,0,0,1}, {1,1,1,1,1,1} };

	// λ���࣬��ʾ�Թ��е�һ��λ��
	class Pos {
	private:
		// ��һ������λ�õķ���
		enum Next { UP = 0, RIGHT, DOWN, LEFT, NONE };
	private:
		int x;
		int y;
		Next next;     // ��һ��λ�õķ���
	public:
		Pos() : x(-1), y(-1), next(NONE) {}
		virtual ~Pos() {}
		Pos(int x, int y) {
			this->x = x;
			this->y = y;
			this->next = UP;    // ��ʼ����
		}

		int X() const { return x; }
		int Y() const { return y; }

		Pos& operator=(const Pos& target) {
			if (this == &target) {
				return *this;
			}
			this->x = target.x;
			this->y = target.y;
			this->next = target.next;
			return *this;
		}

		friend bool operator==(const Pos& a, const Pos& b) {
			return a.x == b.x && a.y == b.y;
		}

		Pos getNext() {
			// ˳ʱ�����
			switch (next) {
			case UP:
				this->next = RIGHT;
				return Pos(x - 1, y);
				break;
			case RIGHT:
				this->next = DOWN;
				return Pos(x, y + 1);
				break;
			case DOWN:
				this->next = LEFT;
				return Pos(x + 1, y);
				break;
			case LEFT:
				this->next = NONE;
				return Pos(x, y - 1);
				break;
			default:
				return Pos();
				break;
			}
		}

		// ��λ�õ���һ���Ƿ�Ϊ��
		bool isNextNone() const {
			return this->next == NONE;
		}
	};

	// �ж�pos�Ƿ����Թ���
	bool isPosInMg(const Pos& pos) {
		int x = pos.X();
		int y = pos.Y();
		if (x < 0 || x >5 || y < 0 || y > 5) {
			return false;
		}
		return true;
	}

	// �ж��Թ��е�λ���Ƿ����ͨ��
	bool isPosCanMove(const Pos& pos) {
		if (isPosInMg(pos)) {
			return mg[pos.X()][pos.Y()] == 0;
		}
		return false;
	}

	// ���Թ��е�λ����Ϊ����ͨ�������ϰ�
	void setPosNoMove(const Pos& pos) {
		if (isPosInMg(pos)) {
			mg[pos.X()][pos.Y()] = -1;
		}
	}

	// ���Թ��е�λ����Ϊ����ͨ��
	void setPosCanMove(const Pos& pos) {
		if (isPosInMg(pos)){
			mg[pos.X()][pos.Y()] = 0;
		}
	}

	using  namespace dst::_3_1::aq_3_1;    // ���÷���ջ

	typedef struct {
		Pos path[36];    // 6 x 6���Թ�������36��λ�ã��ʳ���Ϊ36���������Դ洢·��
		int posNum;
	} PosPath;    // �Թ�·������

	// ��������·��������
	PosPath* Path(const Pos& start, const Pos& end, int& pathNum, const int num = 12) {
		PosPath* allPath = new PosPath[num];    // �ٶ�Ĭ�����ֻ��12��·��
		pathNum = 0;
		Stack<Pos>* st;
		InitStack(st);
		// ��ڽ�ջ
		Push(st, start);
		Pos top;
		while (!StackEmpty(st)) {
			GetTop(st, top);
			if (top == end) {
				// ����һ��·������һ��ջ��ȡջ����next�������ж�
				int index = 0;
				while (!StackEmpty(st)) {
					Pos p;
					Pop(st, p);
					allPath[pathNum].path[index++] = p;
				}
				allPath[pathNum].posNum = index;
				for (int i = index - 1; i >=0; --i) {
					Pos p = allPath[pathNum].path[i];
					Push(st, p);
				}
				pathNum++;
				if (pathNum >= num) {
					return allPath;    // �ѵõ�ָ��������·����ֱ�ӷ���
				}

				Pop(st);
				setPosCanMove(top);
				//printf("get\n");
			}
			// ջ���ص�ջ��Ԫ�ط�ջ�������ã��޸�֮��ջ��Ԫ�ز���仯������pop���޸ĺ���push
			Pop(st, top);
			Pos nextPos = top.getNext();
			Push(st, top);
			setPosNoMove(top);    // ������ջ��λ�ò���ͨ��
			// �ұ�ջ��Ԫ�ص�����λ��
			while (!nextPos.isNextNone()) {
				if (isPosCanMove(nextPos)) {
					Push(st, nextPos);    // ����λ�ÿ��ߣ���ջ
					break;
				} else {
					Pop(st, top);
					nextPos = top.getNext();    // ����λ�ò����ߣ�ȡ��һ������λ��
					Push(st, top);
				}
			}
			// ��ջ��Ԫ�ص�����λ�����ұ飬��ջ������λ�ûָ�Ϊ����
			if (nextPos.isNextNone()) {
				Pop(st);
				setPosCanMove(top);
			}
		}
		DestroyStack(st);
		return allPath;
	}

	// �������·��
	void printAllPath() {
		int pathNum = 0;
		Pos start(1, 1), end(4, 4);
		PosPath* allPath = Path(start, end, pathNum);
		int minPathIndex = -1;
		int minPathNum = 36;
		for (int pathIndex = 0; pathIndex < pathNum; ++pathIndex) {
			if (minPathNum > allPath[pathIndex].posNum) {
				minPathNum = allPath[pathIndex].posNum;
				minPathIndex = pathIndex;
			}
			for (int i = allPath[pathIndex].posNum - 1; i > 0; --i) {
				printf("(%d,%d) => ", allPath[pathIndex].path[i].X(), allPath[pathIndex].path[i].Y());
			}
			printf("(%d,%d)\n", allPath[pathIndex].path[0].X(), allPath[pathIndex].path[0].Y());
		}
		if (minPathIndex == -1) {
			printf("û��·��\n");
		} else {
			printf("��һ�����·��Ϊ�� %d ��������Ϊ��%d\n", minPathIndex + 1, minPathNum);
		}
	}

	void exp3_5() {
		printAllPath();
	}

} // END namespace experiment_3_5
