// Author：Akame Qixisi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

#ifndef DST_4_STRING_H
#define DST_4_STRING_H

// 第四章：串

// 数据结构教程（第5版） 清华大学出版社
// Data Structure Tutorial
namespace dst {
	// 4.1 串（sting）的基本概念
	// 最后修改：2019-9-24
	namespace _4_1 {
		// 串的抽象数据类型描述如下
		/*
		ADT String {
			数据对象:
				D = { ai | 1 <= i <= n, n >= 0, ai 为 char 类型 }
			数据关系:
				R = { <ai,a(i+1)> | ai、a(i+1) ∈ D, i = 1,...,n - 1 }
			基本运算:
				// 除引用外，参数串均未变化，即不破坏参数串
				StrAssign(&s, cstr)
				DestroyStr(&s)
				StrCopy(&s,t)
				StrEqual(s,t)
				StrLength(s)
				Concat(s,t)
				SubStr(s,i,len)
				InsStr(s1,i,s2)
				DelStr(s,i,len)
				RepStr(s,i,len,t)
				DispStr(s)
		}
		*/
	} // END namespace _4_1 串的基本概念

	// 4.2 串的存储结构
	// 顺序串（sequential string）和 链串（linked string）
	// 元素类型：char
	// 最后修改：2019-9-24
	namespace _4_2 {
		// 4.2.1 串的顺序存储结构————顺序串
		// 顺序串（sequential string）
		// 最后修改：2019-9-24
		namespace _4_2_1 {
			// 串的最大长度
			const int MaxSize = 50;

			// 顺序串类型
			typedef struct {
				char data[MaxSize];    // 数据数组
				int length;    // 长度信息
			} SqString;

			// 生成串 StrAssign(&s,cstr)
			// 将一个C/C++字符串常量cstr（以'\0'字符标识结尾）赋给顺序串s
			// 参数s为引用
			void StrAssign(SqString& s, char cstr[]) {
				int i = 0;
				for (i = 0; cstr[i] != '\0'; ++i) {
					s.data[i] = cstr[i];
				}
				s.length = i;    // 设置串s的长度
			}

			// 销毁串 DestroyStr(&s)
			void DestroyStr(SqString& s) {}

			// 复制 StrCopy(&s,t)
			void StrCopy(SqString& s, SqString t) {
				for (int i = 0; i < t.length; ++i) {
					s.data[i] = t.data[i];
				}
				s.length = t.length;
			}

			// 判断是否相等 StrEqual(s,t)
			bool StrEqual(SqString s, SqString t) {
				if (s.length != t.length) {
					return false;    // 长度不相等直接返回false
				}
				for (int i = 0; i < s.length; ++i) {
					if (s.data[i] != t.data[i]) {
						return false;    // 有一个不相等时就返回false
					}
				}
				return true;    // 长度相等，且对应字符都相等，返回true
			}

			// 求串长 StrLength(s)
			int StrLength(SqString s) {
				return s.length;
			}

			// 连接 Concat(s,t)
			// 返回由两个串s和t连接在一起形成的结果串，不破环原串
			// 没有检查两个串的长度超出最大长度的情况
			SqString ConCat(SqString s, SqString t) {
				SqString str;
				str.length = s.length + t.length;
				for (int i = 0; i < s.length; ++i) {
					str.data[i] = s.data[i];
				}
				for (int i = 0; i < t.length; ++i) {
					str.data[s.length + i] = t.data[i];
				}
				return str;
			}

			// 求子串 SubStr(s, i, len)
			// 返回串s中从第i个字符开始的长度为len的子串
			// 参数不正确时返回空串
			SqString SubStr(SqString s, int i, int len) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // 参数不正确时返回空串
				}
				// 注意逻辑序号和数组序号间转换
				for (int k = i - 1; k < i + len - 1; ++k) {
					str.data[k - i + 1] = s.data[k];
				}
				str.length = len;
				return str;
			}

			// 子串的插入 InsStr(s1,i,s2)
			// 将s2插入到s1
			// 不破坏原串，创建新串，依次赋值，中间接子串
			SqString InsStr(SqString s1, int i, SqString s2) {
				SqString str;
				str.length = 0;
				// i 为 s1.length 时，表示在 s1 最后插入串 s2，即连接, 可操作，不返回空串
				if (i <= 0 || i > s1.length + 1) {
					return str;    // 参数不正确时返回空串
				}
				for (int j = 0; j < i - 1; ++j) {
					str.data[j] = s1.data[j];
				}
				for (int j = 0; j < s2.length; ++j) {
					str.data[j + i - 1] = s2.data[j];
				}
				for (int j = i - 1; j < s1.length; ++j) {
					str.data[j + s2.length] = s1.data[j];
				}
				str.length = s1.length + s2.length;
				return str;
			}

			// 子串的删除 DelStr(s,i,len)
			// 不破换原串，创建新串，依次赋值，若删则跳过
			SqString DelStr(SqString s, int i, int len) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // 参数不正确时返回空串
				}
				for (int k = 0; k < i - 1; ++k) {
					str.data[k] = s.data[k];				
				}
				// k从逻辑序号为 第i+len-1（即子序列的最后一个）位置开始，其值正好为下一个元素的数组索引
				for (int k = i + len - 1; k < s.length; ++k) {
					str.data[k - len] = s.data[k];
				}
				str.length = s.length - len;
				return str;
			}

			// 子串的替换 RepStr(s,i,len,t)
			// 用t替换s中的子串
			// 不破换原串，创建新串，依次赋值，若替则赋t的值
			SqString RepStr(SqString s, int i, int len, SqString t) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // 参数不正确时返回空串
				}
				for (int k = 0; k < i - 1; ++k) {
					str.data[k] = s.data[k];
				}
				for (int k = 0; k < t.length; ++k) {
					str.data[k + i - 1] = t.data[k];
				}
				for (int k = i + len - 1; k < s.length; ++k) {
					str.data[k - len + t.length] = s.data[k];
				}
				str.length = s.length - len + t.length;
				return str;
			}

			// 输出串 DispStr(s)
			void DispStr(SqString s) {
				if (s.length > 0) {
					for (int i = 0; i < s.length; ++i) {
						printf("%c", s.data[i]);
					}
					printf("\n");
				}
			}

			// 例4.1 假设串采用顺序串存储，设计一个算法Strcmp(s,t)按字典顺序比较两个串的大小
			int Strcmp(SqString s, SqString t) {
				int comlen = 0;
				// 求s和t的共同长度
				if (s.length < t.length) {
					comlen = s.length;
				} else {
					comlen = t.length;
				}
				// 在共同长度内逐字比较，不同则返回相应值
				for (int i = 0; i < comlen; ++i) {
					if (s.data[i] > t.data[i]) {
						return 1;
					} else if (s.data[i] < t.data[i]) {
						return -1;
					}
				}
				// 执行到此处，表明两个字符串在共同长度内相同
				if (s.length == t.length) {
					return 0;    // 两个字符长度相同，共同字符串相同，返回0
				} else if (s.length > t.length) {
					return 1;    // 共同长度内相同，但s更长，返回1
				} else {
					return -1;
				}
			}

			// 例4.2 假设串采用顺序串存储，设计一个算法求串s中出现的第一个最长的连续相同字符构成的平台
			void LongestString(SqString s, int& index, int& maxlen) {
				index = 0;    // index保存最长平台在s中的开始位置
				maxlen = 1;    // maxlen保存其长度
				int i = 1, start, length;    // length保存局部平台的长度
				while (i < s.length) {
					start = i - 1;    // start 保存当前查找子串的开始位置
					length = 1;
					while (i < s.length && s.data[i] == s.data[i - 1]) {
						++i;
						++length;
					}
					// 若当前查找平台更长，更新
					if (maxlen < length) {
						maxlen = length;
						index = start;
					}
					++i;
				}
			}

		} // END namespace _4_2_1 串的顺序存储结构————顺序串

		// 4.2.2 串的链式存储结构————链串
		// 链串（linked string）
		// 最后修改：2019-9-24
		namespace _4_2_2 {
			// 结点类型
			typedef struct snode {
				char data;    // 存放字符
				struct snode* next;    // 下一个结点
			} LinkStrNode;

			// 生成串 StrAssign(&s,cstr)
			// 将一个C/C++字符串常量cstr（以'\0'字符标识结尾）赋给顺序串s
			// 参数s为指针引用，采用尾插法
			void StrAssign(LinkStrNode*& s, char cstr[]) {
				s = (LinkStrNode*)malloc(sizeof(LinkStrNode));    // 初始化串s
				LinkStrNode *p, *r = s;    // r 为尾指针
				for (int i = 0; cstr[i] != '\0'; ++i) {
					p = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					p->data = cstr[i];
					r->next = p;
					r = p;    // r始终指向尾结点
				}
				r->next = NULL;    // 尾结点的next置为空
			}

			// 销毁串 DestroyStr(&s)
			void DestroyStr(LinkStrNode*& s) {
				LinkStrNode *pre = s, *p = s->next;
				while (p != NULL) {
					free(pre);
					pre = p;
					p = pre->next;
				}
				free(pre);
			}

			// 复制 StrCopy(&s,t)
			void StrCopy(LinkStrNode*& s, LinkStrNode* t) {
				s = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				LinkStrNode *p = t->next, *r = s, *q;
				while (p != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				r->next = NULL;
			}

			// 判断是否相等 StrEqual(s,t)
			bool StrEqual(LinkStrNode* s, LinkStrNode* t) {
				LinkStrNode *p = s->next, *q = t->next;
				while (p != NULL && q != NULL && p->data == q->data) {
					p = p->next;
					q = q->next;
				}
				if (p == NULL && q == NULL) {
					return true;
				} else {
					return false;
				}
			}

			// 求串长 StrLength(s)
			int StrLength(LinkStrNode* s) {
				int i = 0;
				LinkStrNode* p = s->next;
				while (p != NULL) {
					++i;
					p = p->next;
				}
				return i;
			}

			// 连接 Concat(s,t)
			// 返回由两个串s和t连接在一起形成的结果串，不破环原串
			LinkStrNode* ConCat(LinkStrNode* s, LinkStrNode* t) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				LinkStrNode *p = s->next, *r = str, *q;
				while (p != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				p = t->next;    // 换串，再连一遍
				while (p != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				r->next = NULL;
				return str;
			}

			// 求子串 SubStr(s, i, len)
			// 返回串s中从第i个字符开始的长度为len的子串
			// 参数不正确时返回空串
			LinkStrNode* SubStr(LinkStrNode* s, int i, int len) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // 参数不正确时返回空串
				}
				LinkStrNode *r = str, *p = s->next, *q;
				// 让p指向s中的第i个结点
				for (int k = 1; k < i; ++k) {
					p = p->next;
				}
				for (int k = 1; k <= len; ++k) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				r->next = NULL;
				return str;
			}

			// 子串的插入 InsStr(s1,i,s2)
			// 将s2插入到s1
			// 不破坏原串，创建新串，依次赋值，中间接子串
			LinkStrNode* InsStr(LinkStrNode* s1, int i, LinkStrNode* s2) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s1) + 1) {
					return str;
				}
				LinkStrNode *p1 = s1->next, *p2 = s2->next, *r = str, *q;
				for (int k = 1; k < i; ++k) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p1->data;
					r->next = q;
					r = q;
					p1 = p1->next;
				}
				while (p2 != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p2->data;
					r->next = q;
					r = q;
					p2 = p2->next;
				}
				while (p1 != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p1->data;
					r->next = q;
					r = q;
					p1 = p1->next;
				}
				r->next = NULL;
				return str;
			}

			// 子串的删除 DelStr(s,i,len)
			// 不破换原串，创建新串，依次赋值，若删则跳过
			LinkStrNode* DelStr(LinkStrNode* s, int i, int len) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // 参数不正确时返回空串
				}
				LinkStrNode *p = s->next, *r = str, *q;
				for (int k = 1; k < i; ++k) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				for (int k = 0; k < len; ++k) {
					p = p->next;
				}
				while (p != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p->data;
					r->next = q;
					r = q;
					p = p->next;
				}
				r->next = NULL;
				return str;
			}

			// 子串的替换 RepStr(s,i,len,t)
			// 用t替换s的子串
			// 不破换原串，创建新串，依次赋值，若替则赋t的值
			LinkStrNode* RepStr(LinkStrNode* s, int i, int len, LinkStrNode* t) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // 参数不正确时返回空串
				}
				LinkStrNode *p1 = s->next, *p2 = t->next, *r = str, *q;
				for (int k = 1; k < i; ++k) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p1->data;
					r->next = q;
					r = q;
					p1 = p1->next;
				}
				for (int k = 0; k < len; ++k) {
					p1 = p1->next;
				}
				while (p2 != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p2->data;
					r->next = q;
					r = q;
					p2 = p2->next;
				}
				while (p1 != NULL) {
					q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					q->data = p1->data;
					r->next = q;
					r = q;
					p1 = p1->next;
				}
				r->next = NULL;
				return str;
			}

			// 输出串 DispStr(s)
			void DispStr(LinkStrNode* s) {
				LinkStrNode* p = s->next;
				while (p != NULL) {
					printf("%c", p->data);
					p = p->next;
				}
				printf("\n");
			}

			// 例4.3 链串中，将"ab"改为"xyz"
			void Repl(LinkStrNode*& s) {
				LinkStrNode *p = s->next, *q;
				bool find = false;
				while (p != NULL && p->next != NULL && !find) {
					if (p->data == 'a' && p->next->data == 'b') {
						p->data = 'x';
						p->next->data = 'z';
						q = (LinkStrNode*)malloc(sizeof(LinkStrNode));
						q->data = 'y';
						q->next = p->next;
						p->next = q;
						find = true;
					} else {
						p = p->next;
					}
				}
			}

		} // END namespace _4_2_2 串的链式存储结构————链串

	} // END namespace _4_2 串的存储结构

	// 4.3 串的模式匹配（pattern matching）
	// 目标串（target string）、模式串（pattern string）
	// 模式匹配成功是指在目标串s中找到了一个模式串t，返或t的第一个元素在s中出现的物理下标
	// 最后修改：2019-10-15
	namespace _4_3 {
		// 4.3.1 Brute-Force(暴力)算法 O(m × n)
		// 最后修改：2019-10-15
		namespace _4_3_1 {
			// 引入字符串类型，顺序存储
			using dst::_4_2::_4_2_1::SqString;
			
			// 算法如下：
			int BF(SqString s, SqString t) {
				int i = 0, j = 0;
				// 两个串都没有扫描完时循环
				while (i < s.length && j < t.length) {
					if (s.data[i] == t.data[j]) {
						++i;    // 当比较的两个字符相等
						++j;    // i j 都后移一位，来比较下一个
					} else {
						i = i - (j - 1);    // 当比较的两个字符不同，s串回溯到与t串开头处平行的地方
						j = 0;    // t串回到开头处
					}
				}
				if (j >= t.length) {
					return i - t.length;    // j超出t的边界，表示t是s的子串，返回t在s中的物理索引位置
				} else {
					return -1;    // 返回-1，表示模式匹配失败
				}
			}

		} // END namespace _4_3_1 Brute-Force(暴力)算法

		// 4.3.2 KMP算法 O(m + n)
		// 从目标串t中，提取出加速匹配的有用信息，以消除主串的指针回溯
		// 对于t串中的一个字符tj，tj的前一个字符向前最多k个，t从开头向后最多k个
		// 即，tj之前的串两端，各有k个元素（k < j)，他们完全相同
		// 用 back[j] = k 来表示，t串每个位置j上都有一个k的信息，构成一个back[]回退数组
		// back[j] = -1, j 为 0 时
		// back[j] = k, j之前，两端存在k个元素相同
		// back[j] = 0, 其他情况
		// 匹配时遇到不相等的ij处时，利用back[]信息消除主串的回溯，而使用模式串右滑
		// 时间复杂度为 O(m + n)，当所有back[]值都为0时，退化成BF算法
		// 最后修改：2019-10-15
		namespace _4_3_2 {
			// 引入字符串类型（sequential string），最大长度
			using dst::_4_2::_4_2_1::SqString;
			using dst::_4_2::_4_2_1::MaxSize;

			// 由模式串来求back[]回退数组
			// 1. back[0] = -1, back[1] = 0
			// 2. 如果 back[j] = k, 表示有 "t0 t1 ... t(k-1)" == "t(j-k) t(j-k+1) ... t(j-1)"
			// 2.1. 若 tk == tj，即 "t0 t1 ... t(k-1) tk" == "t(j-k) t(j-k+1) ... t(j-1) tj", 显然 back[j + 1] = k + 1
			// 2.2. 若 tk != tj，说明tj（包含tj）之前不存在长度为back[j] + 1的子串和开头字符起的子串相同，那么是否存在一个短一些的子串
			// 2.2. 此时令 k = back[k] 回退，下一步将 tj 与 tk 比较，可以此类推直到找到更短的子串
			// 2.2. 或直接到开头，不存在更短子串（此时，back[j+1] = 0)
			void getBack(SqString t, int back[]) {
				int j = 0, k = -1;    // j扫描目标串t， k来记录t[j]之前与t开头相同的字符的个数
				back[0] = -1;
				// 扫描一遍，求目标串t所有位置的back值
				while (j < t.length - 1) {
					// k为-1表示t回退到开头处，或字符相等
					if (k == -1 || t.data[j] == t.data[k]) {
						++j;    // j 和 k 依次移动到下一个字符
						++k;
						back[j] = k;
					} else {
						k = back[k];    // k 回退
					}
				}
			}

			/* KMP算法的匹配过程如下：
			i = 0, j = 0;
			while (s和t都没扫描完) {
				if (j == -1 或 i j 所指字符相等) {
					i j 分别增加一;
				} else {
					i不变，j回退到back[j]，即模式串右滑;
				}
			}
			if (j超界) {
				返回 i-t的长度;
			} else {
				返回 -1;
			}
			*/
			int KMPIndex(SqString s, SqString t) {
				int back[MaxSize];
				getBack(t, back);
				int i = 0, j = 0;
				while (i < s.length && j < t.length) {
					if (j == -1 || s.data[i] == t.data[j]) {
						++i;
						++j;
					} else {
						j = back[j];
					}
				}
				if (j >= t.length) {
					return i - t.length;
				} else {
					return -1;
				}
			}

		} // END namespace _4_3_2 KMP算法

		// 4.3.3 改进的KMP算法 O(m + n)
		// 按 4.3.2 中所得到的 back[] 数组存在缺陷
		// 当目标串中的字符 si != tj 时，如果 tj == t(back[j]) == tk 时，si 也一定不等于 tk， 此时将 j 回退为 back[j] = k 也无法匹配
		// 用 backval[] 来修正 back[]，在上述情况下（tj == t(back[j]) == tk），直接使 backval[j] = back[back[j]]
		// 其他情况，与之前一样，backval[0] = -1, backval[j] = back[j]
		namespace _4_3_3 {
			// 引入字符串类型（sequential string），最大长度
			using dst::_4_2::_4_2_1::SqString;
			using dst::_4_2::_4_2_1::MaxSize;

			// 由目标串t求出backval[]回退数组
			void getBackVal(SqString t, int backval[]) {
				int j = 0, k = -1;
				backval[0] = -1;
				while (j < t.length) {
					if (k == -1 || t.data[j] == t.data[k]) {
						++j;
						++k;
						if (t.data[j] != t.data[k]) {
							backval[j] = k;
						} else {
							backval[j] = backval[k];    // backval[k] 即 backval[backval[j]]
						}
					} else {
						k = backval[k];
					}
				}
			}

			// 改进后的KMP算法
			int KMPIndexVal(SqString s, SqString t) {
				int backval[MaxSize];
				getBackVal(t, backval);
				int i = 0, j = 0;
				while (i < s.length && j < t.length) {
					if (j == -1 || s.data[i] == t.data[j]) {
						++i;
						++j;
					} else {
						j = backval[j];
					}
				}
				if (j >= t.length) {
					return i - t.length;
				} else {
					return -1;
				}
			}

		} // END namespace _4_3_3 改进的KMP算法

	} // END namespace _4_3 串的模式匹配

} // END namespace dst 数据结构教程

#endif // !DST_4_STRING_H