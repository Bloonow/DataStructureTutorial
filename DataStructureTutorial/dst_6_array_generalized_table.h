// Author��Akame Qixisi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_6_ARRAY_GENERALIZED_TABLE_H
#define DST_6_ARRAY_GENERALIZED_TABLE_H

// �����£�����͹����

// ���ݽṹ�̳̣���5�棩 �廪��ѧ������
// Data Structure Tutorial
namespace dst {
	// 6.1 ���飨array��
	// ����޸ģ�2019-10-8
	namespace _6_1 {
		// ����ĳ������������������£�
		/*
		ADT Array {
			���ݶ���:
				D = { aj1,j2,...,jd | ji = 1,...,bi, i = 1, 2,...,d }    // ��iά�ĳ���Ϊbi
			���ݹ�ϵ:
				R = { r1, r2,..., rd }
				ri = { <aj1...ji...jd, aj1...(ji+1)...jd> | 1 <= jk <= bk �� k != i, 1 <= ji <= bi - 1, i = 2,...,d }
			��������:
				InitArray(&A);
				DestroyArray(&A);
				Value(A, index1, index2, ..., indexd);
				Assign(A, e, index1, index2, ..., indexd);
		}
		*/

		// ���¹�ʽ�ݲ����߼���ţ�Loc��ʾȡ��ַ���㣬 ÿ��Ԫ��ռ�� k ���洢��Ԫ
		// ������ţ�C/C++�У������߼���ż�һ������ i-1 ���� i ����ʾ�������
		/* һά����Ĵ洢�ṹ��Loc(ai) = Loc(a1) + (i - 1) * k
		   ��ά����(M x N)�İ������ȴ�ţ�Loc(ai,j) = Loc(a1,1) + [ (i - 1) * n + (j - 1) ] * k
		   ��ά����(M x N)�İ������ȴ�ţ�Loc(ai,j) = Loc(a1,1) + [ (j - 1) * m + (i - 1) } * k
		*/

		// ��������ѹ���洢���Գƾ����������Ǿ��󣬶ԽǾ���
		// ��һ��һά���Ա�һά���飩B[0,1,...,k,...] �洢��Ҫ�洢�Ķ�ά�����е�Ԫ��
		/* �Գƾ����� k �� i j �Ĺ�ϵ��
		k = i * (i + 1) / 2 + j, i >= j ������
		k = j * (j + 1) / 2 + i, i < j ������
		*/
		/* �����Ǿ����� k �� i j �Ĺ�ϵ��
		k = i * (2n - i + 1) / 2 + j - i, i <= j ��������
		k = n * (n + 1) / 2, i > j
		*/
		/* �����Ǿ����� k �� i j �Ĺ�ϵ��
		k = i * (i + 1) / 2 + j, i >= j ������
		k = n * (n + 1) / 2, i < j
		*/

	} // END namespace _6_1 ����

	// 6.2 ϡ�����sparse matrix��
	// ����Ԫ�صĸ���ԶС��Ԫ���ܸ����ľ���
	// Ԫ�����ͣ�int
	// ����޸ģ�2019-10-10
	namespace _6_2 {
		// ϡ������ѹ����ֻ�洢�����Ԫ��
		// ���������Ԫ�طֲ�û�ɹ��ɣ��ʻ���洢����Ԫ�ص�λ����Ϣ

		// 6.2.1 ϡ��������Ԫ���ʾ
		// ��һ����Ԫ�飨3-tuples������ʾһ������Ԫ��
		// һ��ϡ����������еķ���Ԫ�ذ����Թ�ϵ����һ�����Ա���
		// ��Ԫ��˳���list of 3-tuples��
		// ��������Ϊ��������
		// ����޸ģ�2019-10-10
		namespace _6_2_1 {
			// Ԫ������
			typedef int ElemType;

			// ϡ����������������
			const int M = 20;
			const int N = 20;

			// ϡ������з���Ԫ�����ĸ���
			constexpr int MaxSize = int((M * N) / 10);

			// ��Ԫ������
			typedef struct {
				int r;    // �к�
				int c;    // �к�
				ElemType d;    // Ԫ��ֵ
			} TupNode;

			// ��Ԫ��˳�������
			typedef struct {
				int rows;    // ����
				int cols;    // ����
				int nums;    // ����Ԫ�ظ���
				TupNode data[MaxSize];
			} TSMatrix;

			// ��һ����άϡ����󴴽�����Ԫ���ʾ
			void CreateMat(TSMatrix& t, ElemType A[M][N]) {
				t.rows = M; t.cols = N; t.nums = 0;
				for (int i = 0; i < M; ++i) {
					for (int j = 0; j < N; ++j) {
						// ֻ�洢����Ԫ��
						if (A[i][j] != 0) {
							t.data[t.nums].r = i;
							t.data[t.nums].c = j;
							t.data[t.nums].d = A[i][j];
							++t.nums;
						}
					}
				}
			}

			// ��Ԫ��Ԫ�صĸ�ֵ x != 0
			// ������Ԫ��˳������ҵ��ʵ�λ��k����˳�����λ��Ϊk��Ԫ������ ����[i][j]������ ֮��ĵ�һ����˳����е�Ԫ��
			// ���˳�����kԪ�����þ�����[i][j]Ԫ�أ���Ӧһ������Ԫ�أ�����d�������޸�Ϊx
			// ���˳�����kԪ����[i][j]֮�󣬱���[i][j]λ����Ϊ�㣬�ȸ�ֵΪx���ٽ�˳�����k֮��Ԫ�غ���һλ��x���뵽kλ��
			bool SetValue(TSMatrix& t, ElemType x, int i, int j) {
				if (i >= t.rows || j >= t.cols) {
					return false;    // ���� i j Խ����󣬷���false
				}
				int k = 0;
				while (k < t.nums && t.data[k].r < i) {
					++k;    // Ѱ�Ҵ��ڵ���i�еķ���Ԫ�أ���˳����е�λ��k
				}
				while (k < t.nums && t.data[k].c == i && t.data[k].c < j) {
					++k;    // ����i���з���Ԫ�أ�Ѱ�Ҵ��ڵ��ڵ�j�еķ���Ԫ�أ���˳����е�λ��k
				}
				if (t.data[k].r == i && t.data[k].c == j) {
					t.data[k].d = x;    // ��˳�����λ��k��Ԫ�����þ��� ����ij ��Ӧ��Ԫ�أ���ֵ 
				} else {
					// ij ��Ϊ��Ԫ�أ�Ҫ��˳����в��룬���ƶ������Ԫ�أ��ٸ�ֵ
					for (int k1 = t.nums - 1; k1 >= k; --k1) {
						t.data[k1 + 1].r = t.data[k1].r;
						t.data[k1 + 1].c = t.data[k1].c;
						t.data[k1 + 1].d = t.data[k1].d;
					}
					t.data[k].r = i; t.data[k].c = j; t.data[k].d = x;
					++t.nums;    // ����Ԫ�صļ�������һ
				}
				return true;
			}

			// ��ָ��λ�õ�Ԫ�ظ�������
			bool Assign(TSMatrix t, ElemType &x, int i, int j) {
				if (i >= t.rows || j >= t.cols) {
					return false;    // ���� i j Խ����󣬷���false
				}
				int k = 0;
				while (k < t.nums && t.data[k].r < i) {
					++k;    // Ѱ�Ҵ��ڵ���i�еķ���Ԫ�أ���˳����е�λ��k
				}
				while (k < t.nums && t.data[k].c == i && t.data[k].c < j) {
					++k;    // ����i���з���Ԫ�أ�Ѱ�Ҵ��ڵ��ڵ�j�еķ���Ԫ�أ���˳����е�λ��k
				}
				if (t.data[k].r == i && t.data[k].c == j) {
					x = t.data[k].d;    // ��˳�����λ��k��Ԫ�����þ��� ����ij ��Ӧ��Ԫ�أ���ֵ 
				} else {
					x = 0;    // ָ��λ��ij����˳����У���Ϊ��Ԫ��
				}
				return true;
			}

			// �����Ԫ��˳���
			void DispMat(TSMatrix t) {
				if (t.nums <= 0) {
					return;    // û�з���Ԫ�أ���˳���Ϊ��
				}
				printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
				printf("\t----------------------------------\n");
				for (int k = 0; k < t.nums; ++k) {
					printf("\t%d\t%d\t%d\n", t.data[k].r, t.data[k].c, t.data[k].d);
				}
			}

			// ϡ�����ת�� O(t.cols X t.rows)
			// ��tb���洢ת�þ���B����Ԫ��˳���
			// ��ֵ�ؽ�tb
			void TranTat(TSMatrix t, TSMatrix& tb) {
				if (t.nums <= 0) {
					return;    // û�з���Ԫ�أ���˳���Ϊ��
				}
				tb.rows = t.cols; tb.cols = t.rows; tb.nums = t.nums;
				int k1 = 0;    // k1��¼Ŀǰtb��Ԫ�صĸ���
				// ���б���ԭ����
				for (int v = 0; v < t.cols; ++v) {
					// ���α���˳����еķ���Ԫ�أ��ж���λ���Ƿ��ǵ�v��
					for (int k = 0; k < t.nums; ++k) {
						if (t.data[k].c == v) {
							tb.data[k1].r = t.data[k].c;
							tb.data[k1].c = t.data[k].r;
							tb.data[k1].d = t.data[k].d;
							++k1;
						}
					}
				}
			}

		} // END namespace _6_2_1 ϡ��������Ԫ���ʾ

		// 6.2.2 ϡ������ʮ������ʾ
		// ÿ��һ����ͷ��㣬ÿ��һ����ͷ��㣬����һ����ͷ���
		// ÿ��Ԫ�ؽ��ͬʱ�洢���к�������ѭ����������
		// ����޸ģ�2019-10-10
		namespace _6_2_2 {
			// ϡ��������������
			const int M = 20;
			const int N = 20;
			constexpr int Max = M > N ? M : N;

			typedef int ElemType;

			// ���ݽ����ɣ��С��С�ֵ����ָ������ָ����
			// ���н����ɣ��С��С�link����ָ������ָ����
			// ���������������ݽṹ���ƣ��ʲ��ù�����
			typedef struct mtxn {
				int row;    // �кŻ�����
				int col;    // �кŻ�����
				struct mtxn *right, *down;    // �ҡ���ָ��
				union {
					ElemType value;
					struct mtxn* link;
				} tag;
			} MatNode;

			// ��6.2 ˫�㼯��
			/*
			typedef struct dnode {
				int data;
				struct dnode* next;
			} DType;

			typedef struct hnode {
				DType* next;
				struct hnode* link;
			} HType;
			*/

		} // END namespace _6_2_2 ϡ������ʮ������ʾ

	} // END namespace _6_2 ϡ�����

	// 6.3 �����generalized table��
	// ����������Ա���ƹ㣬�����޸�Ԫ�ص����У����ű�ʾ��
	// Ԫ�����ͣ�ԭ�ӣ�atom�����ӱ�subgeneralized table��
	// ����Ϊ��������Ԫ�صĸ��������ΪǶ�׵Ĳ���
	// Ԫ�����ͣ�char
	// ����޸ģ�2019-10-10
	namespace _6_3 {
		// �����ĳ����������Ͷ������£�
		/*
		ADT GList {
			���ݶ���:
				D = { ei | 1 <= i <= n, n >= 0, ei �� AtomSet �� ei �� GList, AtomSetΪĳ�����ݶ��� }
			������ϵ:
				R = { <e(i-1), ei> | e(i-1)��ei �� D, 2 <= i <= n }
			��������:
				CreateGL(s);
				DestroyGL(&g);
				GLLength(g);
				GLDepth(g);
				DispGL(g);
		*/

		typedef char ElemType;

		// �����Ĵ洢�ṹ
		typedef struct lnode {
			int tag;    // ������ͱ�ʶ��0Ϊԭ�ӽ�㣬1Ϊ�ӱ���
			union {
				ElemType data;    // ���ԭ��ֵ
				struct lnode* sublist;    // ָ���ӱ��ָ��
			} val;
			struct lnode* link;    // ָ����һ��Ԫ��
		} GLNode;    // �����Ľ������

		// ���������㣬Ϊʹ�㷨���㣬�ڹ������߼���ʾ���á�(#)����ʾ�ձ�
		// ��Ԫ��Ϊ��㣬���������ӱ��ͷ���

		// ������ĳ���
		int GLLength(GLNode* g) {
			int n = 0;    // �ۼ�Ԫ�ظ�������ʼΪ0
			GLNode* g1 = g->val.sublist;    // g1ָ������ĵ�һ��Ԫ��
			while (g1 != NULL) {
				++n;    // Ԫ�ظ�����һ
				g1 = g1->link;    // ɨ������Ԫ�ؽ��
			}
			return n;
		}

		// ����������
		// ԭ�����Ϊ0���ձ����Ϊ1������������Ϊ max{ f(subg) } + 1
		int GLDepth(GLNode* g) {
			if (g->tag == 0) {
				return 0;    // ԭ�����ͣ�����0
			}
			GLNode* g1 = g->val.sublist;
			if (g1 == NULL) {
				return 1;    // �ձ�����1
			}
			int maxd = 0;
			// �������е�ÿ��Ԫ��
			while (g1 != NULL) {
				// ��Ԫ��Ϊ�ӱ��ʱ���ж�Ŀǰ�����ȣ�������
				if (g1->tag == 1) {
					int dep = GLDepth(g1);
					if (dep > maxd) {
						maxd = dep;
					}
				}
				g1 = g1->link;
			}
			return maxd + 1;
		}

		// ��������
		void DispGL(GLNode* g) {
			if (g != NULL) {
				// Ԫ��Ϊԭ������
				if (g->tag == 0) {
					printf("%c", g->val.data);    
				} else {
					// Ԫ������Ϊ�ӱ�
					printf("(");
					if (g->val.sublist == NULL) {
						printf("#");    // Ϊ�ձ�
					} else {
						DispGL(g->val.sublist);    // �ǿձ��ݹ�����ӱ�
					}
					printf(")");
				}
				if (g->link != NULL) {
					printf(",");
					DispGL(g->link);
				}
				/*g = g->link;*/
			}
		}

		// ������������ʽ�洢�ṹ
		// ����������߼��ṹ�������ű�ʾ��ÿ��ԭ�ӵ�ֵ���޶�Ϊ����Ӣ����ĸ
		GLNode* CreateGL(char*& s) {
			GLNode* g;
			char ch = *s++;    // ȡһ���ַ�
			// sδɨ����ʱ
			if (ch != '\0') {
				g = (GLNode*)malloc(sizeof(GLNode));    // ����һ���½��
				if (ch == '(') {
					g->tag = 1;    // �ַ�Ϊ ( ����־�ӱ�ͷ
					g->val.sublist = CreateGL(s);    // �ݹ鹹���ӱ����丳����ǰ����sublist����ǰ�Ľ����Ϊ�ӱ��ͷ���
				} else if (ch == ')') {
					g = NULL;
				} else if (ch == '#') {
					g = NULL;
				} else {
					g->tag = 0;    // Ԫ��Ϊԭ���ַ�
					g->val.data = ch;
				}
			} else {
				g = NULL;    // �ַ�ɨ����ϣ�g��Ϊ��
			}
			ch = *s++;    // ȡ��һ��δ������ַ�
			if (g != NULL) {
				if (ch == ',') {
					g->link = CreateGL(s);    // �����ֵܽ��
				} else {
					g->link = NULL;
				}
			}
			return g;
		}

		// ���ٹ����
		void DestroyGL(GLNode*& g) {
			GLNode *g1, *g2;
			g1 = g->val.sublist;    // g1ָ������ĵ�һ��Ԫ��
			// ��������Ԫ��
			while (g1 != NULL) {
				// ��Ϊԭ�ӽ��
				if (g1->tag == 0) {
					g2 = g1->link;    // g2��ʱ�����ֵܽ��
					free(g1);    // �ͷ�g1��ָ��ԭ�ӽ��
					g1 = g2;    // g1ָ�����ֵܽ��
				} else {
					// ��Ϊ�ӱ�
					g2 = g1->link;
					DestroyGL(g1);    // �ݹ��ͷ�g1��ָ���ӱ�ռ�
					g1 = g2;
				}
			}
			free(g);
		}

		// ��6.3 ���ڲ�����ʽ�洢�ṹ�Ĺ�������һ���㷨��ԭ��Ԫ�ظ���
		// �ⷨһ��
		int Count1(GLNode* g) {
			GLNode* g1 = g->val.sublist;
			int count = 0;
			while (g1 != NULL) {
				if (g1->tag == 0) {
					++count;
				} else {
					count += Count1(g1);
				}
				g1 = g1->link;
			}
			return count;
		}

		// ��6.3 ���ڲ�����ʽ�洢�ṹ�Ĺ�������һ���㷨��ԭ��Ԫ�ظ���
		// �ⷨ����
		int Count2(GLNode* g) {
			int count = 0;
			if (g != NULL) {
				if (g->tag == 0) {
					++count;
				} else {
					count += Count2(g->val.sublist);
				}
				count += Count2(g->link);
			}
			return count;
		}

	} // END namespace _6_3 �����

} // END namespace dst ���ݽṹ�̳�

#endif // !DST_6_ARRAY_GENERALIZED_TABLE_H