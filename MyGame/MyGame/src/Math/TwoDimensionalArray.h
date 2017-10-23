#pragma once
#include<vector>
#include<tuple>
#include<utility>

template<typename T>
//�񎟌��z��Ǘ��N���X
class TwoDimensionalArray {
private:
public:
	TwoDimensionalArray(){}
	template <typename...Datas>
	TwoDimensionalArray(int xSize,int ySize,Datas... data) {
		//�w��͈͕��̃f�[�^�g���m�ۂ���
		dataList_.resize(ySize);
		for (auto& d : dataList_) {
			d.resize(xSize);
		}
		//�f�[�^���Z�b�g����
		int dataSize = sizeof...(data);
		setData(0, 0, xSize, ySize,0, dataSize, data...);

	}
	//�f�[�^�̎擾
	T getElement(int x, int y) {
		return dataList_[y][x];
	}
	//�f�[�^�̐ݒ�
	void setElement(int x, int y,const T& data) {
		dataList_[y][x] = data;
	}

private:
	//�f�[�^�Z�b�g�p�̍ċA�֐�
	void setData(int xSize, int ySize, int xMaxSize, int yMaxSize, int loopCount, int dataSize){}
	template <typename Data1,typename...Datas>
	//x,y�̌��ݒl�ƍő�l�ƃf�[�^�ʁA�ϒ��������Avector�Ƀf�[�^�����Ă���
	void setData(int xSize,int ySize,int xMaxSize,int yMaxSize,int loopCount,int dataSize,const Data1& d, Datas... data) {
		loopCount++;
	
		dataList_[ySize][xSize]=d;
		int nextX = (xSize + 1) % yMaxSize;
		int nextY = loopCount / xMaxSize;
		
		setData(nextX, nextY, xMaxSize, yMaxSize, loopCount, dataSize, data...);
	}


private:
	std::vector<std::vector<T>> dataList_;

};
