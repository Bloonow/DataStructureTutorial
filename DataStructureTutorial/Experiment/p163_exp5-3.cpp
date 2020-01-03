// Author：Akame Qisixi / Excel Bloonow
// 作者： 巫见 / 血梦墨雪

// 上机实验题5
// P163 实验题3：恢复IP地址
// 目的：掌握基本递归算法设计
// 内容：给定一个仅仅包含数字的字符串，恢复它所有可能的有效IP地址
// 例如：给定字符串“25525511135”，返回“255.255.11.135” 和 “255.255.111.35”（顺序可以任意）
// 最后修改：2019-11-19
namespace experiment_5_3 {

	int charSequenceToNum(const char* chSeq, int length) {
		int num = 0;
		for (int i = 0; i < length; num = num * 10 + (chSeq[i++] - '0'));
		return num;
	}

	// ip最少要4位，标准ip地址有4组，每组数字在0~255之间
	// 初始时置ip地址如下：0.0.0.00--000（firstDotIndex为k时表示第一组到k之前的字符，第二组从第k个开始）
	// 从右向左，依次右移分割点，并判断当前分割后的每组ip值是否符合要求
	// 若都符合要求，则可以输出
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
		// 最后一组不符合要求
		if (fourthIpGroupValue > 255) {
			++thirdDotIndex;    // 第三个分隔点后移
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