#pragma once
#include<vector>
#include<tuple>
#include<utility>
#include<functional>

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
	//全要素の一括処理(func:処理用関数)
	void loopElement(std::function<void(T&)> func) {
		for (auto& d : dataList_) {
			for (auto& c : d) {
				func(c);
			}
		}
	}
	//指定検索条件に合ったのキーを返す
	std::pair<int,int> getTargetKey(std::function<bool(T&,T&)> func) {
		std::pair<int, int> keyXY=std::make_pair(0,0);

		int ySize = dataList_.size();
		for (int y = 0; y < ySize; y++) {
			int xSize = dataList_[y].size();
			for (int x = 0; x < xSize; x++) {
				//現在の要素:新しい要素
				if (func(getElement(keyXY.first,keyXY.second),getElement(x, y))) {
					keyXY = std::make_pair(x, y);
				}
			}
		}
		return keyXY;
	}
	//全要素のポインタコンテナを作成して返す(非推奨)
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
	//二次元配列の行ごとの要素数
	int getXSize()const { return dataList_[0].size(); }
	//二次元配列の列ごとの要素数
	int getYSize()const { return dataList_.size(); }
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
