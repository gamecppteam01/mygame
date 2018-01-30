#pragma once
#include<cmath>

class ByteConverter{
public:
	//�擪�����ʃo�C�g�Ƃ���byte�z���int�ɕϊ�����(byte�z��̐擪�Ɣz��T�C�Y���󂯎��)
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
		underDigit -= 128;//unsigned char����char�ւ̕ϊ�(�l���킹)
		overDigit -= 128;//unsigned char����char�ւ̕ϊ�(�l���킹)
		result.push_back(overDigit);
		result.push_back(underDigit);

		return result;
	}
	static int String_to_Int(const std::string& text) {
		int underNum = text.back() + 128;//char����unsigned char�ɕϊ�
		int overNum = text.front() + 128;//char����unsigned char�ɕϊ�

		return overNum * 256 + underNum;
	}
	//�w��o�C�g���̍ő�l��Ԃ�
	static int ByteMaxSize(int size) {
		return std::pow(256, size);
	}
	//�w��o�C�g�v�Z���ʒl���}�C�i�X�l�ɕϊ�����(�v�Z�Ώےl�Ƃ��̒l�̌�byte�����󂯎��)
	static int ReverseNumber(int i,int size) {
		return -(ByteMaxSize(size) - i);
	}
};
