// Author：Akame Qisixi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_3_STACK_QUEUE_H
#include "dst_3_stack_queue.h"
#endif // DST_3_STACK_QUEUE_H

// 上机实验题3
// P119 实验题5：用栈求解迷宫问题的所有路径及最短路径程序
// 目的：掌握栈在求解迷宫问题中的应用
// 内容：编写一个程序exp3-5.cpp，改进3.1.4节的求解迷宫问题程序，
// 要求输出图3.28所示 迷宫的所有路径，并求第一条最短路径长度及最短路径
// 最后修改：2019-11-5
namespace experiment_3_5 {
	// 该迷宫（6 x 6）用二维数组表示，0表示通路，1表示障碍
	int mg[6][6] = { {1,1,1,1,1,1}, {1,0,0,0,1,1}, {1,0,1,0,0,1},
				   {1,0,0,0,1,1}, {1,1,0,0,0,1}, {1,1,1,1,1,1} };

	// 位置类，表示迷宫中的一个位置
	class Pos {
	private:
		// 下一个相邻位置的方向
		enum Next { UP = 0, RIGHT, DOWN, LEFT, NONE };
	private:
		int x;
		int y;
		Next next;     // 下一个位置的方向
	public:
		Pos() : x(-1), y(-1), next(NONE) {}
		virtual ~Pos() {}
		Pos(int x, int y) {
			this->x = x;
			this->y = y;
			this->next = UP;    // 初始向上
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
			// 顺时针遍历
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

		// 该位置的下一个是否为空
		bool isNextNone() const {
			return this->next == NONE;
		}
	};

	// 判断pos是否在迷宫内
	bool isPosInMg(const Pos& pos) {
		int x = pos.X();
		int y = pos.Y();
		if (x < 0 || x >5 || y < 0 || y > 5) {
			return false;
		}
		return true;
	}

	// 判断迷宫中的位置是否可以通过
	bool isPosCanMove(const Pos& pos) {
		if (isPosInMg(pos)) {
			return mg[pos.X()][pos.Y()] == 0;
		}
		return false;
	}

	// 将迷宫中的位置设为不可通过，即障碍
	void setPosNoMove(const Pos& pos) {
		if (isPosInMg(pos)) {
			mg[pos.X()][pos.Y()] = -1;
		}
	}

	// 将迷宫中的位置设为可以通过
	void setPosCanMove(const Pos& pos) {
		if (isPosInMg(pos)){
			mg[pos.X()][pos.Y()] = 0;
		}
	}

	using  namespace dst::_3_1::aq_3_1;    // 引用泛型栈

	typedef struct {
		Pos path[36];    // 6 x 6的迷宫，最多就36个位置，故长度为36的数组足以存储路径
		int posNum;
	} PosPath;    // 迷宫路径类型

	// 返回所有路径的数组
	PosPath* Path(const Pos& start, const Pos& end, int& pathNum, const int num = 12) {
		PosPath* allPath = new PosPath[num];    // 假定默认最多只有12条路径
		pathNum = 0;
		Stack<Pos>* st;
		InitStack(st);
		// 入口进栈
		Push(st, start);
		Pos top;
		while (!StackEmpty(st)) {
			GetTop(st, top);
			if (top == end) {
				// 生成一个路径，退一个栈，取栈顶的next，继续判断
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
					return allPath;    // 已得到指定数量的路径，直接返回
				}

				Pop(st);
				setPosCanMove(top);
				//printf("get\n");
			}
			// 栈返回的栈顶元素非栈顶的引用，修改之，栈顶元素不会变化，故先pop，修改后再push
			Pop(st, top);
			Pos nextPos = top.getNext();
			Push(st, top);
			setPosNoMove(top);    // 先设置栈顶位置不可通过
			// 找遍栈顶元素的相邻位置
			while (!nextPos.isNextNone()) {
				if (isPosCanMove(nextPos)) {
					Push(st, nextPos);    // 相邻位置可走，进栈
					break;
				} else {
					Pop(st, top);
					nextPos = top.getNext();    // 相邻位置不可走，取下一个相邻位置
					Push(st, top);
				}
			}
			// 若栈顶元素的相邻位置已找遍，退栈，设其位置恢复为可走
			if (nextPos.isNextNone()) {
				Pop(st);
				setPosCanMove(top);
			}
		}
		DestroyStack(st);
		return allPath;
	}

	// 输出所有路径
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
			printf("没有路径\n");
		} else {
			printf("第一条最短路径为第 %d 条，长度为：%d\n", minPathIndex + 1, minPathNum);
		}
	}

	void exp3_5() {
		printAllPath();
	}

} // END namespace experiment_3_5
