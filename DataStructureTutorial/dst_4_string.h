// Author��Akame Qixisi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_4_STRING_H
#define DST_4_STRING_H

// �����£���

// ���ݽṹ�̳̣���5�棩 �廪��ѧ������
// Data Structure Tutorial
namespace dst {
	// 4.1 ����sting���Ļ�������
	// ����޸ģ�2019-9-24
	namespace _4_1 {
		// ���ĳ�������������������
		/*
		ADT String {
			���ݶ���:
				D = { ai | 1 <= i <= n, n >= 0, ai Ϊ char ���� }
			���ݹ�ϵ:
				R = { <ai,a(i+1)> | ai��a(i+1) �� D, i = 1,...,n - 1 }
			��������:
				// �������⣬��������δ�仯�������ƻ�������
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
	} // END namespace _4_1 ���Ļ�������

	// 4.2 ���Ĵ洢�ṹ
	// ˳�򴮣�sequential string���� ������linked string��
	// Ԫ�����ͣ�char
	// ����޸ģ�2019-9-24
	namespace _4_2 {
		// 4.2.1 ����˳��洢�ṹ��������˳��
		// ˳�򴮣�sequential string��
		// ����޸ģ�2019-9-24
		namespace _4_2_1 {
			// ������󳤶�
			const int MaxSize = 50;

			// ˳������
			typedef struct {
				char data[MaxSize];    // ��������
				int length;    // ������Ϣ
			} SqString;

			// ���ɴ� StrAssign(&s,cstr)
			// ��һ��C/C++�ַ�������cstr����'\0'�ַ���ʶ��β������˳��s
			// ����sΪ����
			void StrAssign(SqString& s, char cstr[]) {
				int i = 0;
				for (i = 0; cstr[i] != '\0'; ++i) {
					s.data[i] = cstr[i];
				}
				s.length = i;    // ���ô�s�ĳ���
			}

			// ���ٴ� DestroyStr(&s)
			void DestroyStr(SqString& s) {}

			// ���� StrCopy(&s,t)
			void StrCopy(SqString& s, SqString t) {
				for (int i = 0; i < t.length; ++i) {
					s.data[i] = t.data[i];
				}
				s.length = t.length;
			}

			// �ж��Ƿ���� StrEqual(s,t)
			bool StrEqual(SqString s, SqString t) {
				if (s.length != t.length) {
					return false;    // ���Ȳ����ֱ�ӷ���false
				}
				for (int i = 0; i < s.length; ++i) {
					if (s.data[i] != t.data[i]) {
						return false;    // ��һ�������ʱ�ͷ���false
					}
				}
				return true;    // ������ȣ��Ҷ�Ӧ�ַ�����ȣ�����true
			}

			// �󴮳� StrLength(s)
			int StrLength(SqString s) {
				return s.length;
			}

			// ���� Concat(s,t)
			// ������������s��t������һ���γɵĽ���������ƻ�ԭ��
			// û�м���������ĳ��ȳ�����󳤶ȵ����
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

			// ���Ӵ� SubStr(s, i, len)
			// ���ش�s�дӵ�i���ַ���ʼ�ĳ���Ϊlen���Ӵ�
			// ��������ȷʱ���ؿմ�
			SqString SubStr(SqString s, int i, int len) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // ��������ȷʱ���ؿմ�
				}
				// ע���߼���ź�������ż�ת��
				for (int k = i - 1; k < i + len - 1; ++k) {
					str.data[k - i + 1] = s.data[k];
				}
				str.length = len;
				return str;
			}

			// �Ӵ��Ĳ��� InsStr(s1,i,s2)
			// ��s2���뵽s1
			// ���ƻ�ԭ���������´������θ�ֵ���м���Ӵ�
			SqString InsStr(SqString s1, int i, SqString s2) {
				SqString str;
				str.length = 0;
				// i Ϊ s1.length ʱ����ʾ�� s1 �����봮 s2��������, �ɲ����������ؿմ�
				if (i <= 0 || i > s1.length + 1) {
					return str;    // ��������ȷʱ���ؿմ�
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

			// �Ӵ���ɾ�� DelStr(s,i,len)
			// ���ƻ�ԭ���������´������θ�ֵ����ɾ������
			SqString DelStr(SqString s, int i, int len) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // ��������ȷʱ���ؿմ�
				}
				for (int k = 0; k < i - 1; ++k) {
					str.data[k] = s.data[k];				
				}
				// k���߼����Ϊ ��i+len-1���������е����һ����λ�ÿ�ʼ����ֵ����Ϊ��һ��Ԫ�ص���������
				for (int k = i + len - 1; k < s.length; ++k) {
					str.data[k - len] = s.data[k];
				}
				str.length = s.length - len;
				return str;
			}

			// �Ӵ����滻 RepStr(s,i,len,t)
			// ��t�滻s�е��Ӵ�
			// ���ƻ�ԭ���������´������θ�ֵ��������t��ֵ
			SqString RepStr(SqString s, int i, int len, SqString t) {
				SqString str;
				str.length = 0;
				if (i <= 0 || i > s.length || len < 0 || i + len - 1 > s.length) {
					return str;    // ��������ȷʱ���ؿմ�
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

			// ����� DispStr(s)
			void DispStr(SqString s) {
				if (s.length > 0) {
					for (int i = 0; i < s.length; ++i) {
						printf("%c", s.data[i]);
					}
					printf("\n");
				}
			}

			// ��4.1 ���贮����˳�򴮴洢�����һ���㷨Strcmp(s,t)���ֵ�˳��Ƚ��������Ĵ�С
			int Strcmp(SqString s, SqString t) {
				int comlen = 0;
				// ��s��t�Ĺ�ͬ����
				if (s.length < t.length) {
					comlen = s.length;
				} else {
					comlen = t.length;
				}
				// �ڹ�ͬ���������ֱȽϣ���ͬ�򷵻���Ӧֵ
				for (int i = 0; i < comlen; ++i) {
					if (s.data[i] > t.data[i]) {
						return 1;
					} else if (s.data[i] < t.data[i]) {
						return -1;
					}
				}
				// ִ�е��˴������������ַ����ڹ�ͬ��������ͬ
				if (s.length == t.length) {
					return 0;    // �����ַ�������ͬ����ͬ�ַ�����ͬ������0
				} else if (s.length > t.length) {
					return 1;    // ��ͬ��������ͬ����s����������1
				} else {
					return -1;
				}
			}

			// ��4.2 ���贮����˳�򴮴洢�����һ���㷨��s�г��ֵĵ�һ�����������ͬ�ַ����ɵ�ƽ̨
			void LongestString(SqString s, int& index, int& maxlen) {
				index = 0;    // index�����ƽ̨��s�еĿ�ʼλ��
				maxlen = 1;    // maxlen�����䳤��
				int i = 1, start, length;    // length����ֲ�ƽ̨�ĳ���
				while (i < s.length) {
					start = i - 1;    // start ���浱ǰ�����Ӵ��Ŀ�ʼλ��
					length = 1;
					while (i < s.length && s.data[i] == s.data[i - 1]) {
						++i;
						++length;
					}
					// ����ǰ����ƽ̨����������
					if (maxlen < length) {
						maxlen = length;
						index = start;
					}
					++i;
				}
			}

		} // END namespace _4_2_1 ����˳��洢�ṹ��������˳��

		// 4.2.2 ������ʽ�洢�ṹ������������
		// ������linked string��
		// ����޸ģ�2019-9-24
		namespace _4_2_2 {
			// �������
			typedef struct snode {
				char data;    // ����ַ�
				struct snode* next;    // ��һ�����
			} LinkStrNode;

			// ���ɴ� StrAssign(&s,cstr)
			// ��һ��C/C++�ַ�������cstr����'\0'�ַ���ʶ��β������˳��s
			// ����sΪָ�����ã�����β�巨
			void StrAssign(LinkStrNode*& s, char cstr[]) {
				s = (LinkStrNode*)malloc(sizeof(LinkStrNode));    // ��ʼ����s
				LinkStrNode *p, *r = s;    // r Ϊβָ��
				for (int i = 0; cstr[i] != '\0'; ++i) {
					p = (LinkStrNode*)malloc(sizeof(LinkStrNode));
					p->data = cstr[i];
					r->next = p;
					r = p;    // rʼ��ָ��β���
				}
				r->next = NULL;    // β����next��Ϊ��
			}

			// ���ٴ� DestroyStr(&s)
			void DestroyStr(LinkStrNode*& s) {
				LinkStrNode *pre = s, *p = s->next;
				while (p != NULL) {
					free(pre);
					pre = p;
					p = pre->next;
				}
				free(pre);
			}

			// ���� StrCopy(&s,t)
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

			// �ж��Ƿ���� StrEqual(s,t)
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

			// �󴮳� StrLength(s)
			int StrLength(LinkStrNode* s) {
				int i = 0;
				LinkStrNode* p = s->next;
				while (p != NULL) {
					++i;
					p = p->next;
				}
				return i;
			}

			// ���� Concat(s,t)
			// ������������s��t������һ���γɵĽ���������ƻ�ԭ��
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
				p = t->next;    // ����������һ��
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

			// ���Ӵ� SubStr(s, i, len)
			// ���ش�s�дӵ�i���ַ���ʼ�ĳ���Ϊlen���Ӵ�
			// ��������ȷʱ���ؿմ�
			LinkStrNode* SubStr(LinkStrNode* s, int i, int len) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // ��������ȷʱ���ؿմ�
				}
				LinkStrNode *r = str, *p = s->next, *q;
				// ��pָ��s�еĵ�i�����
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

			// �Ӵ��Ĳ��� InsStr(s1,i,s2)
			// ��s2���뵽s1
			// ���ƻ�ԭ���������´������θ�ֵ���м���Ӵ�
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

			// �Ӵ���ɾ�� DelStr(s,i,len)
			// ���ƻ�ԭ���������´������θ�ֵ����ɾ������
			LinkStrNode* DelStr(LinkStrNode* s, int i, int len) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // ��������ȷʱ���ؿմ�
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

			// �Ӵ����滻 RepStr(s,i,len,t)
			// ��t�滻s���Ӵ�
			// ���ƻ�ԭ���������´������θ�ֵ��������t��ֵ
			LinkStrNode* RepStr(LinkStrNode* s, int i, int len, LinkStrNode* t) {
				LinkStrNode* str = (LinkStrNode*)malloc(sizeof(LinkStrNode));
				str->next = NULL;
				if (i <= 0 || i > StrLength(s) || len < 0 || i + len - 1 > StrLength(s)) {
					return str;    // ��������ȷʱ���ؿմ�
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

			// ����� DispStr(s)
			void DispStr(LinkStrNode* s) {
				LinkStrNode* p = s->next;
				while (p != NULL) {
					printf("%c", p->data);
					p = p->next;
				}
				printf("\n");
			}

			// ��4.3 �����У���"ab"��Ϊ"xyz"
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

		} // END namespace _4_2_2 ������ʽ�洢�ṹ������������

	} // END namespace _4_2 ���Ĵ洢�ṹ

	// 4.3 ����ģʽƥ�䣨pattern matching��
	// Ŀ�괮��target string����ģʽ����pattern string��
	// ģʽƥ��ɹ���ָ��Ŀ�괮s���ҵ���һ��ģʽ��t������t�ĵ�һ��Ԫ����s�г��ֵ������±�
	// ����޸ģ�2019-10-15
	namespace _4_3 {
		// 4.3.1 Brute-Force(����)�㷨 O(m �� n)
		// ����޸ģ�2019-10-15
		namespace _4_3_1 {
			// �����ַ������ͣ�˳��洢
			using dst::_4_2::_4_2_1::SqString;
			
			// �㷨���£�
			int BF(SqString s, SqString t) {
				int i = 0, j = 0;
				// ��������û��ɨ����ʱѭ��
				while (i < s.length && j < t.length) {
					if (s.data[i] == t.data[j]) {
						++i;    // ���Ƚϵ������ַ����
						++j;    // i j ������һλ�����Ƚ���һ��
					} else {
						i = i - (j - 1);    // ���Ƚϵ������ַ���ͬ��s�����ݵ���t����ͷ��ƽ�еĵط�
						j = 0;    // t���ص���ͷ��
					}
				}
				if (j >= t.length) {
					return i - t.length;    // j����t�ı߽磬��ʾt��s���Ӵ�������t��s�е���������λ��
				} else {
					return -1;    // ����-1����ʾģʽƥ��ʧ��
				}
			}

		} // END namespace _4_3_1 Brute-Force(����)�㷨

		// 4.3.2 KMP�㷨 O(m + n)
		// ��Ŀ�괮t�У���ȡ������ƥ���������Ϣ��������������ָ�����
		// ����t���е�һ���ַ�tj��tj��ǰһ���ַ���ǰ���k����t�ӿ�ͷ������k��
		// ����tj֮ǰ�Ĵ����ˣ�����k��Ԫ�أ�k < j)��������ȫ��ͬ
		// �� back[j] = k ����ʾ��t��ÿ��λ��j�϶���һ��k����Ϣ������һ��back[]��������
		// back[j] = -1, j Ϊ 0 ʱ
		// back[j] = k, j֮ǰ�����˴���k��Ԫ����ͬ
		// back[j] = 0, �������
		// ƥ��ʱ��������ȵ�ij��ʱ������back[]��Ϣ���������Ļ��ݣ���ʹ��ģʽ���һ�
		// ʱ�临�Ӷ�Ϊ O(m + n)��������back[]ֵ��Ϊ0ʱ���˻���BF�㷨
		// ����޸ģ�2019-10-15
		namespace _4_3_2 {
			// �����ַ������ͣ�sequential string������󳤶�
			using dst::_4_2::_4_2_1::SqString;
			using dst::_4_2::_4_2_1::MaxSize;

			// ��ģʽ������back[]��������
			// 1. back[0] = -1, back[1] = 0
			// 2. ��� back[j] = k, ��ʾ�� "t0 t1 ... t(k-1)" == "t(j-k) t(j-k+1) ... t(j-1)"
			// 2.1. �� tk == tj���� "t0 t1 ... t(k-1) tk" == "t(j-k) t(j-k+1) ... t(j-1) tj", ��Ȼ back[j + 1] = k + 1
			// 2.2. �� tk != tj��˵��tj������tj��֮ǰ�����ڳ���Ϊback[j] + 1���Ӵ��Ϳ�ͷ�ַ�����Ӵ���ͬ����ô�Ƿ����һ����һЩ���Ӵ�
			// 2.2. ��ʱ�� k = back[k] ���ˣ���һ���� tj �� tk �Ƚϣ����Դ�����ֱ���ҵ����̵��Ӵ�
			// 2.2. ��ֱ�ӵ���ͷ�������ڸ����Ӵ�����ʱ��back[j+1] = 0)
			void getBack(SqString t, int back[]) {
				int j = 0, k = -1;    // jɨ��Ŀ�괮t�� k����¼t[j]֮ǰ��t��ͷ��ͬ���ַ��ĸ���
				back[0] = -1;
				// ɨ��һ�飬��Ŀ�괮t����λ�õ�backֵ
				while (j < t.length - 1) {
					// kΪ-1��ʾt���˵���ͷ�������ַ����
					if (k == -1 || t.data[j] == t.data[k]) {
						++j;    // j �� k �����ƶ�����һ���ַ�
						++k;
						back[j] = k;
					} else {
						k = back[k];    // k ����
					}
				}
			}

			/* KMP�㷨��ƥ��������£�
			i = 0, j = 0;
			while (s��t��ûɨ����) {
				if (j == -1 �� i j ��ָ�ַ����) {
					i j �ֱ�����һ;
				} else {
					i���䣬j���˵�back[j]����ģʽ���һ�;
				}
			}
			if (j����) {
				���� i-t�ĳ���;
			} else {
				���� -1;
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

		} // END namespace _4_3_2 KMP�㷨

		// 4.3.3 �Ľ���KMP�㷨 O(m + n)
		// �� 4.3.2 �����õ��� back[] �������ȱ��
		// ��Ŀ�괮�е��ַ� si != tj ʱ����� tj == t(back[j]) == tk ʱ��si Ҳһ�������� tk�� ��ʱ�� j ����Ϊ back[j] = k Ҳ�޷�ƥ��
		// �� backval[] ������ back[]������������£�tj == t(back[j]) == tk����ֱ��ʹ backval[j] = back[back[j]]
		// �����������֮ǰһ����backval[0] = -1, backval[j] = back[j]
		namespace _4_3_3 {
			// �����ַ������ͣ�sequential string������󳤶�
			using dst::_4_2::_4_2_1::SqString;
			using dst::_4_2::_4_2_1::MaxSize;

			// ��Ŀ�괮t���backval[]��������
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
							backval[j] = backval[k];    // backval[k] �� backval[backval[j]]
						}
					} else {
						k = backval[k];
					}
				}
			}

			// �Ľ����KMP�㷨
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

		} // END namespace _4_3_3 �Ľ���KMP�㷨

	} // END namespace _4_3 ����ģʽƥ��

} // END namespace dst ���ݽṹ�̳�

#endif // !DST_4_STRING_H