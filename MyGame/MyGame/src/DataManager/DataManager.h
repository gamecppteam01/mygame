#pragma once
#include<list>
#include"../ScoreManager/ScoreData.h"

class DataManager {
private:
	DataManager() = default;
	~DataManager();

public:
	static DataManager& GetInstance() {
		static DataManager d;
		return d;
	}

	void setData(std::list<ScoreData>& list);
	std::list<ScoreData> getData() const;

	void setStage(int stage);
	int getStage()const;

private:
	std::list<ScoreData> datas_;

	//ステージ番号
	int chooseStage_{ 1 };
};