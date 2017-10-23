#pragma once
#include<vector>
#include<tuple>
#include<utility>

template<typename T>
//二次元配列管理クラス
class TwoDimensionalArray {
private:
public:
	TwoDimensionalArray(){}
	template <typename...Datas>
	TwoDimensionalArray(int xSize,int ySize,Datas... data) {
		//指定範囲分のデータ枠を確保して
		dataList_.resize(ySize);
		for (auto& d : dataList_) {
			d.resize(xSize);
		}
		//データをセットする
		int dataSize = sizeof...(data);
		setData(0, 0, xSize, ySize,0, dataSize, data...);

	}
	//データの取得
	T getElement(int x, int y) {
		return dataList_[y][x];
	}
	//データの設定
	void setElement(int x, int y,const T& data) {
		dataList_[y][x] = data;
	}

private:
	//データセット用の再帰関数
	void setData(int xSize, int ySize, int xMaxSize, int yMaxSize, int loopCount, int dataSize){}
	template <typename Data1,typename...Datas>
	//x,yの現在値と最大値とデータ量、可変長引数より、vectorにデータを入れていく
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
