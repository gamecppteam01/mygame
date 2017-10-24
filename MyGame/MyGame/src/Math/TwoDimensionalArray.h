#pragma once
#include<vector>
#include<tuple>
#include<utility>
#include<functional>

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
	//�S�v�f�̈ꊇ����(func:�����p�֐�)
	void loopElement(std::function<void(T&)> func) {
		for (auto& d : dataList_) {
			for (auto& c : d) {
				func(c);
			}
		}
	}
	//�S�v�f�̃|�C���^�R���e�i���쐬���ĕԂ�(�񐄏�)
	std::vector<T*> getAllDataPtr() {
		std::vector<T*> result;
		int ySize = dataList_.size();
		for (int y = 0; y < ySize; y++) {
			int xSize = dataList_[y].size();
			for (int x = 0; x < xSize; x++) {
				result.push_back(&dataList_[y][x]);
			}
		}
		return result;
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
