// Author��Akame Qisixi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

#ifndef DST_4_STRING_H
#include "dst_4_string.h"
#endif // DST_4_STRING_H

// �ϻ�ʵ����4
// P145 ʵ����4���ı����ļ��ܺͽ��ܳ���
// Ŀ�ģ����մ���Ӧ���㷨���
// ���ݣ�һ���ı����������ȸ�������ĸӳ�����м��ܡ����磬����ĸӳ���Ϊ��
// a b c d e f g h i j k l m n o p q r s t u v w x y z
// n g z q t c o b m u h e l k p d a w x f y i v r s j
// ���ַ���"encrypt"������Ϊ"tkzwsdf"����дһ������exp4-4.cpp����������ı������ܺ������Ȼ����н��ܲ������
// ����޸ģ�2019-11-9
namespace experiment_4_4 {
	// �ַ�ת����������
	struct TransUtil {
		// ȥ���ַ����еĿո�
		static char* trimSpace(const char* src, int returnedStringLength) {
			int index = 0;
			int k = 0;
			char* ctr = new char[returnedStringLength + 1];
			while (src[index] != '\0' && k < returnedStringLength) {
				if (src[index] != ' ') {
					ctr[k++] = src[index];
				}
				++index;
			}
			ctr[k] = '\0';
			return ctr;
		}
	};

	// ��ĸӳ���
	class LettersMapTable {
	private:
		char* srcLetters;
		char* mapedLetters;
	public:
		LettersMapTable(const char* srcLetters, const char* mapedLetters) {
			this->srcLetters = TransUtil::trimSpace(srcLetters, 26);
			this->mapedLetters = TransUtil::trimSpace(mapedLetters, 26);
		}
		LettersMapTable() : LettersMapTable("a b c d e f g h i j k l m n o p q r s t u v w x y z",
											"n g z q t c o b m u h e l k p d a w x f y i v r s j")
		{
		}
		virtual ~LettersMapTable() {
			delete[] srcLetters;
			delete[] mapedLetters;
		}

		char encode(char src) const {
			for (int i = 0; i < 26; ++i) {
				if (srcLetters[i] == src) {
					return mapedLetters[i];
				}
			}
			return '\0';
		}

		char decode(char maped) const {
			for (int i = 0; i < 26; ++i) {
				if (mapedLetters[i] == maped) {
					return srcLetters[i];
				}
			}
			return '\0';
		}
		
	};

	using SqString = dst::_4_2::_4_2_1::SqString;

	SqString encode(SqString str, const LettersMapTable& lmt) {
		char* returnCtr = new char[str.length + 1];
		for (int i = 0; i < str.length; ++i) {
			returnCtr[i] = lmt.encode(str.data[i]);
		}
		returnCtr[str.length] = '\0';
		SqString returnStr;
		dst::_4_2::_4_2_1::StrAssign(returnStr, returnCtr);
		return returnStr;
	}

	SqString decode(SqString str, const LettersMapTable& lmt) {
		char* returnCtr = new char[str.length + 1];
		int index = 0;
		for (int i = 0; i < str.length; ++i) {
			returnCtr[i] = lmt.decode(str.data[i]);
		}
		returnCtr[str.length] = '\0';
		SqString returnStr;
		dst::_4_2::_4_2_1::StrAssign(returnStr, returnCtr);
		return returnStr;
	}

	void exp4_4() {
		LettersMapTable lmt;
		SqString str;
		char* ctr = const_cast<char*>("encrypt");
		dst::_4_2::_4_2_1::StrAssign(str, ctr);
		SqString enStr = encode(str, lmt);
		SqString deStr = decode(enStr, lmt);
		printf("�����ܵ��ַ���Ϊ��");
		dst::_4_2::_4_2_1::DispStr(enStr);
		printf("���ܺ���ַ���Ϊ��");
		dst::_4_2::_4_2_1::DispStr(deStr);
		dst::_4_2::_4_2_1::DestroyStr(str);
		dst::_4_2::_4_2_1::DestroyStr(enStr);
		dst::_4_2::_4_2_1::DestroyStr(deStr);
	}

} // END namespace experiment_4_4