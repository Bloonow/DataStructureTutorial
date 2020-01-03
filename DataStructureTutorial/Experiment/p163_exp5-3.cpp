// Author��Akame Qisixi / Excel Bloonow
// ���ߣ� �׼� / Ѫ��īѩ

// �ϻ�ʵ����5
// P163 ʵ����3���ָ�IP��ַ
// Ŀ�ģ����ջ����ݹ��㷨���
// ���ݣ�����һ�������������ֵ��ַ������ָ������п��ܵ���ЧIP��ַ
// ���磺�����ַ�����25525511135�������ء�255.255.11.135�� �� ��255.255.111.35����˳��������⣩
// ����޸ģ�2019-11-19
namespace experiment_5_3 {

	int charSequenceToNum(const char* chSeq, int length) {
		int num = 0;
		for (int i = 0; i < length; num = num * 10 + (chSeq[i++] - '0'));
		return num;
	}

	// ip����Ҫ4λ����׼ip��ַ��4�飬ÿ��������0~255֮��
	// ��ʼʱ��ip��ַ���£�0.0.0.00--000��firstDotIndexΪkʱ��ʾ��һ�鵽k֮ǰ���ַ����ڶ���ӵ�k����ʼ��
	// ���������������Ʒָ�㣬���жϵ�ǰ�ָ���ÿ��ipֵ�Ƿ����Ҫ��
	// ��������Ҫ����������
	void Do(const char* ip, int totalLength, int firstDotIndex, int secondDotIndex, int thirdDotIndex) {
		if (totalLength < 4) {
			return;
		}
		int fourthIpGroupValue, thirdIpGroupValue, secondIpGroupValue, firstIpGroupValue;
		fourthIpGroupValue = charSequenceToNum(ip + thirdDotIndex, totalLength - thirdDotIndex);
		thirdIpGroupValue = charSequenceToNum(ip + secondDotIndex, thirdDotIndex - secondDotIndex);
		secondIpGroupValue = charSequenceToNum(ip + firstDotIndex, secondDotIndex - firstDotIndex);
		firstIpGroupValue = charSequenceToNum(ip, firstDotIndex);
		if ((firstIpGroupValue <= 255) && (secondIpGroupValue <= 255) && (thirdIpGroupValue <= 255) && (fourthIpGroupValue <= 255)) {
			printf("%d.%d.%d.%d\n", firstIpGroupValue, secondIpGroupValue, thirdIpGroupValue, fourthIpGroupValue);
			++thirdDotIndex;
			fourthIpGroupValue = charSequenceToNum(ip + thirdDotIndex, totalLength - thirdDotIndex);
		}
		// ���һ�鲻����Ҫ��
		if (fourthIpGroupValue > 255) {
			++thirdDotIndex;    // �������ָ������
			thirdIpGroupValue = charSequenceToNum(ip + secondDotIndex, thirdDotIndex - secondDotIndex);
		}
		if (thirdIpGroupValue > 255) {
			++secondDotIndex;
			secondIpGroupValue = charSequenceToNum(ip + firstDotIndex, secondDotIndex - firstDotIndex);
		}
		if (secondIpGroupValue > 255) {
			++firstDotIndex;
			firstIpGroupValue = charSequenceToNum(ip, firstDotIndex);
		}
		if (firstIpGroupValue > 255) {
			return;
		}
		Do(ip, totalLength, firstDotIndex, secondDotIndex, thirdDotIndex);
	}

	void exp5_3() {
		const char* ip1 = "25525511135";
		printf("srcIP: %s\n", ip1);
		Do(ip1, 11, 1, 2, 3);
	}

} // END namespace experiment_5_3