#pragma once
#include<cmath>

class ByteConverter{
public:
	//先頭を下位バイトとしたbyte配列をintに変換する(byte配列の先頭と配列サイズを受け取る)
	static int Byte_to_Int(unsigned char* data,int size) {
		int result = 0;
		for (int i = 0; i < size; i++) {
			result += data[i]*std::pow(256,i);
		}
		return result;
	}
	static std::string Int_to_String(int num) {
		std::string result;

		int underDigit = num % 256;
		int overDigit = num / 256;
		underDigit -= 128;//unsigned charからcharへの変換(値合わせ)
		overDigit -= 128;//unsigned charからcharへの変換(値合わせ)
		result.push_back(overDigit);
		result.push_back(underDigit);

		return result;
	}
	static int String_to_Int(const std::string& text) {
		int underNum = text.back() + 128;//charからunsigned charに変換
		int overNum = text.front() + 128;//charからunsigned charに変換

		return overNum * 256 + underNum;
	}
	//指定バイト数の最大値を返す
	static int ByteMaxSize(int size) {
		return std::pow(256, size);
	}
	//指定バイト計算結果値をマイナス値に変換する(計算対象値とその値の元byte数を受け取る)
	static int ReverseNumber(int i,int size) {
		return -(ByteMaxSize(size) - i);
	}
};
