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

private:
	std::list<ScoreData> datas_;
};