﻿// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_10_INTERNAL_SORT_H
#define DST_10_INTERNAL_SORT_H

// 第十章：内排序

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 10.1 排序（sort）的基本概念
	// 最后修改：2019-11-21
	namespace _10_1 {
		// 10.1.1 什么是排序
		// 一组元素组成的表，指定一个数据项为关键字作为排序运算的依据
		// 所谓排序就是要整理表中的元素，使之按关键字递增或递减有序排列

		// 10.1.2 排序的稳定性
		// 当一维表中的元素关键字都不同时，排序结果唯一，否则不唯一
		// 对于存在多个相同关键字的一维表，如果相同关键字的元素的相对次序在排序后不变，
		// 则称这种算法是稳定的（stable），否则为不稳定的（unstable）

		// 10.1.3 内排序和外排序
		// 若整个表都存在于内存中，排序时不涉及数据的内、外存交换，则称之为内排序（internal sort）
		// 若存在内、外存交换，则称之为外排序（external sort）

		// 10.1.4 基于比较的排序算法的性能
		// 其主要进行两种基本操作：比较（compare）和移动（move）
		// 若待排序元素的关键字顺序正好和排序顺序相同，称此表中元素为正序；反之则为反序
		// 对于 n 个元素排序结果有 n! 种情况，对应的判定树是一颗有 n! 个叶子结点的高度最小的二叉树，分支节点个数为0，总结点数 = n0+n2 = 2n! - 1
		// 其高度 h = ⌈log2(2n!)⌉ = ⌈log2(n!)⌉ + 1，关键字比较次数最多的次数为 c = h - 1 = ⌈log2(n!)⌉ ≈ nlog2(n)
		// 故从平均情况看，大约需要 nlog2(n) 次关键字比较（所有 n! 种排序情况的关键字比较次数的平均值）
		// 移动次数 和 比较次数 也是相同的数量级，
		// 所以基于比较的排序算法最好的平均时间复杂度为 O(nlog2(n))

		// 10.1.5 排序数据的组织
		// 最后修改：2019-11-21
		namespace _10_1_5 {
			typedef int KeyType;    // 定义关键字类型为 int
			//typedef int InfoType;    // 其他数据类型
			typedef struct {
				KeyType key;    // 关键字项
				//InfoType data;    // 其他数据项
			} RecType;    // 排序元素的类型

		} // END namespace _10_1_5 排序数据的组织

	} // END namespace _10_1 排序的基本概念

	// 10.2 插入排序（insertion sort）
	// 默认：递增排序
	// 最后修改：2019-12-17
	namespace _10_2 {
		// 插入排序的基本思想：每次将一个待排序的元素按其关键字大小插入到前面已经排序好的子表中的适当位置，直到全部元素插入完成为止
		// 直接插入排序（straight insertion sort），折半插入排序（binary insertion sort），希尔排序（shell sort）

		// 10.2.1 直接插入排序（straight insertion sort）
		// 默认：递增排序
		// 最后修改：2019-11-21
		namespace _10_2_1 {
			// 10.2.1.1 排序思路
			// 假设待排序的元素存放在 R[0...n-1]中，在排序过程中，其被分为连个子区间
			// 已经排好的有序区（ordered region）R[0...i-1]，和未排序的无序区（disordered region）R[i...n-1]
			// 直接插入排序（straight insertion sort）的一趟操作是将当前无序区的开头元素 R[i] 插入到有序区中的适当位置，使 R[0...i] 变为有序区
			// 这种方法通常称为 增量法，因为它每次使有序区增加一个元素
			// 说明：直接插入排序每趟产生的有序区并不一定使全局有序区，就是说有序区中的元素并不一定放在排序完的最终位置上
			// 当一个元素在整个排序过程中就已经放在其最终位置上称为归位（homing）

			// 引用排序元素类型
			using _10_1::_10_1_5::RecType;

			// 10.2.1.2 排序算法
			/* 直接插入排序（递增排序），O(n方)
			先将 R[i] 暂存到 tmp 中
			j 在有序区中从后向前查找（j初值为i-1），凡是关键字大于 temp.key 的记录均后移一个位置，
			直到找到某个位置 j，有 R[j].key <= tmp.key，则将 tmp 放在 R[j] 的后面
			*/
			void InsertSort(RecType R[], int n) {
				RecType tmp;
				int j;    // 用来从后向前遍历 有序区R[0...i-1]
				// n-1 趟
				for (int i = 1; i < n; ++i) {
					// 若 i 比 i - 1 位置小，即不符合递增，应对其排序
					if (R[i].key < R[i - 1].key) {
						tmp = R[i];
						j = i - 1;
						// 寻找 R[i] 的插入位置
						do {
							R[j + 1] = R[j];    // 将关键字大于 R[i].key 的记录后移
							--j;
						} while (j >= 0 && R[j].key > tmp.key);
						// 最后 j 指向第一个小于 R[i]（tmp）的元素，j + 1 即插入位置
						R[j + 1] = tmp;    // 在 j+1 处插入 R[i]
					}
				}
			}

			// 10.2.1.3 算法分析
			// 当初始数据不同时，直接插入排序所耗费的时间有很大的差异
			// 最好的情况是表初态为正序，此时算法的最好时间复杂度为 O(n)；最坏的情况是表初态为反序，此时算法的最坏时间复杂度为 O(n^2)
			// 算法的平均时间复杂度为 O(n^2)，也就是说算法的平均时间复杂度接近最坏情况
			// 算法中使用的辅助变量与问题规模 n 无关，故算法辅助空间复杂度为 O(1)，也就是说它是一个就地排序算法
			// 另外在算法运行中，保持元素的相对顺序不变，故该算法是一种稳定的排序方法

		} // END namespace _10_2_1 直接插入排序

		// 10.2.2 折半插入排序（binary insertion sort）
		// 默认：递增排序
		// 最后修改：2019-12-17
		namespace _10_2_2 {
			// 10.2.2.1 排序思路
			// 直接插入排序中将无序区的开头元素R[i]（1 <= i <= n-1）插入到有序区R[0..i-1]是采用的顺序比较法
			// 由于有序区的元素是有序的，可以采用折半查找法在有序区R[0..i-1]中寻找插入位置，再统一移到元素进行插入，这样的插入排序称为折半插入排序或二分插入排序
			// 第 i 趟在R[lowIndex..highIndex]（初始时low = 0，high = i-1）中采用折半查找方法查找插入R[i]的位置为R[high+1]
			// 再将R[high+1..i-1]元素后移一个位置，并插入即置R[high+1] = R[i]
			// 说明：和直接插入排序一样，折半插入排序每趟产生的有序区不一定是全局有序区

			// 引用排序元素类型
			using _10_1::_10_1_5::RecType;

			// 10.2.2.2 排序算法
			void BinInsertSort(RecType R[], int n) {
				int lowIndex, highIndex, midIndex;
				RecType tmp;
				for (int i = 0; i < n; ++i) {
					// 反序时，即不符合要排序的顺序，应对其进行排序
					if (R[i].key < R[i - 1].key) {
						tmp = R[i];    // 将 R[i] 保存到tmp中
						lowIndex = 0;
						highIndex = i - 1;
						// 在 R[low..high] 中找到插入位置，初始时为整个有序区
						while (lowIndex <= highIndex) {
							midIndex = (lowIndex + highIndex) / 2;
							if (tmp.key < R[midIndex].key) {
								highIndex = midIndex - 1;
							} else {
								lowIndex = midIndex + 1;
							}
						}     // 最后 highIndex 所指即第一个小于 R[i]（tmp） 的位置，highIndex + 1 即插入位置
						// 移动元素
						for (int j = i - 1; j > highIndex; --j) {
							R[j + 1] = R[j];
						}
						R[highIndex + 1] = tmp;
					}
				}
			}

			// 10.2.2.3 算法分析
			// 实际上，折半插入排序和直接插入排序相比移动元素的性能没有改善，仅仅减少了关键字的比较次数
			// 就平均性能而言，由于折半查找优于顺序查找，所以折半插入排序也优于直接插入排序
			// 该算法的平均时间复杂度为 O(n^2)，空间复杂度为 O(1)，也是一种稳定的排序方法

		} // END namespace _10_2_2 折半插入排序

		// 10.2.3 希尔排序（shell sort）
		// 默认：递增排序
		// 最后修改：2019-12-17
		namespace _10_2_3 {
			// 10.2.3.1 排序思路
			// 希尔排序也是一种插入排序，实际上是一种分组插入方法
			// 先取一个小于 n 的整数 d1 作为第一个增量，把表的全部元素分成 d1 个组，将所有距离为 d1 的倍数的元素放在同一组，如下：
			// 第1组：	0		d		2d		...		kd		（k = n/d - 1，衡量每组元素的个数）
			// 第2组：	1		1+d		1+2d	...		1+kd
			// 第i组：	i-1		i-1+d	i-1+2d	...		i-1+kd
			// 第d组:	d-1		2d-1	3d-1	...		(k+1)d-1
			// 在各组内进行直接插入排序；然后取第二个增量 d2（<d1），重复上述的分组和排序，直到所取的增量 dt = 1（dt < d(t-1) < ... < d2 < d1）
			// 即所有的元素放在同一组中进行直接插入排序为止，所以希尔排序称为减少增量的排序方法
			// 每一趟希尔排序从元素R[d]（每组的第二个元素）开始起，采用直接插入排序，直到元素 R[n-1] 为止
			// 每个元素的比较和插入都在同组内部进行，对于元素R[i]，同组的前面的元素有 { R[j] | j = i - d >= 0 }
			// 说明：希尔排序每趟并不产生有序区，在最后一趟排序结束前，所有的元素并不一定归位了，但是在希尔排序每趟完成后数据越来越接近有序

			// 引用排序元素类型
			using _10_1::_10_1_5::RecType;

			// 10.2.3.2 排序算法
			// 取 d1 = n/2，d(i+1) = ⌊di/2⌋ 时的希尔排序算法如下
			void ShellSort(RecType R[], int n) {
				int j;    // 用来遍历有序区
				RecType tmp;
				int d = n / 2;    // 增量置初值
				while (d >= 1) {
					// 对所有组采用直接插入排序
					for (int i = d; i < n; ++i) {
						tmp = R[i];
						j = i - d;   // 对相隔 d 个位置一组采用直接插入排序
						while (j >= 0 && tmp.key < R[j].key) {
							R[j + d] = R[j];
							j = j - d;
						}    // 最后 j 指向第一个小于 R[i]（tmp）的元素，j + d 即插入位置
						R[j + d] = tmp;
					}
					d = d / 2;    // 减少增量
				}
			}

			// 10.2.3.3 算法分析
			// 希尔排序算法的时间是一个所取“增量”序列的函数，到目前为止增量的选取无一定论，但无论增量如何取，最后一个增量必须等于 1
			// 希尔算法的时间复杂度难以分析，一般认为其平均时间复杂度为 O(n^1.3)，其速度通常比直接插入排序快
			// 辅助空间复杂度为 O(1)，即希尔排序是一个就地排序，另外希尔排序算法是一种不稳定的排序算法

		} // END namespace _10_2_3 希尔排序

	} // END namespace _10_2 插入排序

	// 10.3 交换排序（swap sort）
	// 默认：递增排序
	// 最后修改：2019-12-17
	namespace _10_3 {
		// 交换排序的基本思想是两两比较待排序元素的关键字，发现这两个元素的次序相反即时进行交换，直到没有反序的元素为止
		// 冒泡排序（bubble sort），快速排序（quick sort）

		// 工具，交换算法
		struct _10_3_Util {
			static void swap(_10_1::_10_1_5::RecType& a, _10_1::_10_1_5::RecType& b) {
				_10_1::_10_1_5::RecType tmp = a;
				a = b;
				b = tmp;
			}
		};

		// 10.3.1 冒泡排序（bubble sort）
		// 默认：递增排序
		// 最后修改：2019-12-17
		namespace _10_3_1 {
			// 10.3.1.1 排序思路
			// 冒泡排序也称为气泡排序，是一种典型的交换排序方法，其基本思想是：
			// 通过无序区中相邻元素关键字间的比较和位置的交换使得关键字较小的元素如气泡一般逐渐往上“漂浮”直到“水面”
			// 整个算法从最下面的元素开始，对每两个相邻的关键字进行比较，且使关键字较小的元素换至关键字较大的元素之上，使得经过一趟冒泡排序后关键字最小的元素到达最上端
			// 接着在剩下的元素中找到关键字次小的元素，并把它换至第二个位置上，以此类推，直到所有的元素都有序为止
			// 说明：冒泡排序每趟产生的有序区一定是全局有序的，也就是说每趟产生的有序区中的所有元素都归位了

			// 引用排序元素类型
			using _10_1::_10_1_5::RecType;

			// 10.3.1.2 排序算法
			void BubbleSort(RecType R[], int n) {
				// 共需要 n - 1 趟冒泡比较
				for (int i = 0; i < n - 1; ++i) {
					// 将 R[i] 元素归位
					for (int j = n - 1; j > i; ++i) {
						// 相邻的两个元素反序时
						if (R[j].key < R[j - 1].key) {
							_10_3_Util::swap(R[j], R[j - 1]);    // 将 R[j] 和 R[j-1] 两个元素交换
						}
					}
				}
			}

			// 在有些情况下，在第 i（i < n-1）趟时已经排好序了，但仍会执行后面的几趟比较
			// 实际上，一旦算法中的某一趟比较时不出现任何元素交换，说明已经排序好了，就可以结束算法，为此改进的冒牌排序如下
			void BubbleSort_Refine(RecType R[], int n) {
				bool exchanged = false;
				for (int i = 0; i < n - 1; ++i) {
					exchanged = false;
					for (int j = n - 1; j > i; --j) {
						if (R[j].key < R[j - 1].key) {
							_10_3_Util::swap(R[j], R[j - 1]);
							exchanged = true;
						}
					}
					if (!exchanged) {
						return;
					}
				}
			}

			// 10.3.1.3 算法分析
			// 当初始数据不同时，冒牌排序所耗费的时间有很大的差异
			// 最好的情况是表初态为正序，此时算法的最好时间复杂度为 O(n)；最坏的情况是表初态为反序，此时算法的最坏时间复杂度为 O(n^2)
			// 算法的平均时间复杂度为 O(n^2)，也就是说算法的平均时间复杂度接近最坏情况
			// 虽然冒泡排序不一定要进行 n-1 趟，但由于它的元素移动次数较多，一般平均时间性能要比直接插入排序差
			// 算法中使用的辅助变量与问题规模 n 无关，故算法辅助空间复杂度为 O(1)，也就是说它是一个就地排序算法
			// 另外在算法运行中，保持元素的相对顺序不变，故该算法是一种稳定的排序方法 

		} // END namespace _10_3_1 冒泡排序

		// 10.3.2 快速排序（quick sort）
		// 默认：递增排序
		// 最后修改：2019-12-17
		namespace _10_3_2 {
			// 10.3.2.1 排序思路
			// 快速排序是由冒泡排序改进而得的，它的基本思想是在待排序的 n 个元素中任取一个元素（通常取第一个元素）作为基准元素，把该元素放入适当的位置后
			// 数据序列被划分为两部分，所有关键字比该元素关键字小的元素放置在前一部分，所有比它大的元素放置在后一部分，并把该元素放在这两部分的中间（称为该元素归位）
			// 这个过程称为一趟快速排序，即一趟划分，之后对产生的两个部分分别重复上述过程，直至每部分内只有一个元素或空为止
			// 简而言之，每趟使表的第一个元素放入适当位置，将表一分为二，对子表按递归方式继续这种划分，直到划分的子表的长度为1或0

			/* 一趟快速排序的划分过程 partition(R,leftIndex,rightIndex) 是采用从两头向中间扫描的办法，同时交换与基准元素逆序的元素，具体方法是：
			设两个指示器 i 和 j，它们的初始值分别指向无序区中的第一个元素和最后一个元素，假设无序区中的元素为 R[leftIndex, leftIndex+1, ..., rightIndex]，
			则 i 的初始值为 leftIndex，j 的初始值为 rightIndex，首先将 R[leftIndex] 移置变量 tmp 中作为基准
			令 j 自位置 right 起向前扫描直至 R[j].key < tmp.key 时将 R[j] 移至位置 i，然后让 i 向后扫描直至 R[i].key > tmp.key 时将 R[i] 移至位置 j
			依次重复直到 i == j，此时所有 R[left, left+1, ..., i-1] 的关键字都小于 tmp.key，而所有 R[i+1, i+2, ..., right] 的关键字都大于 tmp.key
			此时再将 tmp 中的元素移至位置 i，它将无序区中的元素分割成 R[left..i-1] 和 R[i+1..right]，以便分别进行排序
			说明：快速排序每趟仅将一个元素归位
			显然，快速排序是一个递归过程，其递归模型如下：f(R,leftIndex,rightIndex) ≡
			不做任何事情    // 当 R[leftIndex..rightIndex]中没有元素或只有一个元素时
			i = partition(R,left,right);    // 其他情况
			f(R,left,i-1);
			f(R,i+1,right);
			*/

			// 引用排序元素类型
			using _10_1::_10_1_5::RecType;

			// 10.3.2.2 排序算法

			// 基础算法，请勿显式调用
			struct _10_3_2_Base {
				// 一趟划分
				static int partition(RecType R[], int leftIndex, int rightIndex) {
					int i = leftIndex, j = rightIndex;
					RecType tmp = R[i];    // 以 R[i] 为基准
					// 从两端交替向中间扫描，直到 i == j 为止
					while (i < j) {
						while (i < j && R[j].key >= tmp.key) --j;    // 从右向左扫描，找第一个小于 tmp.key 的 R[j]
						R[i] = R[j];    // 找到这样的 R[j]，将其放入到 R[i] 中
						while (i < j && R[i].key <= tmp.key) ++i;    // 从左向右扫描，找第一个大于 tmp.key 的 R[i]
						R[j] = R[i];    // 找到这样的 R[i]，将其放入到 R[j] 中
					}
					R[i] = tmp;    // 将基准元素放入到适当的位置
					return i;
				}
			};

			// 快速排序
			void QuickSort(RecType R[], int leftIndex, int rightIndex) {
				// 区间内至少存在两个元素的情况
				if (leftIndex < rightIndex) {
					int i = _10_3_2_Base::partition(R, leftIndex, rightIndex);    // 划分
					QuickSort(R, leftIndex, i - 1);    // 对左区间递归排序
					QuickSort(R, i + 1, rightIndex);    // 对右区间递归排序
				}
			}

			// 实际上，在快速排序中可以以任意一个元素为基准（更好的选择方法时从数序中随机选择一个元素作为基准）
			// 以下算法以当前区间的中间位置的元素为基准，同样可以达到快速排序的目的
			void QuickSort_2(RecType R[], int leftIndex, int rightIndex) {
				if (leftIndex < rightIndex) {
					int pivot = (leftIndex + rightIndex) / 2;    // 用区间中间元素作为基准
					if (pivot != leftIndex) {
						// 若基准不是区间的第一个元素，则将之与第一个元素互换，照顾到 partition() 内部是将区间的第一个元素作为基准的
						_10_3_Util::swap(R[pivot], R[leftIndex]);
					}
					int i = _10_3_2_Base::partition(R, leftIndex, rightIndex);    // 划分
					QuickSort_2(R, leftIndex, i - 1);
					QuickSort_2(R, i + 1, rightIndex);
				}
			}

			// 快速排序，非递归实现
			void QuickSort_NoRecursion(RecType R[], int firstIndex, int lastIndex) {
				struct Pair {
					int beginIndex;
					int endIndex;
					void set(int a, int b) { beginIndex = a; endIndex = b; }
					void get(int& a, int& b) { a = beginIndex; b = endIndex; }
				};
				Pair* st = new Pair[lastIndex - firstIndex + 1];
				int top = -1;    // 栈，用来存储每次递归调用时的无序区间的 左索引 和 右索引
				int leftIndex = firstIndex, rightIndex = lastIndex;    // 每次递归调用时的无序区的范围
				int i, j;    // 用于划分的指示器
				RecType tmp;    // 基准元素
				st[++top].set(leftIndex, rightIndex);    // 初次调用现场入栈
				// 栈不为空循环
				while (top >= 0) {
					st[top--].get(leftIndex, rightIndex);
					if (leftIndex >= rightIndex) continue;
					i = leftIndex; j = rightIndex;
					tmp = R[i];    // 选取该区间的第一个元素作为基准元素
					while (i < j) {
						while (i < j && R[j].key >= tmp.key) --j;
						R[i] = R[j];
						while (i < j && R[i].key <= tmp.key) ++i;
						R[j] = R[i];
					}
					R[i] = tmp;    // 将基准元素放入到适当位置
					// 将递归调用的 左区 和 右区 的状态现场依次进栈
					st[++top].set(i + 1, rightIndex);
					st[++top].set(leftIndex, i - 1);
				}
			}

			// 10.3.2.3 算法分析
			// 最好的情况是每一次划分都将 n 个元素划分为两个长度差不多的子区间，这样递归树的高度为 O(log2(n))，而每一层划分的时间为 O(n)
			// 所以此时算法的时间复杂度为 O(n*log2(n))，空间复杂度为 O(n)
			// 最坏的情况是每次划分选取的基准都是当前无序区中关键字最小（或最大）的元素，划分的结果是基准左边的子区间为空（或右边的子区间为空）
			// 而划分所得的另一个非空的子区间中的元素的数目仅比划分前的无序区中的元素个数减少一个
			// 这样的递归树的高度为 n，需要做 n-1 次划分，此时算法的时间复杂度为 O(n^2)，空间复杂度为 O(n)
			// 在平均的情况下，平均时间复杂度为 O(n*log2(n))，也就是说，算法的平均时间复杂度接近最好情况，平均空间复杂度为 O(log2(n))
			// 另外，快速排序算法是一种不稳定的排序方法

		} // END namespace _10_3_2 快速排序

	} // END namespace _10_3 交换排序

	// 10.4 选择排序（selection sort）
	// 默认：递增排序
	// 最后修改：2019-12-17
	namespace _10_4 {
		// 选择排序的基本思想是每一趟从待排序的元素中选出关键字最小的元素，顺序放在已排好序的子表最后，直到全部元素排序完毕
		// 由于选择排序方法每一趟总是从无序区中选出全局最小（或最大）的关键字，所以适合于从大量的元素中选择一部分排序元素
		// 简单选择排序（simple selection sort，又称直接选择排序）、堆排序（heap sort）

		// 10.4.1 简单选择排序（simple selection sort)
		// 默认：递增排序
		// 最后修改：2019-12-17
		namespace _10_4_1 {
			// 10.4.1.1 排序思路
			// 简单选择排序的基本思想是第 i 趟排序开始时，当前有序区和无序区分别为 R[0..i-1] 和 R[i..n-1]（0 <= i < n-1）
			// 该趟排序是从当前无序区中选出关键字最小的元素 R[k]，将其与无序区中的第一个元素交换，使 R[0..i] 和 R[i+1..n-1] 分别变为新的有序区和无序区
			// 因为每趟排序均使有序区中增加了一个元素，且有序区中的元素的关键字都不大于无序区中元素的关键字，即第 i 趟排序之后，R[0..i] 的关键字均小于等于 R[i+1..n-1] 的关键字
			// 所以进行 n-1 趟排序之后 R[0..n-2] 的所有关键字均小于等于 R[n-1].key，也就是说，经过 n-1 趟排序后整个表递增有序
			// 说明：简单选择排序每趟产生的有序区一定是全局有序区，也就是说，每趟产生的有序区中所有元素都归位了

			// 引用排序元素类型
			using dst::_10_1::_10_1_5::RecType;

			// 10.4.1.2 排序算法
			void SelectSort(RecType R[], int n) {
				int k;    // 某次排序中最小元素的位置
				// n - 1 趟排序
				for (int i = 0; i < n - 1; ++i) {
					k = i;
					for (int j = i + 1; j < n; ++j) {
						if (R[j].key < R[k].key) {
							k = j;    // 在当前的无序区中选择关键字最小的元素的位置
						}
					}
					if (k != i) {
						_10_3::_10_3_Util::swap(R[i], R[k]);
					}
				}
			}

			// 10.4.1.3 算法分析
			// 无论初始数据序列的状态如何，在第 i 趟排序中选出最小关键字的元素，所需要的关键字比较相同，因此总的平均时间复杂度为 O(n^2)
			// 辅助变量与问题规模 n 无关，故辅助空间复杂度为 O(1)，也就是说该算法是一个就地排序
			// 另外，简单选择排序算法是一个不稳定的排序算法

		} // END namespace _10_4_1 简单选择排序

		// 10.4.2 堆排序（heap sort）
		// 默认：递增排序
		// 最后修改:2019-11-22
		namespace _10_4_2 {
			// 10.4.2.1 排序思路
			// 堆排序是一种树形选择排序法，它的特点是将 R[0...n-1] 看成是一棵完全二叉树的顺序存储结构（ i 为逻辑编号 1...n ）
			// 利用完全二叉树中的双亲结点和孩子结点之间的位置关系（ i 的左右孩子分别为 2i，2i+1）在无序区中选择关键字最大（或最小）的元素
			// 当 R[0...n-1] 中的 n 个关键字序列 k0, k1, ..., kn 满足如下性质（堆性质）时，称为堆
			// (1)、ki <= k(2i) 且 ki <= k(2i+1)（小根堆） 或 (2)、ki >= k(2i) 且 ki >= k(2i+1)（大根堆）
			// 堆排序的排序过程与简单的选择排序类似，只是挑选最大或最小元素时采用的方法不同，这里采用大根堆，每次挑选最大元素归位

			// 引用排序元素类型
			using dst::_10_1::_10_1_5::RecType;

			// 10.4.2.2 排序算法

			// 基础算法，请勿显式调用
			struct _10_4_2_Base {
				/* 挑选最大元素是采用筛选方法实现的，思想为：大者上浮，小者被筛下去；其过程如下：（ i 为逻辑编号）
				假设正在处理的元素 R[i] 为某棵子二叉树的根结点，它的左右子树已经是大根堆，将其两个孩子的关键字的最大者与根的关键字比较
				若根的关键字 R[i].key 较小，将其与最大孩子（MAX { R[2i], R[2i+1]）进行交换（即筛下去）
				交换有可能破坏下一级的堆，故继续采用上述方法构造修复刚刚交换孩子（下一级）的堆，直到这颗完全二叉树变成一个大根堆为止
				假设对 R[lowIndex...highIndex] 进行筛选，必须满足：以 lowIndex 为根结点的左右子树均为大根堆
				注意物理编号（0...n-1），根结点为 index，左右孩子节点为 2 * index + 1 和 2 * index + 2
				*/
				static void sift(RecType R[], int lowIndex, int highIndex) {
					int i = lowIndex, j = 2 * i + 1;    // R[j] 是 R[i] 的左孩子
					RecType tmp = R[i];
					while (j <= highIndex) {
						// 若右孩子关键字较大，把 j 指向右孩子
						if (j < highIndex && R[j].key < R[j + 1].key) {
							++j;
						}
						// 此处 j 指向最大孩子，若根结点小于最大孩子，交换之，并修复下一级的堆
						if (tmp.key < R[j].key) {
							R[i] = R[j];    // 将 最大孩子R[j] 调整到当前处理的 双亲结点R[i] 的位置上
							i = j;    // 修改 i 和 j 的值，指向下一级，以便继续向下筛选
							j = 2 * i + 1;
						} else {
							break;    // 若根结点大于等于最大孩子，筛选结束
						}
					}
					R[i] = tmp;    // 被筛的结点放到适合的最终位置上
				}
			};

			/* 堆排序（递增排序）
			构建初始堆 R[0...n-1] 的过程是：对于一颗完全二叉树，从物理编号 i = ⌊n/2⌋-1 ~ 0，即最后一个分支结点开始，利用上述筛法建堆
			在初始堆 R[0...n-1] 构造完成后，根结点 R[0] 一定是最大关键字结点，将其放到序列最后，即 堆中的根 R[0] 与最后一个叶子结点 R[n-1] 交换
			最大元素归位，整个待排序元素个数减少一个，且由于根结的改变，这 n-1 个结点 R[0...n-2] 不一定为堆，但 R[0] 的左右子树均为堆，
			故再调用一次筛法 sift 将这 n-1 个结点 R[0...n-2] 调整成堆，其根结点 R[0] 为次大元素，将之放到序列的倒数第二个位置，即与堆中最后一个叶子结点交换
			如此重复，直到完全二叉树中只剩下一个根为止
			*/
			void HeapSort(RecType R[], int n) {
				// 循环建立初始堆，调用 sift 算法 ⌊n/2⌋ 次
				for (int i = n / 2 - 1; i >= 0; _10_4_2_Base::sift(R, i--, n - 1));
				// 进行 n-1 趟完成堆排序，每一趟堆中元素个数减1
				for (int i = n - 1; i > 0; --i) {
					// 将最后一个元素与根 R[0] 交换
					_10_3::_10_3_Util::swap(R[0], R[i]);
					_10_4_2_Base::sift(R, 0, i - 1);    // 对 R[0...n-2] 进行筛选，得到 i-1 个结点的堆
				}
			}

			// 10.4.2.3 算法分析
			// 堆排序的时间主要由建立初始堆和反复重建堆这两部分的时间构成，它们均是通过调用 sift() 实现的
			// 对于高度为 k 的完全二叉树/子树，调用 sift() 时，其中 while 循环最多执行 k-1 次，最多进行 2(k-1) 次比较，最多进行 k+1 次移动，因此主要以关键字比较来分析时间性能
			// 堆排序的最坏时间复杂度为 O(n*log2(n))，平均时间复杂度分析较难，但实验研究表明，它接近最坏性能
			// 实际上，堆排序和简单选择排序算法一样，其时间性能与初始序列顺序无关，也就是说，堆排序的算法最好、最坏和平均时间复杂度都是 O(n*log2(n))
			// 由于建初始堆所需的比较次数较多，所以堆排序不适合元素较少的排序表
			// 辅助空间复杂度为 O(1)，堆排序算法是一种不稳定的排序算法

		} // END namespace _10_4_2 堆排序

	} // END namespace _10_4 选择排序

	// 10.5 归并排序（merge sort）
	// 默认：递增排序
	// 最后修改：2019-12-18
	namespace _10_5 {
		// 10.5.1 排序思路
		// 归并排序是多次将两个或两个以上的有序表合并成一个新的有序表，最简单的归并是直接将两个有序的子表合并成一个有序的表，即二路归并
		// 二路归并排序（2-way merge sort）的基本思想是将 R[0..n-1]看成是 n 个长度为 1 的有序序列，然后进行两两归并，得到 ⌈n/2⌉ 个长度为 2（最后一个可能小于2）的有序序列
		// 再进行两两归并，得到 ⌈n/4⌉ 个长度为 4（最后一个有序序列长度可能小于4）的有序序列，...，直到得到一个长度为 n 的有序序列
		// 说明：归并排序每趟产生的有序区只是局部有序的，也就是说再最后一趟排序结束前所有的元素并不一定归位了

		// 引用排序元素类型
		using dst::_10_1::_10_1_5::RecType;

		// 10.5.2 排序算法

		// 基础算法，请勿显式调用
		struct _10_5_Base {
			/* 将两个有序表直接归并为一个有序表的算法 Merge()
			设两个有序表放在同一数组中相邻的位置上，即 R[beginIndex..endIndexOne]（第一段）和 R[endIndexOne+1..endIndexTwo]（第二段）
			先将它们合并到一个局部的暂存数组 Rtmp 中，待合并完成后再将其复制到 R 中
			每次从两个段中取出一个元素进行关键字比较，将较小者放入 Rtmp 中，较大者留作下次比较，最后将各段中余下的部分直接复制到 Rtmp 中，最后将 Rtmp 复制给 R
			*/
			static void Merge(RecType R[], int beginIndex, int endIndexOne, int endIndexTwo) {
				//if (beginIndex > endIndexOne || endIndexOne > endIndexTwo) return;
				int i = beginIndex, j = endIndexOne + 1, k = 0;    // i，j，k 分别扫描 第一段，第二段，Rtmp
				RecType* Rtmp = (RecType*)malloc((endIndexTwo - beginIndex + 1) * sizeof(RecType));    // 动态分配空间
				while (i <= endIndexOne && j <= endIndexTwo) {
					if (R[i].key <= R[j].key) {
						Rtmp[k++] = R[i++];    // 将第一段放入 Rtmp
					} else {
						Rtmp[k++] = R[j++];    // 第二代放入 Rtmp
					}
				}
				// 将剩下的元素放入 Rtmp
				while (i <= endIndexOne) Rtmp[k++] = R[i++];
				while (j <= endIndexTwo) Rtmp[k++] = R[j++];
				// 将合并好的有序序列复制给 R
				for (int m = beginIndex, n = 0; m <= endIndexTwo; R[m++] = Rtmp[n++]);
				free(Rtmp);
			}

			/* Merge() 实现了一次归并，其中使用的辅助空间正好是要归并的元素的个数，接下来利用 Merge() 解决一趟归并问题
			在某趟归并中，设各子表的长度为 length（最后一个子表的长度可能小于length），则归并前 R[0..n-1] 中共有 ⌈n/length⌉ 各子表：
			R[0..length-1]，R[length..2*length-1]，...，R[length*⌊n/length⌋..n-1]
			在调用 Merge() 将相邻的一对子表进行归并时，必须对表的个数可能是奇数以及最后一个子表的长度小于 length 这两种特殊的情况进行特殊处理：
			若子表的个数为奇数，则最后一个子表无须和其他子表归并（即本趟为空）；若子表的个数为偶数，则要注意最后一对子表中最后一个子表区间的上界是 n-1
			对整个排序序列进行一趟归并
			*/
			static void MergePass(RecType R[], int length, int n) {
				int i;
				// 归并长度为 length 的两个相邻子表，若最后剩下的长度小于 2 * length，则不处理
				for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length) {
					Merge(R, i, i + length - 1, i + 2 * length - 1);
				}
				// 在此处理剩下的表（长度小于2*length），若 i+length-1 > n-1 即剩下的表不足length长，即表的个数为奇数，不处理；否则处理最后两个表，注意最后一个表的末尾为 n-1
				if (i + length - 1 < n - 1) {
					Merge(R, i, i + length - 1, n - 1);
				}
			}

			// 上述二路归并排序实际上采用的是自底向上的过程，也可以采用自顶向下的递归过程，其算法如下：
			// 对 R[lowIndex..highIndex] 进行二路归并
			static void MergeSortRecursionHepler(RecType R[], int lowIndex, int highIndex) {
				if (lowIndex < highIndex) {
					int mid = (lowIndex + highIndex) / 2;
					MergeSortRecursionHepler(R, lowIndex, mid);
					MergeSortRecursionHepler(R, mid + 1, highIndex);
					Merge(R, lowIndex, mid, highIndex);
				}
			}
		};

		// 在进行二路归并时，第1趟归并排序对应length=1，第2趟对应length=2，第3趟对应length=4，...，每一次length翻一倍，但总小于n，所以总趟数为 ⌈log2(n)⌉
		void MergeSort(RecType R[], int n) {
			for (int length = 1; length < n; length = 2 * length) {
				_10_5_Base::MergePass(R, length, n);    // 进行 ⌈log2(n)⌉ 趟归并
			}
		}

		// 自顶向下的递归的二路归并排序
		void MergeSort_Recursion(RecType R[], int n) {
			_10_5_Base::MergeSortRecursionHepler(R, 0, n - 1);
		}

		// 10.5.3 算法分析
		// 对于长度为 n 的排序表，二路归并需要进行 ⌈log2(n)⌉ 趟，每趟归并的时间为 O(n)，故其最好、最坏和平均时间复杂度都为 O(n*log2(n))
		// 每次二路归并都需要使用一个辅助数组来暂存两个有序子表归并的结果，而每次归并后都会释放其空间，但最后一趟需要所有的元素参与归并，故辅助空间复杂度为 O(n)
		// 另外，在一次二路归并中，元素的相对次序不会发生改变，该算法是一种稳定的排序算法
		// 归并排序可以是多路的，如三路归并排序等，归并的趟数为 log3(n)，一趟的时间为 O(n)，时间复杂度为 n*log3(n) = n*log2(n)/log2(3) 仍为 O(n*log2(n))
		// 不过三路归并排序算法的实现远比二路归并排序算法复杂

	} // END namespace _10_5 归并排序

	// 10.6 基数排序（radix sort）
	// 默认：递增排序
	// 最后修改：2019-12-18
	namespace _10_6 {
		// 10.6.1 排序思路
		// 基数排序（radix sort）是通过“分配”和“收集”过程来实现排序，不需要进行关键字间的比较，是一种借助于多关键字排序的思想对单关键字排序的方法
		// 一般情况下，元素 R[i] 的关键字 R[i].key 由 d（digit） 位数字（或字符）组成，即 k:d-1,d-2,...1,0，每一个数字表示关键字的一位，其中 d-1 位最高位，0 位最低位
		// 每一位的值都在 0 <= ki < r 范围内，其中 r 为基数（radix），例如对于二进制 r 为 2，对于十进制 r 为 10 等
		// 基数排序有两种，即最低为优先（least significant digit first，LSD）和最高位优先（most significant digit first，MSD），其原理是相同的，这里主要讨论前者
		// 最低为优先的过程是先按最低位的值对元素进行排序，在此基础上再次按次低位进行排序，以此类推
		// 由低位到高位，每趟都是根据关键字的一位并在前一趟的基础上对所有的元素进行排序，直至最高位，则完成了基数排序的整个过程
		// 对一个数据序列采用LSD还是MSD需要由数据序列的特点确定，一般越重要的位越放在后面排序
		// 以 r（radix）为基数的最低位优先排序的过程是：假设线性表由元素序列 a0, a1, a2, ..., a(n-1) 构成，每个元素 aj 的关键字为 d 的元组 kj:d-1,d-2,...1,0
		// 其中 0 <= kj(i) <= r-1（0 <= j < n，0 <= i <= d-1），在排序过程中使用 r（基数radix）个队列 Q0, Q1, Q2, ..., Q(r-1)，排序过程如下：
		// 对所有位数由低到高 i = 0,1, ..., d-1 依次做一次“分配”和“收集”（即一次稳定排序的过程）
		// 分配：开始时，把 Q0,Q1,...,Q(r-1) 各个队列置成空队列，然后依次考查线性表中每一个元素 aj (j = 0,1,...,n-1)，根据元素 aj 的关键字 aj.ki（设为k），把元素插入到 Qk 中
		// 收集：将 Q0,Q1,...Q(r-1) 各个队列中的元素依次首尾相接，得到新的元素序列，从而组成新的线性表
		// 在 d 趟执行之后数据序列就有序了
		// 说明：基数排序每趟并不产生有序区，与就是说在最后一趟排序结束前所有元素并不一定归位了

		// 10.6.2 排序算法

		// 基础算法和结构，请勿显式调用
		struct _10_6_Base {
			// 在基数排序中每个元素多次进出队列，如果采用顺序表存储，需要有大量元素的移动，而采用链式即构存储时，只需修改相关指针域
			// 假设待排序的数据序列存放在以 p 为首结点的指针的单链表中，其中结点类型 NodeType 的声明如下：
			static const int MAXDigit = 10;    // 最大关键字位数，此处为一个 int（ 2^32 - 1 = 4.5E+9 ）
			typedef struct node {
				char digit[MAXDigit + 1];    // 关键字位数，地位到高位（适配时逆序该数组可在LSD和MSD中间转换）
				struct node* next;    // 指向下一个结点
			} NodeType;    // 基数排序数据的结点类型
			static const int MAXRadix = 16;    // 最大支持16进制
			// 其中，digit 域存放关键字，它是一个字符数组，data[0..MAXDigit-1] 依次存放关键字的低位到高位的各数字字符，关键字的实际位数由参数 d 指定

			// 以下基数排序算法 RadixSort(p,r,d) 实现LSD方法（此处根据教程录入，实际可更改），其中参数 p 为存储的待排序序列的单链表的指针，r 为基数，d 为关键字位数
			static void RadixSort_base(NodeType*& p, int radix, int digit) {
				NodeType *head[MAXRadix], *tail[MAXRadix];    // 定义各链队的首尾指针（ head[i] 和 tail[i] 为同一个链队 ），链队的个数为基数的大小，即 0,1,...,r-1
				NodeType* t = NULL;    // t 用来指向 p 的尾结点
				int k;    // 用来指示该元素属于哪个链队
				// 用 d 从低位到高位扫描
				for (int d = 0; d < digit; ++d) {
					for (int i = 0; i < radix; ++i) {
						head[i] = tail[i] = NULL;    // 每次扫描某一位时，先将链队置为 NULL 的状态
					}
					// 分配：遍历原链表 p
					while (p != NULL) {
						k = p->digit[d] - '0';    // 将字符转换成数字，k 即该元素 p 的关键字上的第 d 位，将该元素放入 Qk 中
						if (head[k] == NULL) {
							head[k] = p; tail[k] = p;    // Qk 为空时
						} else {
							tail[k]->next = p; tail[k] = p;    // Qk 不为空时
						}
						p = p->next;    // 依次遍历原链表中的元素
					}
					p = NULL;
					// 收集：遍历所有链队，重新用 p 收集所有结点
					for (int i = 0; i < radix; ++i) {
						// 若该队列非空，即放入了元素，将其连接到 p 上
						if (head[i] != NULL) {
							if (p == NULL) {
								p = head[i]; t = tail[i];    // p 为空，即还没连上过链队
							} else {
								t->next = head[i]; t = tail[i];    // p 不为空，t 指向该链队开头，更新 t
							}
						}
					}
					t->next = NULL;    // 置 p 的最后一个结点的下一个结点为 NULL
				}
			}

			static void numToSequence(int num, char sequence[]) {
				for (int i = 0; i < MAXDigit; ++i) {
					sequence[i] = (num % 10) + '0';    // 10 进制，高位用 0 补齐
					num = num / 10;
				}
				sequence[MAXDigit] = '\0';
			}

			static int sequenceToNum(char sequence[]) {
				int /*length = 0, */num = 0;
				int i;
				//while (*sequence++ != '\0') ++length;
				for (i = MAXDigit - 1; i >= 0; --i) {
					if (sequence[i] != '0') break;    // 因为sequence中的字符是从低位到高位，且高位用 0 补齐，故从右向左找到第一个非零字符，即原数字的最高位
				}
				while (i >= 0) {
					num = num * 10 + sequence[i--] - '0';
				}
				return num;
			}

		};

		// 引用排序元素类型
		using dst::_10_1::_10_1_5::RecType;

		// 基数排序，适配算法
		void RadixSort(RecType R[], int n) {
			if (n <= 0) return;
			_10_6_Base::NodeType* p = (_10_6_Base::NodeType*)malloc(sizeof(_10_6_Base::NodeType));    // 头结点
			_10_6_Base::numToSequence(R[0].key, p->digit);
			_10_6_Base::NodeType *r = p, *s;    // r 为尾指针
			for (int i = 1; i < n; ++i) {
				s = (_10_6_Base::NodeType*)malloc(sizeof(_10_6_Base::NodeType));    // 采用尾插法从数据序列生成链表
				_10_6_Base::numToSequence(R[i].key, s->digit);
				r->next = s; r = s;
			}
			r->next = NULL;
			_10_6_Base::RadixSort_base(p, 10, _10_6_Base::MAXDigit);    // 排序
			for (int i = 0; i < n && p != NULL; ++i) {
				R[i].key = _10_6_Base::sequenceToNum(p->digit);    // 从单链表中取出数据
				s = p;
				p = p->next;
				free(s);
			}
		}

		// 10.6.3 算法分析
		// 在基数排序的过程中共进行了 digit 趟的分配和收集，每一趟中分配过程需要扫描所有结点，而收集过程时按队列进行的，所以一趟的执行时间为 O(n+radix)
		// 因此基数排序的时间复杂度为 O(digit*(n+radix))，其中 digit 和 radix 为常量时，时间复杂度为 O(n)
		// 在基数排序中需要辅助空间为 radix（创建radix个队列），辅助空间复杂度为 O(radix)
		// 另外，元素的相对位置不会发生改变，该算法是一种稳定的排序方法

	} // END namespace _10_6 基数排序

	// 10.7 各种内排序方法的比较和选择
	// 最后修改：2019-12-18
	namespace _10_7 {
		// 通常按平均时间将排序方法分为下面3种：
		// (1)、平方阶排序：O(n^2)，一般称为简单排序方法，例如直接插入排序、简单选择排序和冒泡排序
		// (2)、线性对数阶排序：O(n*log2(n))，如快速排序、堆排序和归并排序
		// (3)、线性阶排序：O(n)，如基数排序（假定数据的位数digit和进制radix为常量时）

		/* 表 10.1 各种排序方法的性能
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		排序方法     │  时间复杂度平均情况  │    最坏情况    │    最好情况    │  空间复杂度  │  稳定性  │  复杂性
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		直接插入排序 │  O(n^2)             │  O(n^2)        │  O(n)          │  O(1)       │  稳定    │  简单
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		折半插入排序 │  O(n^2)             │  O(n^2)        │  O(n)          │  O(1)       │  稳定    │  简单
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		希尔排序     │  O(n^1.3)           │                │                │  O(1)       │  不稳定  │  较复杂
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		冒泡排序     │  O(n^2)             │  O(n^2)        │  O(n)          │  O(1)       │  稳定    │  简单
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		快速排序     │  O(n*log2(n))       │  O(n^2)        │  O(n*log2(n)   │  O(log2(n)) │  不稳定  │  较复杂
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		简单选择排序 │  O(n^2)             │  O(n^2)        │  O(n^2)        │  O(1)       │  不稳定  │  简单
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		堆排序       │  O(n*log2(n))       │  O(n*log2(n))  │  O(n*log2(n))  │  O(1)       │  不稳定  │  较复杂
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		二路归并排序 │  O(n*log2(n))       │  O(n*log2(n))  │  O(n*log2(n))  │  O(n)       │  稳定    │  较复杂
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		基数排序     │  O(d(n+r))          │  O(d(n+r))     │  O(d(n+r))     │  O(r)       │  稳定    │  较复杂
		───────────────────────────────────────────────────────────────────────────────────────────────────────
		*/

		// 正是因为不同的排序方法适应不同的应用环境和要求，所以选择适当的排序方法应该综合考虑下列因素：
		// (1)、待排序的元素数目 n（问题规模）
		// (2)、元素的大小（每个元素的规模)
		// (3)、关键字的结构及其初始状态
		// (4)、对稳定性的要求
		// (5)、语言工具的条件
		// (6)、数据的存储结构
		// (7)、时间和空间复杂度

		/* 没有哪一种排序方法时绝对好的，每一种排序方法都有其优点，适合于不同的环境，因此在实际应用中应根据具体情况做选择
		首先考虑排序对稳定性的要求，若要求稳定，则只能在稳定方法中选取，否则可以在所有方法中选取；
		其次要考虑待排序元素个数n的大小，若n较大，则可在改进方法中选取，否则在简单方法中选取；然后再考虑其他因素
		下面给出综合考虑了以上几个方面所得出的大致结论：
		(1)、若 n 较小（如n≤50)，可采用直接插入或简单选择排序。一般地，这两种排序方法中，直接插入排序较好，但简单选择排序移动的元素数少于直接插入排序
		(2)、若文件初始状态基本有序（指正序），则选用直接插入或冒泡排序为宜
		(3)、若n较大，应采用时间复杂度为 O(n*log2n) 的排序方法，例如快速排序、堆排序或二路归并排序
			 快速排序是目前基于比较的内排序中被认为是较好的方法，当待排序的关键字是随机分布时，快速排序的平均时间最少
			 但堆排序所需的辅助空间少于快速排序，并且不会出现快速排序可能出现的最坏情况
			 这两种排序都是不稳定的，若要求排序稳定，则可选用二路归并排序
		(4)、若需要将两个有序表合并成一个新的有序表，最好用二路归并排序方法
		(5)、基数排序可能在O(n)时间内完成对n个元素的排序
			 但遗憾的是，基数排序只适用于像字符串和整数这类有明显结构特征的关键字，而当关键字的取值范围属于某个无穷集合（例如实数型关键字）时无法使用基数排序
			 这时只有借助于“比较”的方法来排序，由此可知，若n很大，元素的关键字位数较少且可以分解时采用基数排序较好
		*/

	} // END namespace _10_7 各种内排序方法的比较和选择

} // END namespace dst 数据结构教程

#endif // !DST_10_INTERNAL_SORT_H